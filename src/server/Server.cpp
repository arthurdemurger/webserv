/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 15:13:22 by ademurge         ###   ########.fr       */
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
void				Server::set_config(Config conf) { _config = conf; }

/*
** ------------------------------- METHODS --------------------------------
*/

/*
for each port of the server object, create one socket object and populate vector of sockets
then populate the fds vector w. the server socket
*/

int	Server::activate(int port, int backlog)
{
	Socket	sock;

	if (sock.create_socket(port, INADDR_ANY, backlog) == -1)
		return (-1);
	_sockets.push_back(sock);
	_fds.push_back(_sockets.back().getServerFd());
	return (0);
}

/*
for each Config block, configure the server object by getting its ports
then loop through vector of ports and call activate() for each port
*/
int	Server::configure(Config conf)
{
	_config = conf;
	_name = _config.get_name();
	std::vector<int> ports = _config.get_ports();

	for (std::vector<int>::iterator it = ports.begin(); it != ports.end(); it++)
		if (activate((*it), BACKLOG) == -1)
			return (-1);
	return (0);
}
