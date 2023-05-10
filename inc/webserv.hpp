/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:09:04 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 15:38:19 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP

#define WEBSERV_HPP

/* Some utils libraries */
#include <iostream>

/* Sockets headers */
#include "sockets/Socket.hpp"
#include "sockets/BindSocket.hpp"
#include "sockets/ConnectSocket.hpp"
#include "sockets/ListenSocket.hpp"

#include "server/Server.hpp"

/* Define constants */
# define PORT 8080

#endif
