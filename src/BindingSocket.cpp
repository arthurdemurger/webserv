/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 10:25:57 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BindingSocket.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) : Socket(domain, service, protocol, port, interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

	// Establish connection
	check((serverSock = socket(domain, service , protocol)), "socket failed.");
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
BindingSocket::~BindingSocket() { }

/*
** ------------------------------- ACCESSORS --------------------------------
*/

/*
** ------------------------------- METHODS --------------------------------
*/

