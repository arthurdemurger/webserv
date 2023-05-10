/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 10:26:12 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGSOCKET_HPP

# define BINDINGSOCKET_HPP

#include "Socket.hpp"

class BindingSocket : public Socket
{
	private:
		int					serverSock;
		int					connection;
		struct sockaddr_in	address;

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		BindingSocket(int domain, int service, int protocol, int port, u_long interface);
		~BindingSocket();

		/*
		** ------------------------------- Accessors --------------------------------
		*/

		/*
		** ------------------------------- Methods --------------------------------
		*/
		virtual int	connect_to_ntwk();
};

# endif