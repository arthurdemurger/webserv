/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:32:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 17:02:25 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Config.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Config::Config() {}

Config::Config(std::string path)
{
	
	//read the config file
	//count the server blocks
	//split the different sever blocks in a vector of string
	//the servers are already in map so loop through map
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