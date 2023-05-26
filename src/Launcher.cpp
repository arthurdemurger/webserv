/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:26 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 15:39:58 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Launcher.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Launcher::Launcher(std::string conf_filename)
{
	if (conf_filename.empty())
		conf_filename = "config/default.conf";

	setup(conf_filename);

	FD_ZERO(&_read_pool);
	FD_ZERO(&_write_pool);
}

Launcher::Launcher(const Launcher &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Launcher::~Launcher(void)
{
	for (std::map<int, Server *>::iterator it = _servers.begin(); it != _servers.end(); it++)
		if (it->second)
			delete (it->second);
}

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Launcher	&Launcher::operator=(const Launcher &copy)
{
	if (this != &copy)
	{
		for (std::map<int, Server *>::iterator it = _servers.begin(); it != _servers.end(); it++)
			if (it->second)
				delete (it->second);

		std::map<int, Server *>	map = copy._servers;

		for (std::map<int, Server *>::iterator it = map.begin(); it != map.end(); it++)
			_servers[it->first] = new Server(*(map[it->first]));
		_parser = copy._parser;
		_read_pool = copy._read_pool;
		_write_pool = copy._write_pool;
	}
	return (*this);
}
/*
** ------------------------------- METHODS --------------------------------
*/
void	Launcher::setup(std::string conf_filename)
{
	Parser	pars(conf_filename);

	// pars.getConfig();
	
	// Server serv;

	// serv.activate(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY, 10);
	// _servers[serv.get_fd()] = serv;
}

void	Launcher::accepter(int server_sock)
{
	int	new_client;
	struct sockaddr_in	address = _servers[server_sock]->get_sockets()[server_sock].getAddress();
	int					addressLen = sizeof(address);

	if((new_client = accept(server_sock, (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();

	std::cout << YELLOW << "Accept new connection | server '" << server_sock <<  "' => socket : " << new_client << RESET << std::endl;
	FD_SET(new_client, &_read_pool);
	FD_SET(new_client, &_write_pool);
	if (fcntl(new_client, F_SETFL, O_NONBLOCK) < 0)
		throw Server::FcntlException();
	if (_clients.count(new_client))
		_clients.erase(new_client);
	_clients[new_client] = Client(new_client, server_sock);
	if (new_client > _max_fd)
		_max_fd = new_client;
}

void	Launcher::send_response(int client_sock, Client client)
{
	_clients[client_sock].send_response();
	std::cout << CYAN << "response sent | server '" << client.get_server_fd() <<  "' => socket : " << client_sock << RESET << std::endl;
	close(client_sock);
	FD_CLR(client_sock, &_read_pool);
	FD_CLR(client_sock, &_write_pool);
	_clients.erase(client_sock);
	std::cout << LIGHTMAGENTA << "connection removed | server '" << client.get_server_fd() <<  "' => socket : " << client_sock << RESET << std::endl;
}

void	Launcher::add_request(int &client_sock, Client client)
{
	std::cout << RED << "Read request | server '" << client.get_server_fd() <<  "' => socket : " << client_sock << RESET << std::endl;
	FD_SET(client_sock, &_write_pool);
	if (!_clients[client_sock].add_request())
	{
		close(client_sock);
		FD_CLR(client_sock, &_read_pool);
		FD_CLR(client_sock, &_write_pool);
		_clients.erase(client_sock);
		--client_sock;
	}
}

void	Launcher::add_serv_to_set(void)
{
	for (std::map<int, Server *>::iterator i = _servers.begin(); i != _servers.end(); i++)
	{
		std::vector<int> fds = i->second->get_fds();
		for (std::vector<int>::iterator j = fds.begin(); j != fds.end(); j++)
			add_to_set(*j, _read_pool);
	}
}

void	Launcher::remove_from_set(int fd, fd_set &set)
{
	FD_CLR(fd, &set);
	if (_max_fd == fd)
		_max_fd--;
}

void	Launcher::add_to_set(int fd, fd_set &set)
{
	FD_SET(fd, &set);
	if (_max_fd < fd)
		_max_fd = fd;
}

void	Launcher::run(void)
{
	fd_set	read_pool_cpy;
	fd_set	write_pool_cpy;

	_max_fd = 0;


	add_serv_to_set();
	while (true)
	{
		std::cout << "########## WAITING ##########" << std::endl;

		read_pool_cpy = _read_pool;
		write_pool_cpy = _write_pool;
		if (select(_max_fd + 1, &read_pool_cpy, &write_pool_cpy, NULL, NULL) < 0)
			throw Launcher::SelectException();
		for (int sock = 0; sock <= _max_fd; ++sock)
		{
			if (FD_ISSET(sock, &read_pool_cpy) && _servers.count(sock))
				accepter(sock);
			else if (FD_ISSET(sock, &read_pool_cpy) && _clients.count(sock))
				add_request(sock, _clients[sock]);
			else if (FD_ISSET(sock, &write_pool_cpy) && _clients.count(sock))
				send_response(sock, _clients[sock]);
		}
		std::cout << "########## DONE    ##########" << std::endl << std::endl;
	}
}