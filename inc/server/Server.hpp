/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/17 12:00:13 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include "../sockets/ListenSocket.hpp"
#include "netinet/in.h"
#include "../request/Client.hpp"
#include <unistd.h>
#include <map>
#include <fcntl.h>

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
		void	accepter(int &max_fd);
		void	changeSet(int fd, fd_set &dest_set, fd_set &src_set);

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