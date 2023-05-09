/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/09 15:48:27 by ademurge         ###   ########.fr       */
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
		int					server_sock;
		int					connection;
		struct sockaddr_in	address;

	public:
		Socket(int domain, int service, int protocol, int port, u_long interface);

		virtual int	connect_to_ntwk() = 0;
		void		test_connection();
		~Socket();
};

# endif