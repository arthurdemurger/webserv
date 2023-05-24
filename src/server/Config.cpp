/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:19:59 by hdony             #+#    #+#             */
/*   Updated: 2023/05/10 13:42:51 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing/Parsing.hpp"

Config::Config() {}

Config::Config(const Config &rhs)
{
	*this = rhs;
}

Config  &Config::operator=(const Config &rhs)
{
	if (this != &rhs)
	{
		this->_content = rhs._content;
		this->_server_nb = rhs._server_nb;
		this->_vec_start_block = rhs._vec_start_block;
		this->_vec_end_block = rhs._vec_end_block;
		this->_vec_config = rhs._vec_config;
		this->_vec_server = rhs._vec_server;
	}
	return (*this);
}

Config::~Config() {}

const   std::vector<std::string> &Config::getVecServConf() const
{
	return (this->_vec_config);
}

const int   &Config::getServerNb() const
{
	return (this->_server_nb);
}

/* Populate the server vector based on each respective server block  */
void	Config::PopulateServer()
{
	int i;

	i = 0;
	while (i < this->_server_nb)
	{
		this->_vec_server.push_back(Server(this->_vec_config[i]));
		i++;
	}
}

void	Config::ServerBlockEnd()
{
	int i;

	i = -1;
	while (this->_content[++i])
	{
		if (this->_content[i] == '}')
		{
			if ((int)this->_content[i - 1] == 10)
			{
				// std::cout << "block end: " << i << std::endl;
				this->_vec_end_block.push_back(i + 1);
			}
		}
	}
}

/* Populate the config vector with the different server blocks */
void	Config::PopulateVecConfig()
{
	int i;

	i = 0;
	ServerBlockEnd();
	while (i < this->_server_nb)
	{
		// std::cout << "block " << i << ": " << this->_content.substr(this->_vec_start_block[i], this->_vec_end_block[i]) << std::endl;
		this->_vec_config.push_back(this->_content.substr(this->_vec_start_block[i], this->_vec_end_block[i]));
		i++;
	}
}

/* Count the # of different server blocks in the content string */
void	Config::ServerCount()
{
	std::size_t pos;
	std::string substr = "server {";
	this->_server_nb = 0;

	pos = 0;
	while ((pos = this->_content.find(substr, pos)) != std::string::npos)
	{
		this->_vec_start_block.push_back(pos);
		pos += substr.length();
		this->_server_nb++;
	}
	if (this->_server_nb == 0)
	{
		std::cout << "Error: no server block in config. file\n";
		exit(EXIT_FAILURE);
	}
	// std::cout << "server nb: " << this->_server_nb << std::endl;
}

/* Read the whole config file into the string content */
std::string Config::ConfigReading(std::string &path)
{
	std::ifstream ifs(path);
	if (ifs.fail())
	{
		std::cout << "Error: open file\n";
		exit (EXIT_FAILURE);
	}
	std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	// std::cout << "content: " << content << std::endl;
	return (content);
}

void	Config::ConfigParsing(std::string path)
{
	this->_content = ConfigReading(path);
	ServerCount();
	PopulateVecConfig();
	PopulateServer();
}