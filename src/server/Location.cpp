/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:24:10 by hdony             #+#    #+#             */
/*   Updated: 2023/06/30 16:16:54 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Location.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Location::Location() {}

Location::Location(std::string LocationBlock, std::string LocationType)
{
	setLocType(LocationType);
	std::istringstream  iss(LocationBlock);
	std::string		 line;
	while (getline(iss, line))
	{
		RemoveTab(line);
		std::istringstream iss_line(line);
		std::string key, value;
		getline(iss_line, key, ' ');
		getline(iss_line, value, ';');
		if (!key.compare("root"))
			this->_root = value;
		else if (!key.compare("autoindex"))
		{
			if(!value.compare("on"))
				this->_autoindex = true;
			else
				this->_autoindex = false;
		}
		else if (!key.compare("allow_methods"))
			setAllowMethods(value);
		else if (!key.compare("index"))
			this->_index = value;
		else if (!key.compare("return"))
			this->_return = value;
		else if (!key.compare("alias"))
			this->_alias = value;
	}
}

Location::Location(const Location &rhs)
{
	*this = rhs;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Location::~Location() {}

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Location	&Location::operator=(const Location &rhs)
{
	if (this != &rhs)
	{
		this->_location_type = rhs._location_type;
		this->_root = rhs._root;
		this->_autoindex = rhs._autoindex;
		this->_allow_methods = rhs._allow_methods;
		this->_index = rhs._index;
		this->_return = rhs._return;
		this->_alias = rhs._alias;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSORS --------------------------------
*/

void	Location::setLocType(std::string &LocationType)
{
	std::istringstream  iss(LocationType);
	std::string		 line;

	getline(iss, line, ' ');
	this->_location_type = line;
}

void	Location::setAllowMethods(std::string &value)
{
	std::istringstream iss(value);
	std::string token;

	while (getline(iss, token, ' '))
	{
		this->_allow_methods.push_back(token);
	}
}

std::string &Location::getLocationType() {	return (this->_location_type); }
std::string &Location::getRoot() {	return (this->_root); }
bool	&Location::getAutoindex() {	return (this->_autoindex); }
std::vector<std::string>	&Location::getAllowMethods() {	return (this->_allow_methods); }
std::string &Location::getIndex() {	return (this->_index); }
std::string &Location::getReturn() { return (this->_return); }
std::string &Location::getAlias() {	return (this->_alias); }