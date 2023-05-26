/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 18:04:27 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Server.hpp"

#include "../../inc/server/Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Server::Server()
{

}

Server::Server(const Server &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Server::~Server() { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Server &Server::operator=(const Server &copy)
{
	if (this != &copy)
	{
		_name = copy._name;
		_sockets = copy._sockets;
		_fds = copy._fds;
		_config = copy._config;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSOR --------------------------------
*/
Config				Server::get_config(void) const { return (_config); }
std::vector<int>	Server::get_fds(void) const { return (_fds); }
std::string			Server::get_name(void) const { return (_name); }
std::vector<Socket>	Server::get_sockets(void) const { return (_sockets); }
void				Server::set_config(Config const &conf) { _config = conf; }

/*
** ------------------------------- METHODS --------------------------------
*/
void	Server::activate(int protocol, int port, int backlog)
{
	_sockets.push_back(Socket(AF_INET, SOCK_STREAM, protocol, port, INADDR_ANY, backlog));
	_fds.push_back(_sockets.back().getServerFd());
}

void	Server::configure(Config const &conf)
{
	_config = conf;
	_name = _config.get_name();
	std::vector<int> ports = _config.get_ports();

	for (std::vector<int>::iterator it = ports.begin(); it != ports.end(); it++)
		activate(0, (*it), 10);
}
