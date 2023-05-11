/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/11 12:21:05 by ademurge         ###   ########.fr       */
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

void	Server::accepter(int clientSocket)
{
	struct sockaddr_in	address = socket->getAddress();
	int					addressLen = sizeof(address);

	if((clientSocket = accept(socket->getServerSock(), (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();
}

void	Server::handler(int clientSocket, char *buffer) const
{
	int	n;

	if ((n = read(clientSocket, (void *) buffer, BUF_SIZE)) < 0)
		throw Server::ReadException();
	std::cout << "'" << buffer << "'" << std::endl;
}

void	Server::responder(int clientSocket) const
{
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	write(clientSocket, hello.c_str(), hello.size());
	// responder();
}

void	Server::launcher(void)
{
	char	buffer[BUF_SIZE];
	int		clientSocket;
	int		max_fd = 0;
	fd_set	curr_sockets, ready_sockets;

	max_fd = socket->getServerSock();

	FD_ZERO(&curr_sockets);
	FD_SET(socket->getServerSock(), &curr_sockets);
	while (true)
	{
		std::cout << "waiting..." << std::endl;

		ready_sockets = curr_sockets;
		if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
		{
			perror("select error");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i <= max_fd; i++)
		{
			if (FD_ISSET(i, &ready_sockets))
			{
				if (i == socket->getServerSock())
				{
					accepter(clientSocket);
					FD_SET(clientSocket, &curr_sockets);
					if (clientSocket > max_fd)
						max_fd = clientSocket;
				}
				else
				{
					handler(i, buffer);
					FD_CLR(i, &curr_sockets);
				}
			}
		}

		std::cout << "done..." << std::endl;
		close (clientSocket);
	}
}