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

#include "../../inc/sockets/ListenSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
ListenSocket::ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bklg) :
	BindSocket(domain, service, protocol, port, interface), backlog(bklg)
{
	check((isListening = listening()), LISTEN);
}

ListenSocket::ListenSocket(const ListenSocket &copy) : BindSocket(copy), backlog(copy.backlog) { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const ListenSocket	&ListenSocket::operator=(const ListenSocket &copy)
{
	if (this != &copy)
	{
		serverSock = copy.getServerSock();
		isConnected = copy.getIsConnected();
		address = copy.getAddress();
		backlog = copy.getBacklog();
		isListening = copy.getIsListening();
	}
	return (*this);
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
ListenSocket::~ListenSocket() { }

/*
** ------------------------------- ACCESSORS --------------------------------
*/
int					ListenSocket::getBacklog(void) const { return (backlog); }
int					ListenSocket::getIsListening(void) const { return (isListening); }

/*
** ------------------------------- METHODS --------------------------------
*/

int	ListenSocket::listening(void)
{
	return (listen(getIsConnected(), backlog));
}

