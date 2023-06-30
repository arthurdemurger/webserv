/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:41:07 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/30 16:05:49 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser/Parser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Parser::Parser() {}

Parser::Parser(std::string path)
{
	//read the config file
	this->_content = reading(path);
	//count the server blocks
	server_count();
	//split the different sever blocks in a vector of string
	split_blocks();
	//build Config object for each server block
	build_server_config();
}

Parser::Parser(const Parser &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Parser::~Parser() { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Parser &Parser::operator=(const Parser &copy)
{
	if (this != &copy)
	{
		_content = copy._content;
		_server_nb = copy._server_nb;
		_start_block = copy._start_block;
		_end_block = copy._end_block;
		_config_block = copy._config_block;
		_config = copy._config;
	}
	return (*this);
}

/*
** ------------------------------- METHODS --------------------------------
*/

std::string Parser::reading(std::string path)
{
	std::ifstream ifs(path);
	if (ifs.fail())
		exit (EXIT_FAILURE);
	std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	return (content);
}

/* Count the # of different server blocks in the content string */
void	Parser::server_count()
{
	std::size_t pos;
	std::string substr = "server {";
	this->_server_nb = 0;

	pos = 0;
	while ((pos = this->_content.find(substr, pos)) != std::string::npos)
	{
		this->_start_block.push_back(pos);
		pos += substr.length();
		this->_server_nb++;
	}
	if (this->_server_nb == 0)
	{
		std::cout << "Error: no server block in config. file\n";
		exit(EXIT_FAILURE);
	}
}

void	Parser::block_end()
{
	int i;

	i = -1;
	while (this->_content[++i])
	{
		if (this->_content[i] == '}')
		{
			if ((int)this->_content[i - 1] == 10)
			{
				this->_end_block.push_back(i + 1);
			}
		}
	}
}

/* Populate the config vector with the different server blocks */
void	Parser::split_blocks()
{
	int i;

	i = 0;
	block_end();
	while (i < this->_server_nb)
	{
		this->_config_block.push_back(this->_content.substr(this->_start_block[i], this->_end_block[i]));
		i++;
	}
}

/* Populate the config vector with the different server param */
std::vector<Config>   Parser::build_server_config()
{
	int i;

	i = 0;
	while (i < this->_server_nb)
	{
		this->_config.push_back(Config((this->_config_block[i])));
		i++;
	}
	return (this->_config);
}

/*
** ------------------------------- ACCESSOR --------------------------------
*/

const std::vector<Config> Parser::getConfig() const { return (this->_config); }
