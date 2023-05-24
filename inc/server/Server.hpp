/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/24 12:02:13 by ademurge         ###   ########.fr       */
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

#define RESET          "\x1B[0m"
#define RED            "\x1B[31m"
#define LIGHT_RED      "\x1B[91m"
#define WHITE          "\x1B[37m"
#define BLINK           "\x1b[5m"
#define YELLOW         "\x1B[33m"
#define LIGHT_BLUE     "\x1B[94m"
#define CYAN           "\x1B[36m"
#define DARK_GREY      "\x1B[90m"
#define LIGHTMAGENTA   "\x1B[95m"

class Client;

class Server
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/
		ListenSocket			*_server_sock;
		int						_server_fd;
		int						_max_fd;
		fd_set					_read_set;
		fd_set					_write_set;
		std::map<int, Client>	_clients;
		/*
		** ------------------------------- Methods --------------------------------
		*/
		void	accepter();

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
				virtual const char *what() const throw()
				{
					perror("read");
					return ("Server closed because of an error");
				};
		};
		class AcceptException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("accept");
					return ("Server closed because of an error");
				};
		};
		class SelectException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("select");
					return ("Server closed because of an error");
				};
		};
		class FcntlException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("fcntl");
					return ("Server closed because of an error");
				};
		};
};

#endif