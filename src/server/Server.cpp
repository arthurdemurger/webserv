/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 11:10:48 by ademurge         ###   ########.fr       */
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
	std::cout << YELLOW << "Accept new connection | socket : " << new_socket << RESET << std::endl;

	FD_SET(new_socket, &_read_set);
	FD_SET(new_socket, &_write_set);


	if (new_socket > max_fd)
		max_fd = new_socket;

	if (_clients.count(new_socket) != 0)
		_clients.erase(new_socket);
	_clients.insert(std::pair<int, Client>(new_socket, Client()));
	_clients[new_socket].setSocket(new_socket);
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

		read_set_cpy = _read_set;
		write_set_cpy = _write_set;

		if (select(max_fd + 1, &read_set_cpy, &write_set_cpy, NULL, NULL) < 0)
		{
			perror("select error");
			close (_server_fd);
			throw Server::SelectException();
		}

		if (FD_ISSET(_server_fd, &read_set_cpy))
			accepter(max_fd);

		for (int i = 0; i < _clients.size(); ++i)
		{
			int	sock = _clients[i].getSocket();

			if (FD_ISSET(sock, &read_set_cpy))
			{
					std::cout << RED << "Read request [socket " << sock << "]" << RESET << std::endl;
					if (!_clients[sock].addRequest())
					{
						close(sock);
						FD_CLR(sock, &_read_set);
						FD_CLR(sock, &_write_set);
						_clients.erase(sock);
						--i;
					}
					FD_SET(sock, &_write_set);
			}
			if (FD_ISSET(sock, &write_set_cpy))
			{
				_clients[sock].sendResponse();
				std::cout << CYAN << "response sent [socket " << sock << "]" << RESET << std::endl;

				close(sock);
				FD_CLR(sock, &_read_set);
				FD_CLR(sock, &_write_set);
				_clients.erase(sock);
				std::cout << LIGHTMAGENTA << "connection removed [socket " << sock << "]" << RESET << std::endl;
			}
		}
		std::cout << "########## DONE    ##########" << std::endl << std::endl;
	}
}
