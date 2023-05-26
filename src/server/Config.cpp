/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:32:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 12:20:35 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Config.hpp"
#include "../../inc/Webserv.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Config::Config() {}

Config::Config(std::string server_block)
{
	//parse the config file
	std::istringstream iss(server_block);
    std::string line;
    getline(iss, line);
    // while (getline(iss, line))
    // {
    //     std::istringstream iss_line(line);
    //     std::string key, value, location;
    //     getline(iss_line, key, ' ');
    //     RemoveTab(key);
    //     getline(iss_line, value, ';');
    //     setter(key, value, iss, location);
    // }
    // PrintServer();
	// populate server value
}

Config::Config(const Config &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Config::~Config() { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Config &Config::operator=(const Config &copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}