/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/30 14:52:28 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/server/client/Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Request::Request() : _isParsed(false) { }

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
std::string							Request::get_method() const { return (_method); };
std::string							Request::get_body() const { return (_body); };
std::string							Request::get_path() const { return (_path); };
std::string							Request::get_status() const { return (_status); };
std::map<std::string, std::string>	Request::get_headers() const { return (_headers); };
bool								Request::get_is_parsed() const { return (_isParsed); };

/*
** ------------------------------- METHODS --------------------------------
*/

int	Request::parse(int fd)
{
	std::stringstream	ss, buffer;
	char				buff[BUF_SIZE];
	std::string			line;
	std::string			request;
	int					i, n;

	i = 0;
	n = read(fd, buff, BUF_SIZE);
	std::string data(buff, n);
	while (n > 0)
	{
		n = read(fd, buff, BUF_SIZE);
		data += buff;
	}
	if (!n)
		return (0);
	ss << data;
	while (getline(ss, line))
	{
		if (i == 0)
			parse_request_line(line);
		else if (i > 0 && !line.empty())
			parse_request_headers(line);
		else
		{
			buffer << ss.rdbuf();
			this->_body = buffer.str();
			break;
		}
		i++;
	}
	_isParsed = true;
	// print_request();
	return (1);
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
		if (!key.empty() && !value.empty())
			_headers[key] = value;
	}
}

void	Request::trim_value(std::string &value)
{
	int	i;

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
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}
	std::cout << "\n";
	std::cout << "REQUEST BODY START\n";
	std::cout << this->_body << std::endl;
}
