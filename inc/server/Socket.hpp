/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/24 16:08:56 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP

# define SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define SOCKET 0
#define BIND 1
#define CONNECT 2
#define LISTEN 3

class Socket
{
	private:
		int					_server_fd;
		struct sockaddr_in	_address;
		int					_backlog;

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Socket(int domain, int service, int protocol, int port, u_long interface, int backlog);
		Socket();
		~Socket();
		Socket(const Socket &copy);

		/*
		** ------------------------------- Operator overload --------------------------------
		*/
		const Socket	&operator=(const Socket &copy);

		/*
		** ------------------------------- Accessors --------------------------------
		*/
		int					getServerFd(void) const;
		struct sockaddr_in	getAddress(void) const;

		/*
		** ------------------------------- Exceptions --------------------------------
		*/
		class SocketException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Socket failed."; };
		};
		class BindException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Bind failed."; };
		};
		class ListenException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Listen failed."; };
		};
		class FcntlException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "fcntl failed."; };
		};

};

# endif