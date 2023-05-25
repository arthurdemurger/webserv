/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:32:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 16:14:23 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Config.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Config::Config()
{

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