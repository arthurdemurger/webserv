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

#include "../inc/BindSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
BindSocket::BindSocket(int domain, int service, int protocol, int port, u_long interface) :
	Socket(domain, service, protocol, port, interface)
{
	// Establish network connection
	setConnection(connect_to_ntwk());
	check(getConnection(), "Bind failed.");
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
		connection = copy.getConnection();
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


