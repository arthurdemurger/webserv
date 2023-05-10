/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 15:49:56 by ademurge         ###   ########.fr       */
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

void	Server::check(int itemToCheck, int error)
{
	if (itemToCheck < 0)
	{
		switch(error)
		{
			case ACCEPT:
				perror("Accept failed.");
				break ;
			case READ:
				perror("Read failed.");
			default:
				perror("problem detected.");
		}
		exit(EXIT_FAILURE);
	}
}

void	Server::accepter()
{
	struct sockaddr_in	address = socket->getAddress();
	int					addressLen = sizeof(address);
	int					n;

	check((tmpSocket = accept(socket->getServerSock(), (struct sockaddr *) &address, (socklen_t *) &addressLen)), ACCEPT);
	check((n = read(tmpSocket, buffer, 30000)), READ);
}

void	Server::handler()
{
	std::cout << buffer << std::endl;
}

void	Server::responder()
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