/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:41:07 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 11:36:53 by hdony            ###   ########.fr       */
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
	//insert the server object in the vector
    //from the vector build Config obj w. respective server params
    //One Server object needs one Config object 
	
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

	}
	return (*this);
}

/*
** ------------------------------- Methods --------------------------------
*/

std::string Parser::reading(std::string path)
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

/* Count the # of different server blocks in the content string */
void    Parser::server_count()
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
    // std::cout << "server nb: " << this->_server_nb << std::endl;
}

void    Parser::block_end()
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
                this->_end_block.push_back(i + 1);
            }
        }
    } 
}

/* Populate the config vector with the different server blocks */
void    Parser::split_blocks()
{
    int i;

    i = 0;
    block_end();
    while (i < this->_server_nb)
    {
        // std::cout << "block " << i << ": " << this->_content.substr(this->_vec__start_block[i], this->_vec__end_block[i]) << std::endl;
        this->_config.push_back(this->_content.substr(this->_start_block[i], this->_end_block[i]));
        i++;
    }
}