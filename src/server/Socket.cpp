/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/13 11:26:12 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Socket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Socket::Socket(void) { }
#include <arpa/inet.h>

Socket::Socket(int port,  u_long interface, int backlog)
{
	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(interface);

	if((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw Socket::SocketException();
	const int enable = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw Socket::SocketException();
	if (bind(_server_fd, reinterpret_cast<sockaddr*>(&_address), sizeof(_address)) < 0)
		throw Socket::BindException();
	if (listen(_server_fd, backlog) < 0)
		throw Socket::ListenException();
	if (fcntl(_server_fd, F_SETFL, O_NONBLOCK) < 0)
		throw Socket::FcntlException();
}

Socket::Socket(const Socket &copy)
{
	*this = copy;
}

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const Socket	&Socket::operator=(const Socket &copy)
{
	if (this != &copy)
	{
		_server_fd = copy._server_fd;
		_address = copy._address;
		_backlog = copy._backlog;
	}
	return (*this);
}


/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Socket::~Socket() { }

/*
** ------------------------------- ACCESSORS --------------------------------
*/
int					Socket::getServerFd(void) const { return (_server_fd); };
struct sockaddr_in	Socket::getAddress(void) const { return (_address); };

/*
** ------------------------------- METHODS --------------------------------
*/

