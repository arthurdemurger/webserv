/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/09 16:59:58 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP

# define SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket
{
	private:
		int					serverSock;
		int					connection;
		struct sockaddr_in	address;

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Socket(int domain, int service, int protocol, int port, u_long interface);
		~Socket();

		/*
		** ------------------------------- Accessors --------------------------------
		*/
		int					getServerSock(void) const;
		int					getConnection(void) const;
		struct sockaddr_in	getAddress(void) const;

		/*
		** ------------------------------- Methods --------------------------------
		*/
		virtual int	connect_to_ntwk() = 0;
		void		check(int item, char *message);
};

# endif