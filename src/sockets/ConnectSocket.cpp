/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 12:25:28 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sockets/ConnectSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
ConnectSocket::ConnectSocket(int domain, int service, int protocol, int port, u_long interface) :
	Socket(domain, service, protocol, port, interface)
{
	// Establish network connection
	setIsConnected(connect_to_ntwk());
	check(getIsConnected(), CONNECT);
}

ConnectSocket::ConnectSocket(const ConnectSocket &copy)
{
	*this = copy;
}

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const ConnectSocket	&ConnectSocket::operator=(const ConnectSocket &copy)
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
ConnectSocket::~ConnectSocket() { }

/*
** ------------------------------- ACCESSORS --------------------------------
*/

/*
** ------------------------------- METHODS --------------------------------
*/

int	ConnectSocket::connect_to_ntwk(void)
{
	return (connect(serverSock, (struct sockaddr *) &address, sizeof(address)));
}


