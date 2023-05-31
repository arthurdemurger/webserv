/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/31 14:49:11 by hdony            ###   ########.fr       */
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
std::string										Request::get_method() const { return (_method); };
std::string										Request::get_body()   const { return (_body); };
std::string										Request::get_path()   const { return (_path); };
std::map<std::string, std::string>				Request::get_headers()const { return (_headers); };
bool											Request::get_is_parsed()   const { return (_isParsed); };

/*
** ------------------------------- METHODS --------------------------------
*/

int	Request::parse(int fd, Config conf)
{
	std::stringstream	ss, buffer;
	char				buff[BUF_SIZE];
	std::string			line;
	std::string			request;
	int					i, n;

	std::cout << "2:" << conf.get_name() << std::endl;
	std::cout << "2:" << conf.get_ports().back() << std::endl;
	i = 0;
	this->_status = "200";
	fcntl(fd, F_SETFL, O_NONBLOCK);
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
	std::cout << data << std::endl;
	while (getline(ss, line))
	{
		if (i == 0)
			parse_request_line(line, conf);
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
	return (1);
}

void	Request::check_method()
{
	std::string methods[3] = {"GET", "DELETE", "POST"};
	int	i = 0;

	while (i < 3)
	{
		if (!this->_method.compare(methods[i]))
			return ;
		i++;
	}
	this->_status = "400";
}

void	Request::parse_request_line(std::string &line, Config conf)
{
	std::istringstream	iss(line);
	std::string			str;
	int					i;

	i = 0;
	while (getline(iss, str, ' '))
	{
		if (i == 0)
		{
			this->_method = str;
			check_method();
		}
		else if (i == 1)
		{
			this->_path = str;
			check_path(conf);
		}
		i++;
	}
	if (i != 3)
		this->_status = "400";
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

void	Request::check_path(Config conf)
{
	
	// std::vector<Location> _loc	= conf.get_location();
	// std::vector<Location>::iterator it = _loc.begin();
	// std::cout << "HERE:::" << it->getLocationType() << std::endl;
	// for (std::vector<Location>::iterator it = _loc.begin(); it != _loc.end(); ++it)
	// {
	// 	if (! _path.compare(it->getLocationType()))
	// 		break ;
	// }
	
	/*
	if (it != _loc.end())
	{
		append the root to the path;
		_path.append(_loc.getRoot());
		first look for the root in the location block.
		then look for the root in the server parameters 
			open file()
			set status to 200
			if fail to open -> 404
			return ;
	}
	else // no match in location block
	{
		append the root of the param server
		open the file
		set status to 200
		if fail to open -> 404
		return ;
	}*/
	
	//set status to 404;
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

