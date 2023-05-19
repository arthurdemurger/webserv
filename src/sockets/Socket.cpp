/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 15:33:07 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sockets/Socket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Socket::Socket(int domain, int service, int protocol, int port,  u_long interface)
{
	_address.sin_family = domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(interface);

	if((_server_fd = socket(domain, service, protocol)) < 0)
		throw Socket::SocketException();
	const int enable = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    	throw Socket::SocketException();
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

