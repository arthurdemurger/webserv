/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 14:03:45 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP

# define SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#define SOCKET 0
#define BIND 1
#define CONNECT 2
#define LISTEN 3

class Socket
{
	protected:
		int					serverSock;
		struct sockaddr_in	address;

		Socket();
	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Socket(int domain, int service, int protocol, int port, u_long interface);
		virtual ~Socket();
		Socket(const Socket &copy);
		/*
		** ------------------------------- Operator overload --------------------------------
		*/
		const Socket	&operator=(const Socket &copy);

		/*
		** ------------------------------- Accessors --------------------------------
		*/
		int					getServerSock(void) const;
		struct sockaddr_in	getAddress(void) const;

		/*
		** ------------------------------- Methods --------------------------------
		*/
		virtual int	connect_to_ntwk() = 0;
		void		check(int itemToTest, int error);
};

# endif