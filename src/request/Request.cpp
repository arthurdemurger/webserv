/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 12:27:59 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/request/Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Request::Request() { }

Request::Request(const Request &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Request::~Request(void) { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Request	&Request::operator=(const Request &copy)
{
	if (this != &copy)
	{
		_method = copy._method;
		_path = copy._path;
		_headers = copy._headers;
		_body = copy._body;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSORS --------------------------------
*/
std::string										Request::getMethod() const { return (_method); };
std::string										Request::getBody()   const { return (_body); };
std::string										Request::getPath()   const { return (_path); };
std::unordered_map<std::string, std::string>	Request::getHeaders()const { return (_headers); };

/*
** ------------------------------- METHODS --------------------------------
*/

/*	Une requête est prête à être lue dans le fd donnée en argument.
	Il faut donc récupérer toutes les infos nécessaires de la requête et les sauvegarder
	dans les différents attributs de cette classe.
*/
void	Request::parse(int fd)
{
	(void)fd;
	std::ifstream		ifs;
	std::stringstream	buffer;
	std::string			line;
	int					i;

	i = 0;
	ifs.open("request.txt");

	while (getline(ifs, line))
	{
		if (i == 0)
			parse_request_line(line);
		else if (i > 0 && !line.empty())
			parse_request_headers(line);
		else
		{
			buffer << ifs.rdbuf();
			this->_body = buffer.str();
			break;
		}
		i++;
	}
	print_request();
}

void	Request::parse_request_line(std::string &line)
{
	std::istringstream	iss(line);
	std::string			str;
	int					i;

	i = 0;
	while (getline(iss, str, ' '))
	{
		if (i == 0)
			this->_method = str;
		else if (i == 1)
			this->_path = str;
		i++;
	}
}

void	Request::parse_request_headers(std::string &line)
{
	std::istringstream	iss(line);
	std::string			key, value;
	
	while (getline(iss, key, ':'))
	{
		getline(iss, value);
		trim_value(value);
		_headers[key] = value;
	}
}

void	Request::trim_value(std::string &value)
{
	int						i;

	i = 0;
	for (std::string::iterator	it = value.begin(); it != value.end(); ++it)
	{
		if (*it == ' ')
			i++;	
	}
	value.erase(0, i);
}

void	Request::print_request()
{
	std::cout << "REQUEST LINE START\n";
	std::cout << "method: " << this->_method << std::endl;
	std::cout << "path: " << this->_path << std::endl;
	std::cout << "\n";
	std::cout << "REQUEST HEADERS START\n";
	for (std::unordered_map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}
	std::cout << "\n";
	std::cout << "REQUEST BODY START\n";
	std::cout << this->_body << std::endl;
}