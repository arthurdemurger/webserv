/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 14:03:38 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sockets/Socket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Socket::Socket(int domain, int service, int protocol, int port,  u_long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

	// Establish isConnected
	check((serverSock = socket(domain, service , protocol)), SOCKET);
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
		serverSock = copy.serverSock;
		address = copy.address;
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
int					Socket::getServerSock(void) const { return (serverSock); };
struct sockaddr_in	Socket::getAddress(void) const { return (address); };

/*
** ------------------------------- METHODS --------------------------------
*/
void		Socket::check(int itemToTest, int error)
{
	if (itemToTest < 0)
	{
		switch(error)
		{
			case SOCKET:
				perror("Socket failed.");
				break;
			case BIND:
				perror("Bind failed.");
				break;
			case CONNECT:
				perror("Connect failed.");
				break;
			case LISTEN:
				perror("Listen failed.");
				break;
			default:
				perror("Problem detected.");
		}
		exit(EXIT_FAILURE);
	}
}

