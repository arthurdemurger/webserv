/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:26 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/01 13:01:09 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Launcher.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Launcher::Launcher(std::string conf_filename)
{
	if (conf_filename.empty())
		_config_file = "config/default.conf";
	else
		_config_file = conf_filename;

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
Launcher::~Launcher(void) { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Launcher	&Launcher::operator=(const Launcher &copy)
{
	if (this != &copy)
	{
		_servers = copy._servers;
		_parser = copy._parser;
		_read_pool = copy._read_pool;
		_write_pool = copy._write_pool;
	}
	return (*this);
}
/*
** ------------------------------- METHODS --------------------------------
*/
void	Launcher::setup(void)
{
	std::vector<Server>	servers;
	Parser	parser(_config_file);
	std::vector<Config> configs = parser.getConfig();

	for (std::vector<Config>::iterator it = configs.begin(); it != configs.end(); it++)
	{
		Server				serv;
		std::vector<int>	fds;

		serv.configure(*it);
		fds = serv.get_fds();
		for (std::vector<int>::iterator ite = fds.begin(); ite != fds.end(); ite++)
			_servers[(*ite)] = serv;
	}
}

void	Launcher::add_serv_to_sets(void)
{
	for (std::map<int, Server>::iterator i = _servers.begin(); i != _servers.end(); i++)
	{
		std::vector<int> fds = i->second.get_fds();
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

void	Launcher::accepter(int server_sock)
{
	int					new_client;
	struct sockaddr_in	address = _servers[server_sock].get_sockets()[server_sock].getAddress();
	int					addressLen = sizeof(address);

	if((new_client = accept(server_sock, (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();

	add_to_set(new_client, _read_pool);
	if (fcntl(new_client, F_SETFL, O_NONBLOCK) < 0)
		throw Server::FcntlException();
	_clients.erase(new_client);
	_clients.insert(std::make_pair(new_client, Client(new_client, server_sock)));

	std::cout << BKGD_YELLOW << "[ACCEPT CONNECTION]" << RESET << " " << YELLOW << _servers[_clients[new_client].get_server_fd()].get_name() << " - client socket [" << _clients[new_client].get_socket() << "]" << RESET << std::endl;

}

void	Launcher::handle_response(int &client_sock, Client &client)
{
	// std::cout << "2 - " << client.is_request_parsed() << std::endl;
	if (client.is_request_parsed())
	{
		std::cout << BKGD_GREEN << "[SEND RESPONSE]" << RESET << " " << GREEN << _servers[client.get_server_fd()].get_name() << " - client socket [" << client.get_socket() << "]" << RESET << std::endl;
		_clients[client_sock].send_response();
		close(client_sock);
		remove_from_set(client_sock, _read_pool);
		remove_from_set(client_sock, _write_pool);
		_clients.erase(client_sock);
		std::cout << BKGD_MAGENTA << "[CONNECTION REMOVED]" << RESET << " " << MAGENTA << _servers[client.get_server_fd()].get_name() << " - client socket [" << client.get_socket() << "]" << RESET << std::endl;
	}
}

void	Launcher::handle_request(int &client_sock, Client &client)
{

	client.add_request(_servers[client.get_server_fd()].get_config());
	remove_from_set(client_sock, _read_pool);
	add_to_set(client_sock, _write_pool);
	// close(client_sock);
	// remove_from_set(client_sock, _read_pool);
	// remove_from_set(client_sock, _write_pool);
	// _clients.erase(client_sock);
	// --client_sock;
	std::cout << BKGD_RED << "[READ REQUEST]" << RESET << " " << RED << _servers[client.get_server_fd()].get_name() << " - client socket [" << client.get_socket() << "] | is parsed : " << client.is_request_parsed() << RESET << std::endl;
}

void Launcher::print_fd(void)
{
	std::vector<std::string> names;

	for (std::map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		if (std::find(names.begin(), names.end(), it->second.get_name()) == names.end())
		{
			names.push_back(it->second.get_name());
			std::vector<int> fds = it->second.get_fds();
			for (std::vector<int>::iterator ite = fds.begin(); ite != fds.end(); ite++)
				std::cout << "server [" << it->first << "] - fd  :" << (*ite) << std::endl;
		}
	}
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		std::cout << "client socket [" << it->second.get_socket() << "] - server : " << it->second.get_server_fd() << std::endl;
}



void	Launcher::run(void)
{
	fd_set	read_pool_cpy;
	fd_set	write_pool_cpy;

	_max_fd = 0;
	setup();
	add_serv_to_sets();
	while (true)
	{
		std::cout << "########## WAITING ##########" << std::endl;

		read_pool_cpy = _read_pool;
		write_pool_cpy = _write_pool;
		if (select(_max_fd + 1, &read_pool_cpy, &write_pool_cpy, NULL, NULL) < 0)
			throw Launcher::SelectException();
		for (int sock = 0; sock <= _max_fd; ++sock)
		{
			if (FD_ISSET(sock, &read_pool_cpy))
			{
				if (_servers.count(sock))
					accepter(sock);
				else if (_clients.count(sock))
					handle_request(sock, _clients[sock]);
			}
			else if (FD_ISSET(sock, &write_pool_cpy) && _clients.count(sock))
				handle_response(sock, _clients[sock]);
		}
		// print_fd();
		// sleep(5);
		std::cout << "########## DONE    ##########" << std::endl << std::endl;
	}
}