/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:09:04 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/24 17:43:23 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP

#define WEBSERV_HPP

/* Some utils libraries */

/* Sockets headers */
#include "server/client/Client.hpp"
#include "server/client/Request.hpp"
#include "server/client/Response.hpp"
#include "server/Config.hpp"
#include "server/Server.hpp"
#include "server/Socket.hpp"
#include "parser/Parser.hpp"
#include "Launcher.hpp"

/* Define constants */
# define PORT 80

#endif
