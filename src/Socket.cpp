/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/09 17:06:00 by ademurge         ###   ########.fr       */
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
	// Bind
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

/*
** ------------------------------- METHODS --------------------------------
*/
void		Socket::check(int item, char *message)
{
	if (item < 0)
		perror(message);
	exit(EXIT_FAILURE);
}

