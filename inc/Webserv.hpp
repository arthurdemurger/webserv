/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:09:04 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/30 14:21:18 by hdony            ###   ########.fr       */
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
// #include "server/client/Request.hpp"
// #include "server/client/Response.hpp"
// #include "server/Config.hpp"
// #include "server/Socket.hpp"
// #include "parser/Parser.hpp"
// #include "Launcher.hpp"

/* Define constants */
# define BUF_SIZE		30000
# define RESET			"\x1B[0m"
# define RED			"\x1B[31m"
# define LIGHT_RED		"\x1B[91m"
# define WHITE			"\x1B[37m"
# define BLINK			"\x1b[5m"
# define YELLOW			"\x1B[33m"
# define LIGHT_BLUE		"\x1B[94m"
# define CYAN			"\x1B[36m"
# define DARK_GREY		"\x1B[90m"
# define LIGHTMAGENTA	"\x1B[95m"

#endif
