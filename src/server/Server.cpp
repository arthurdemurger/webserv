/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 16:26:56 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Server::Server()
{

}

Server::Server(const Server &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Server::~Server() { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Server &Server::operator=(const Server &copy)
{
	if (this != &copy)
	{
		_socket = copy._socket;
		_serv_fd = copy._serv_fd;
		_read_set = copy._read_set;
		_write_set = copy._write_set;
		_config = copy._config;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSOR --------------------------------
*/
Config					Server::get_config(void) const { return (_config); }
int						Server::get_fd(void) const { return (_serv_fd); }
std::string				Server::get_name(void) const { return (_name); }
std::vector<int>		Server::get_read_set(void) const { return (_read_set); }
Socket					Server::get_socket(void) const { return (_socket); }
std::vector<int>		Server::get_write_set(void) const { return (_write_set); }

/*
** ------------------------------- METHODS --------------------------------
*/

/* Private Methods */


/* Public Methods */

void	Server::launcher(void)
{
	char	buffer[BUF_SIZE];
	fd_set	read_set_cpy;
	fd_set	write_set_cpy;

	// set the fd_sets for reading and writing sockets
	FD_ZERO(&_read_set);
	FD_ZERO(&_write_set);
	FD_SET(_server_fd, &_read_set);

	/* The main loop that runs continuously to the user uses ^C */
	while (true)
	{
		std::cout << "########## WAITING ##########" << std::endl;

		read_set_cpy = _read_set;
		write_set_cpy = _write_set;

		/* Launch the select and check its status. We use two fd_set, one for reading and one for writing */
		if (select(_max_fd + 1, &read_set_cpy, &write_set_cpy, NULL, NULL) < 0)
		{
			perror("select error");
			close (_server_fd);
			throw Server::SelectException();
		}

		/* If there is activity on the server socket, then there is a new connection to the server.
			So we add it to the clients map and use the accept() system function */
		if (FD_ISSET(_server_fd, &read_set_cpy))
			accepter(max_fd);
		std::cout << "1\n";
		/* We loop on all client sockets and check their activity */
		for (int i = 0; i < _clients.size(); ++i)
		{
			int	sock = _clients[i].getSocket();

			/* We check the activity on the read_set.
				if there is some, we recover the request and we change the fd_set of the client socket */
			if (FD_ISSET(sock, &read_set_cpy))
			{
					std::cout << RED << "Read request [socket " << sock << "]" << RESET << std::endl;
					FD_SET(sock, &_write_set);
					if (!_clients[sock].addRequest())
					{
						std::cout << RED << "didn't read anything [socket " << sock << "]" << RESET << std::endl;
						close(sock);
						FD_CLR(sock, &_read_set);
						FD_CLR(sock, &_write_set);
						_clients.erase(sock);
						--i;
					}
			}

			/* We check the write_set.
				If we can write, then we send the answer to the request, then we close the connection. */
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
