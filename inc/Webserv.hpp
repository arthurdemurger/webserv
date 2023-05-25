/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:09:04 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 16:26:13 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP

#define WEBSERV_HPP

/* Some utils libraries */
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

/* Sockets headers */
// #include "server/client/Client.hpp"
#include "server/client/Request.hpp"
#include "server/client/Response.hpp"
#include "server/Config.hpp"
#include "server/Socket.hpp"
#include "parser/Parser.hpp"
// #include "Launcher.hpp"

/* Define constants */
# define PORT 8080

#endif
