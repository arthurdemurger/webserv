/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 15:15:11 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP

# define SOCKET_HPP

#include "../Webserv.hpp"

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
		Socket();
		~Socket();
		Socket(const Socket &copy);

		int		create_socket(int port, u_long interface, int backlog);
		/*
		** ------------------------------- Operator overload --------------------------------
		*/
		const Socket	&operator=(const Socket &copy);

		/*
		** ------------------------------- Accessors --------------------------------
		*/
		int					getServerFd(void) const;
		struct sockaddr_in	getAddress(void) const;
};

# endif