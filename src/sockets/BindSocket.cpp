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
	// Establish network connection
	setIsConnected(connect_to_ntwk());
	check(getIsConnected(), BIND);
}

BindSocket::BindSocket(const BindSocket &copy)
{
	*this = copy;
}

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const BindSocket	&BindSocket::operator=(const BindSocket &copy)
{
	if (this != &copy)
	{
		serverSock = copy.getServerSock();
		isConnected = copy.getIsConnected();
		address = copy.getAddress();
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
	return (bind(serverSock, (struct sockaddr *) &address, sizeof(address)));
}


