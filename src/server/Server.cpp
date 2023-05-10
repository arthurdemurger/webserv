/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 16:46:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Server.hpp"


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Server::Server(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
	socket = new ListenSocket(domain, service, protocol, port, interface, bklg);
}

Server::Server(const Server &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Server::~Server() { delete socket; }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const Server &Server::operator=(const Server &copy)
{
	if (this != &copy)
	{
		delete socket;
		socket = copy.socket;
	}
	return (*this);
}


/*
** ------------------------------- ACCESSOR --------------------------------
*/
ListenSocket	*Server::getSocket(void) const { return (socket); }

/*
** ------------------------------- METHODS --------------------------------
*/

void	Server::accepter()
{
	struct sockaddr_in	address = socket->getAddress();
	int					addressLen = sizeof(address);
	int					n;

	if((tmpSocket = accept(socket->getServerSock(), (struct sockaddr *) &address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();
	if ((n = read(tmpSocket, buffer, 30000)) < 0)
		throw Server::ReadException();
}

void	Server::handler() const
{
	std::cout << buffer << std::endl;
}

void	Server::responder() const
{
	char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	write(tmpSocket, hello, strlen(hello));
}

void	Server::launcher(void)
{
	while (true)
	{
		std::cout << "waiting..." << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "done..." << std::endl;

		close (tmpSocket);
	}
}