/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 11:21:24 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTSOCKET_HPP

# define CONNECTSOCKET_HPP

#include "Socket.hpp"

class ConnectSocket : public Socket
{
	private:
		ConnectSocket();
	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		ConnectSocket(const ConnectSocket &copy);
		ConnectSocket(int domain, int service, int protocol, int port, u_long interface);
		~ConnectSocket();

		/*
		** ------------------------------- Operator overload --------------------------------
		*/
		const ConnectSocket	&operator=(const ConnectSocket &copy);

		/*
		** ------------------------------- Methods --------------------------------
		*/
		int	connect_to_ntwk(void);
};

# endif