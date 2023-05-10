/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 11:12:57 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDSOCKET_HPP

# define BINDSOCKET_HPP

#include "Socket.hpp"

class BindSocket : public Socket
{
	private:
		BindSocket();

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		BindSocket(const BindSocket &copy);
		BindSocket(int domain, int service, int protocol, int port, u_long interface);
		~BindSocket();

		/*
		** ------------------------------- Operator overload --------------------------------
		*/
		const BindSocket	&operator=(const BindSocket &copy);

		/*
		** ------------------------------- Methods --------------------------------
		*/
		int	connect_to_ntwk(void);
};

# endif