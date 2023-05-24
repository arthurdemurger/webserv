/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:09:04 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/24 15:18:41 by hdony            ###   ########.fr       */
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
