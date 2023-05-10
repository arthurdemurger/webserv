/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 11:16:20 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Socket::Socket(int domain, int service, int protocol, int port,  u_long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

	// Establish connection
	check((serverSock = socket(domain, service , protocol)), "socket failed.");
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
		connection = copy.connection;
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
int					Socket::getConnection(void) const { return (connection); };
struct sockaddr_in	Socket::getAddress(void) const { return (address); };
void				Socket::setConnection(int con) { connection = con; };

/*
** ------------------------------- METHODS --------------------------------
*/
void		Socket::check(int item, char *message)
{
	if (item < 0)
		perror(message);
	exit(EXIT_FAILURE);
}

