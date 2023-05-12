/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/12 12:08:41 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include "../sockets/ListenSocket.hpp"
#include "netinet/in.h"
#include "../request/Client.hpp"
#include <unistd.h>
#include <map>

#define ACCEPT 0
#define READ 1
#define BUF_SIZE 30000

class Client;

class Server
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/
		ListenSocket			*_server_sock;
		int						_server_fd;
		fd_set					_read_set;
		fd_set					_write_set;
		std::map<int, Client>	_clients;
		/*
		** ------------------------------- Methods --------------------------------
		*/
		void	accepter(int &clientSocket, char *buffer);
		void	handler(int &clientSocket, char *buffer) const;
		Server();

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Server(int domain, int service, int protocol, int port, u_long interface, int bklg);
		Server(const Server &copy);
		const Server &operator=(const Server &copy);
		~Server();

		/*
		** ------------------------------- Accessor --------------------------------
		*/
		ListenSocket	*getSocket(void) const;
		/*
		** ------------------------------- Methods --------------------------------
		*/
		void	addClient(int socket);
		void	addToSet(int set, int fd);
		void	launcher();

		/*
		** ------------------------------- Exceptions --------------------------------
		*/
		class ReadException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Read failed."; };
		};
		class AcceptException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Accept failed."; };
		};
		class SelectException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Select failed."; };
		};
};

#endif