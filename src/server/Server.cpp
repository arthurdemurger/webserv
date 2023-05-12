/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/12 15:20:38 by ademurge         ###   ########.fr       */
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

/* Private Methods */

void	Server::addClient(int socket, int &max_fd)
{
	_clients.insert(std::pair<int, Client>(socket, Client()));
	_clients[socket].setSocket(socket);
	if (socket > max_fd)
		max_fd = socket;
}

void	Server::changeSet(int fd, fd_set &dest_set, fd_set &src_set)
{
	FD_CLR(fd, &src_set);
	FD_SET(fd, &dest_set);
}

int	Server::accepter(void)
{
	int					clientSocket;
	struct sockaddr_in	address = _server_sock->getAddress();
	int					addressLen = sizeof(address);

	if((clientSocket = accept(_server_sock->getServerFd(), (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();
	return (clientSocket);
}

/* Public Methods */

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
	 	std::cout << "########## WAITING ##########" << std::endl;

		read_set_cpy = _read_set;
		write_set_cpy = _write_set;

		if (select(max_fd + 1, &read_set_cpy, &write_set_cpy, NULL, NULL) < 0)
		{
			perror("select error");
			throw Server::SelectException();
		}

		for (int i = 0; i <= max_fd; ++i)
		{
			if (FD_ISSET(i, &read_set_cpy))
			{
				if (i == _server_fd)
				{
					std::cout << "1" << std::endl;
					tmp_sock = accepter();
					FD_SET(tmp_sock, &_read_set);
					addClient(tmp_sock, max_fd);
				}
				else
				{
					std::cout << "2" << std::endl;
					_clients[i].addRequest();
					changeSet(i, _write_set, _read_set);
				}
			}
			else if (FD_ISSET(i, &write_set_cpy))
			{
				std::cout << "3" << std::endl;
				_clients[i].sendResponse();
				changeSet(i, _read_set, _write_set);
			}
		}
		std::cout << "########## DONE    ##########" << std::endl << std::endl;
	}
}
