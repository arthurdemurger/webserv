/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:23 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/24 17:41:59 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_HPP

#define LAUNCHER_HPP

#include <map>
#include <vector>
#include <iostream>
#include "server/Server.hpp"
#include "parser/Parser.hpp"

class Server;
class Parser;

class Launcher
{
	private:
		Parser							_parser;
		std::map<std::string, Server>	_servers;
		std::vector<int>				_serv_socks;
		std::vector<int>				_read_pool;
		std::vector<int>				_write_pool;

	public:
		Launcher(void);
		~Launcher(void);
};

#endif // LAUNCHER_HPP