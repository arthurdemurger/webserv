/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:26 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 15:21:09 by ademurge         ###   ########.fr       */
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
	_max_fd = 0;
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

std::string Launcher::getCurrentTime()
{
	char buf[9];

	std::time_t currentTime = std::time(NULL);
	std::tm* timeStruct = std::localtime(&currentTime);

	std::sprintf(buf, "%02d:%02d:%02d", timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);
	return (buf);
}

std::string	Launcher::log_launch(void)
{
	std::vector<int>	ports;
	std::string			log;

	for (std::map<int, Server>::iterator map_it = _servers.begin(); map_it != _servers.end(); map_it++)
	{
		std::vector<int> vec = map_it->second.get_config().get_ports();
		for (std::vector<int>::iterator vec_it = vec.begin(); vec_it != vec.end(); vec_it++)
			if (std::find(ports.begin(), ports.end(), (*vec_it)) == ports.end())
				ports.push_back(*vec_it);
	}

	log = "[Ports : ";
	for (std::vector<int>::iterator it = ports.begin(); it != ports.end(); it++)
	{
		if ((*it) != ports.back())
			log += std::to_string((*it)) + ", ";
		else
			log += std::to_string((*it));
	}
	log += "]";
	return (log);
}

 void	Launcher::put_on_console(std::string color, std::string status, std::string message)
{
	std::string	time = getCurrentTime();

	if (status.length() != 18)
		status.resize(18, ' ');

	std::cout << CYAN << "[" << getCurrentTime() << "] " << color << status << " " << message << RESET << std::endl;
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

void	Launcher::close_socket(int socket)
{
	put_on_console(MAGENTA, "CONNECTION REMOVED", "socket " + std::to_string(socket) + " (" + _servers[_clients[socket].get_server_fd()].get_name() + ")");
	if (FD_ISSET(socket, &_read_pool))
		remove_from_set(socket, _read_pool);
	if (FD_ISSET(socket, &_write_pool))
		remove_from_set(socket, _write_pool);
	close(socket);
	_clients.erase(socket);
}

void	Launcher::accepter(int server_sock)
{
	int					new_client;
	struct sockaddr_in	address = _servers[server_sock].get_sockets()[server_sock].getAddress();
	int					addressLen = sizeof(address);

	if((new_client = accept(server_sock, (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		return (put_on_console(BKGD_RED, "Accept failed.", ""));

	add_to_set(new_client, _read_pool);
	if (fcntl(new_client, F_SETFL, O_NONBLOCK) < 0)
	{
		close_socket(new_client);
		return (put_on_console(BKGD_RED, "fcntl failed.", ""));
	}

	_clients.erase(new_client);
	_clients.insert(std::make_pair(new_client, Client(new_client, server_sock)));

	put_on_console(YELLOW, "ACCEPT CONNECTION", "socket " + std::to_string(new_client) + " (" + _servers[server_sock].get_name() + ")");
}

void	Launcher::handle_response(int &client_sock)
{
		std::string response = _clients[client_sock].send_response();

		if (response.empty())
		{
			close_socket(client_sock);
			return (put_on_console(BKGD_RED, "read/write failed.", ""));
		}

		std::string protocol = "HTTP/1.1 ";
		size_t	size;
		std::string	header = "";

		if (((size = response.find("\n")) != std::string::npos) && (size - protocol.length() >= 0))
			header = response.substr(protocol.length(), response.find("\n") - protocol.length());

		put_on_console(GREEN, "SEND RESPONSE", header);
		close_socket(client_sock);
}

void	Launcher::handle_request(int &client_sock, Client &client)
{
	std::string path = client.add_request(_servers[client.get_server_fd()].get_config());

	if (path.empty())
	{
		close_socket(client.get_socket());
		return (put_on_console(BKGD_RED, "Read failed.", ""));
	}

	remove_from_set(client_sock, _read_pool);
	add_to_set(client_sock, _write_pool);

	put_on_console(RED, "READ_REQUEST", path);
}

int	Launcher::setup(void)
{
	std::vector<Server>	servers;
	Parser	parser(_config_file);
	std::vector<Config> configs = parser.getConfig();

	for (std::vector<Config>::iterator it = configs.begin(); it != configs.end(); it++)
	{
		Server				serv;
		std::vector<int>	fds;

		if (serv.configure(*it) == -1)
			return (-1);
		fds = serv.get_fds();
		for (std::vector<int>::iterator ite = fds.begin(); ite != fds.end(); ite++)
			_servers[(*ite)] = serv;
	}
	for (std::map<int, Server>::iterator i = _servers.begin(); i != _servers.end(); i++)
	{
		std::vector<int> fds = i->second.get_fds();
		for (std::vector<int>::iterator j = fds.begin(); j != fds.end(); j++)
			add_to_set(*j, _read_pool);
	}
	return (0);
}

void	Launcher::run(void)
{
	int	ret;

	fd_set	read_pool_cpy;
	fd_set	write_pool_cpy;
	struct timeval	timer;

	if (setup() < 0)
	{
		for (std::map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); it++)
		{
			std::vector<int>	vec = it->second.get_fds();
			for (std::vector<int>::iterator fds = vec.begin(); fds !=  vec.end(); fds++)
				close(*fds);
		}
		return ;
	}

	std::string message_log = log_launch();
	put_on_console(DARK_GREY, "WEBSERV LAUNCHED", message_log);
	while (true)
	{
		// std::cout << "########## WAITING ##########" << std::endl;
		timer.tv_sec = TIME_OUT;
		read_pool_cpy = _read_pool;
		write_pool_cpy = _write_pool;
		if ((ret = select(_max_fd + 1, &read_pool_cpy, &write_pool_cpy, NULL, &timer)) < 0)
			throw Launcher::SelectException();
		if (!ret)
		{
			put_on_console(DARK_GREY, "TIMEOUT", "");
			// system("leaks webserv");
			break ;
		}
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
				handle_response(sock);
		}
		// std::cout << "########## DONE    ##########" << std::endl << std::endl;
	}
}
