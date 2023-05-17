/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/17 14:10:25 by ademurge         ###   ########.fr       */
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
void	Server::changeSet(int fd, fd_set &dest_set, fd_set &src_set)
{
	FD_CLR(fd, &src_set);
	FD_SET(fd, &dest_set);
}

void	Server::accepter(int &max_fd)
{
	int					new_socket;
	struct sockaddr_in	address = _server_sock->getAddress();
	int					addressLen = sizeof(address);

	if((new_socket = accept(_server_sock->getServerFd(), (struct sockaddr *)&address, (socklen_t *) &addressLen)) < 0)
		throw Server::AcceptException();
	// fcntl(new_socket, F_SETFL, O_NONBLOCK);
	if (_clients.count(new_socket) != 0)
		_clients.erase(new_socket);
	_clients.insert(std::pair<int, Client>(new_socket, Client()));
	_clients[new_socket].setSocket(new_socket);
	if (new_socket > max_fd)
		max_fd = new_socket;
	FD_SET(new_socket, &_read_set);
}

/* Public Methods */

void	Server::launcher(void)
{
	struct timeval	timeout;
	char	buffer[BUF_SIZE];
	fd_set	read_set_cpy;
	fd_set	write_set_cpy;
	int		max_fd;

	max_fd = _server_fd;

	FD_ZERO(&_read_set);
	FD_ZERO(&_write_set);
	FD_SET(_server_fd, &_read_set);
	while (true)
	{
		std::cout << "########## WAITING ##########" << std::endl;

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		read_set_cpy = _read_set;
		write_set_cpy = _write_set;

		if (select(max_fd + 1, &read_set_cpy, &write_set_cpy, NULL, NULL) < 0)
		{
			perror("select error");
			throw Server::SelectException();
		}

		for (int i = 1; i <= max_fd; ++i)
		{
			if (FD_ISSET(i, &read_set_cpy))
			{
				if (i == _server_fd)
				{
					std::cout << "1" << std::endl;
					accepter(max_fd);
				}
				else if (_clients.count(i))
				{
					std::cout << "2" << std::endl;
					_clients[i].addRequest();
					changeSet(i, _write_set, _read_set);
				}
			}
			else if (FD_ISSET(i, &write_set_cpy) && _clients.count(i))
			{
				std::cout << "3" << std::endl;
				_clients[i].sendResponse();
				// FD_CLR(i, &_read_set);
				// FD_CLR(i, &_write_set);
				// close(i);
				changeSet(i, _read_set, _write_set);
			}
		}
		std::cout << "########## DONE    ##########" << std::endl << std::endl;
	}
}
