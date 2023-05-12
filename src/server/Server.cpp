/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/12 12:28:23 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Server.hpp"


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Server::Server(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
	_server_sock = new ListenSocket(domain, service, protocol, port, interface, bklg);
	_server_fd = _server_sock->getServerFd();
}

Server::Server(const Server &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Server::~Server() { delete _server_sock; }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
const Server &Server::operator=(const Server &copy)
{
	if (this != &copy)
	{
		delete _server_sock;
		_server_sock = copy._server_sock;
	}
	return (*this);
}


/*
** ------------------------------- ACCESSOR --------------------------------
*/
ListenSocket	*Server::getSocket(void) const { return (_server_sock); }

/*
** ------------------------------- METHODS --------------------------------
*/
void	Server::accepter(int &clientSocket, char *buffer)
{
	struct sockaddr_in	address = _server_sock->getAddress();
	int					addressLen = sizeof(address);

	if((clientSocket = accept(_server_sock->getServerFd(), (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();
}

void	Server::handler(int &clientSocket, char *buffer) const
{
	std::cout << "'" << buffer << "'" << std::endl;
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<!doctype html><html><head><title>This is the title of the webpage!</title></head><body><p>This is an example paragraph. Anything in the <strong>body</strong> tag will appear on the page, just like this <strong>p</strong> tag and its contents.</p></body></html>";
	write(clientSocket, hello.c_str(), hello.size());
}

void	Server::launcher(void)
{
	char	buffer[BUF_SIZE];
	fd_set	read_set_cpy;
	fd_set	write_set_cpy;
	int		max_fd;
	int		tmp_sock;

	max_fd = _server_fd;

	FD_ZERO(&_read_set);
	FD_ZERO(&_write_set);
	FD_SET(_server_fd, &_read_set);
	while (true)
	{
	 	std::cout << "waiting..." << std::endl;

		read_set_cpy = _read_set;
		write_set_cpy = _write_set;

		if (select(max_fd + 1, &read_set_cpy, &write_set_cpy, NULL, NULL) < 0)
		{
			perror("select error");
			throw Server::SelectException();
		}

		for (int i = 0; i <= max_fd; i++)
		{
			if (FD_ISSET(i, &read_set_cpy))
			{
				if (i == _server_fd)
				{
					tmp_sock = i;
					accepter(tmp_sock, buffer);
					FD_SET(tmp_sock, &_read_set);
					addClient(tmp_sock);
				}
				else
				{
					_clients[i].addRequest();
					FD_CLR(i, &_read_set);
					FD_SET(i, &_write_set);
				}
			}
			else if (FD_ISSET(i, &write_set_cpy))
			{
				_clients[i].sendResponse();
			}
		}

		std::cout << "done..." << std::endl;
		close (tmp_sock);
	}
}