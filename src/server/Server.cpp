/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/11 15:06:31 by ademurge         ###   ########.fr       */
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

void	Server::accepter(int &clientSocket, char *buffer)
{
	struct sockaddr_in	address = socket->getAddress();
	int					addressLen = sizeof(address);

	if((clientSocket = accept(socket->getServerSock(), (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();
	if (read(clientSocket, buffer, BUF_SIZE) < 0)
		throw Server::ReadException();
	std::cout << "'" << buffer << "'" << std::endl;
	}

void	Server::handler(int &clientSocket, char *buffer) const
{
	std::cout << "'" << buffer << "'" << std::endl;
	responder(clientSocket);
}

void	Server::responder(int &clientSocket) const
{
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<!doctype html><html><head><title>This is the title of the webpage!</title></head><body><p>This is an example paragraph. Anything in the <strong>body</strong> tag will appear on the page, just like this <strong>p</strong> tag and its contents.</p></body></html>";
	write(clientSocket, hello.c_str(), hello.size());
}

void	Server::launcher(void)
{
	char	buffer[BUF_SIZE];
	int		clientSocket;
	int		max_fd = 0;
	fd_set	read_fd_tmp, write_fd_tmp;

	max_fd = socket->getServerSock();

	FD_ZERO(&read_fd_set);
	FD_ZERO(&write_fd_set);
	FD_SET(socket->getServerSock(), &read_fd_set);
	while (true)
	{
	 	std::cout << "waiting..." << std::endl;

		read_fd_tmp = read_fd_set;
		write_fd_tmp = write_fd_set;
		if (select(max_fd + 1, &read_fd_tmp, &write_fd_tmp, NULL, NULL) < 0)
		{
			perror("select error");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i <= max_fd; i++)
		{
			if (FD_ISSET(i, &read_fd_tmp))
			{
				if (i == socket->getServerSock())
				{
					accepter(clientSocket, buffer);
					FD_SET(clientSocket, &read_fd_set);
					if (clientSocket > max_fd)
						max_fd = clientSocket;
				}
				else
				{
					handler(i, buffer);
					FD_CLR(i, &read_fd_set);
				}
			}
		}
			// accepter(clientSocket);
			// handler(clientSocket, buffer);
			// responder(clientSocket);
		std::cout << "done..." << std::endl;
		close (clientSocket);
	}
}