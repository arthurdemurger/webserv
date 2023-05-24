/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:59:13 by hdony             #+#    #+#             */
/*   Updated: 2023/05/24 15:32:52 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing/Parsing.hpp"

Location::Location(std::string LocationBlock, std::string LocationType)
{
	// std::cout << "LocationBlock: " << LocationBlock << std::endl;
	setLocType(LocationType);
	std::istringstream  iss(LocationBlock);
	std::string		 line;
	while (getline(iss, line))
	{
		// std::cout << "line: " << line << std::endl;
		RemoveTab(line);
		std::istringstream iss_line(line);
		std::string key, value;
		getline(iss_line, key, ' ');
		// std::cout << "key: " << key << std::endl;
		getline(iss_line, value, ';');
		// std::cout << "value: " << value << std::endl;
		if (!key.compare("root"))
			this->_root = value;
		else if (!key.compare("autoindex"))
		{
			if(!value.compare("on"))
				this->_autoindex = true;
			else
				this->_autoindex = false;
			// std::cout << "autoindex: " << _autoindex << std::endl;
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

Location::~Location() {}

void	Location::setLocType(std::string &LocationType)
{
	std::istringstream  iss(LocationType);
	std::string		 line;

	getline(iss, line, ' ');
	this->_location_type = line;
	// std::cout << "location type: " << _location_type << std::endl;
}

void	Location::setAllowMethods(std::string &value)
{
	std::istringstream iss(value);
	std::string token;

	while (getline(iss, token, ' '))
	{
		this->_allow_methods.push_back(token);
		// std::cout << "token: " << token << std::endl;
	}
}

std::string &Location::getLocationType()
{
	return (this->_location_type);
}

std::string &Location::getRoot()
{
	return (this->_root);
}

bool	&Location::getAutoindex()
{
	return (this->_autoindex);
}

std::vector<std::string>	&Location::getAllowMethods()
{
	return (this->_allow_methods);
}

std::string &Location::getIndex()
{
	return (this->_index);
}

std::string &Location::getReturn()
{
	return (this->_return);
}

std::string &Location::getAlias()
{
	return (this->_alias);
}