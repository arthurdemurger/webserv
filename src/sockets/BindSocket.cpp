/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 11:12:19 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sockets/BindSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
BindSocket::BindSocket(int domain, int service, int protocol, int port, u_long interface) :
	Socket(domain, service, protocol, port, interface)
{
	if (connect_to_ntwk() < 0)
		throw BindSocket::BindException();
}

BindSocket::BindSocket(const BindSocket &copy) : Socket(copy) { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const BindSocket	&BindSocket::operator=(const BindSocket &copy)
{
	if (this != &copy)
	{
		_server_fd = copy.getServerFd();
		_address = copy.getAddress();
	}
	return (*this);
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
BindSocket::~BindSocket() { }

/*
** ------------------------------- ACCESSORS --------------------------------
*/

/*
** ------------------------------- METHODS --------------------------------
*/

int	BindSocket::connect_to_ntwk(void)
{
	return (bind(_server_fd, (struct sockaddr *) &_address, sizeof(_address)));
}


