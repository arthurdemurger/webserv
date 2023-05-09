/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/09 15:48:28 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"

Socket::Socket(int domain, int service, int protocol, int port,  u_long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

	// Establish connection
	server_sock = socket(domain, service , protocol);

	// Bind
}

Socket::~Socket() { }


void		Socket::test_connection();
