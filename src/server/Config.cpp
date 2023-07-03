/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:32:53 by ademurge          #+#    #+#             */
/*   Updated: 2023/07/03 13:49:55 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Config.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Config::Config() {}

Config::Config(std::string server_block)
{
	std::istringstream iss(server_block);
	std::string line;
	getline(iss, line);
	while (getline(iss, line))
	{
		std::istringstream iss_line(line);
		std::string key, value, location;
		getline(iss_line, key, ' ');
		RemoveTab(key);
		getline(iss_line, value, ';');
		setter(key, value, iss, location);
	}
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
Config &Config::operator=(const Config &rhs)
{
	 if (this != &rhs)
	{
		this->_port = rhs._port;
		this->_host = rhs._host;
		this->_allow_methods = rhs._allow_methods;
		this->_server_name = rhs._server_name;
		this->_error_page = rhs._error_page;
		this->_client_max_body_size = rhs._client_max_body_size;
		this->_root = rhs._root;
		this->_index = rhs._index;
		this->_location = rhs._location;
	}
	return (*this);
}


/*
** ------------------------------- METHODS --------------------------------
*/

void	Config::setter(std::string &key, std::string &value, std::istringstream &iss, std::string &location)
{
	if (!key.compare("listen"))
		setPortMBS(key, value);
	else if (!key.compare("host"))
		setHostDir(value);
	else if (!key.compare("server_name"))
		setServerNameDir(value);
	else if (!key.compare("error_page"))
		setErrorPageDir(value);
	else if (!key.compare("client_max_body_size"))
		setPortMBS(key, value);
	else if (!key.compare("root"))
		this->_root = value;
	else if (!key.compare("index"))
		this->_index = value;
	else if (!key.compare("location"))
	{
		getline(iss, location, '}');
		this->_location.push_back(Location(location, value));
	}
}

void	Config::setPortMBS(std::string &key, std::string &value)
{
	size_t i, port;

	i = 0;
	while (isdigit(value[i]))
	{
		i++;
	}
	if (i != value.length())
	{
		std::cout << "Error: listen directive format\n";
		exit(EXIT_FAILURE);
	}
	if (!key.compare("listen"))
	{
		port = atoi(value.c_str());
		this->_port.push_back(port);
	}
	else
		this->_client_max_body_size = atoi(value.c_str());
}

void	Config::setHostDir(std::string &value)
{

	std::istringstream iss(value);
	std::string token;
	int i, count, ret;

	count = 0;
	if ( (ret = value.find(".") != std::string::npos) )
	{
		while (getline(iss, token, '.'))
		{
			for (std::string::iterator it = token.begin(); it != token.end(); ++it)
			{
				if (!isdigit(*it))
				{
					std::cout << "Error: Host Directive format\n";
					exit(EXIT_FAILURE);
				}
			}
			i = atoi(value.c_str());
			if (i < 0 || i > 255 )
			{
				std::cout << "Error: Host Directive format\n";
				exit(EXIT_FAILURE);
			}
			count++;
		}
		if (count != 4)
		{
			std::cout << "Error: Host Directive format\n";
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (value.compare("localhost") != 0)
		{
			std::cout << "Error: Host Directive format\n";
			exit(EXIT_FAILURE);
		}
	}
	this->_host = value;
}

void	Config::setServerNameDir(std::string &value)
{
	std::istringstream iss(value);
	std::string token;

	while (getline(iss, token, ' '))
	{
		this->_server_name.push_back(token);
	}
	if (token.empty())
	{
		this->_server_name.push_back("default name");
	}
}

void	Config::setErrorPageDir(std::string &value)
{
	std::istringstream iss(value);
	std::string token;
	int		 key;
	std::string val;
	int i = 1;

	while (getline(iss, token, ' '))
	{
		if (!(i % 2))
			val = token;
		else
			key = atoi (token.c_str());
		i++;
	}
	this->_error_page.insert(std::pair<int, std::string>(key, val));
}

std::string					Config::get_name(void) const { return (_server_name[0]); }
std::vector<int>			Config::get_ports(void) const { return (_port); }
std::vector<Location>		Config::get_location(void) const { return (_location); }
std::string					Config::get_root(void) const { return (_root); }
std::string					Config::get_index(void) const { return (_index); }
std::string					Config::get_host(void) const { return (_host); }
int							Config::get_CMBS(void) const { return (_client_max_body_size); }
std::map<int, std::string>	Config::get_error_pages(void) const { return (_error_page); };