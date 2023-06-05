/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/05 12:41:09 by ademurge         ###   ########.fr       */
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

void	Request::parse(int fd, Config conf)
{
	std::stringstream	ss, buffer;
	char				buff[BUF_SIZE];
	std::string			line;
	std::string			request;
	int					i, n;

	i = 0;
	this->_status = "200";
	n = read(fd, buff, BUF_SIZE);
	std::string data(buff, n);
	while (n > 0)
	{
		n = read(fd, buff, BUF_SIZE);
		data += buff;
	}

	ss << data;
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
	// print_request();
	_isParsed = true;
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

void	Request::parse_path(std::string path)
{
	std::istringstream	ss(path);
	std::string			line;
	int					c = 0;

	while(getline(ss, line, '/'))
	{
		std::cout << "line: " << line << std::endl;
		if (c == 1)
			this->_location = line;
		else if (c == 3)
			this->_file = line;
		c++;
	}
}

void	Request::parse_styles(Config conf)
{
	if (_path.find("style") != std::string::npos)
	{
		_path = conf.get_root() + "styles.css";
		this->_status = "200";
	}
	else
	{
		_path = conf.get_root();
		this->_status = "404";
	}
}

void	Request::check_location_file()
{
	std::istringstream	iss(_path);
	std::string			line;
	int					c = 0;

	while (getline(iss, line, '/')) {
		if (c == 1)
			this->_location = line;
		else if (c == 2)
			this->_file = line;
		c++;
	}
}

void	Request::open_file(std::string path, Config conf)
{
	std::ifstream ifs(path);
	if (ifs.fail())
	{
		std::cerr << "Error: " << strerror(errno) << " | path : " << path << std::endl;
		parse_styles(conf);
	}
}

void	Request::check_path(Config conf)
{
	std::vector<Location>			_loc = conf.get_location();
	std::vector<Location>::iterator	it;
	std::string						root_path, substr = "/";
	int								c = 0, count = 0, index = 0;
	size_t							pos;

	std::cout << "_path: " << _path << std::endl;
	this->_status = "200";
	check_location_file();
    while ((index = _path.find(substr, index)) != std::string::npos) {
        index += substr.length();
		count++;
    }
	if (count > 1)
	{
		_location.insert(0, "/");
		for (it = _loc.begin(); it != _loc.end(); ++it)
		{
			if (!_location.compare(it->getLocationType()))
			{
				root_path = it->getRoot();
				if (_file.empty())
					_file = it->getIndex();
				root_path.append(_file);
				this->_path = root_path;
				std::cout << "updated_path: " << _path << std::endl;
				open_file(root_path, conf);
				break ;
			}
		}
		if (it == _loc.end())
			parse_styles(conf);
	}
	else
	{
		if (!_path.compare("/"))
		{
			_path.erase(0, 1);
			_path.append(conf.get_root().append(conf.get_index()));
		}
		else
		{
			if (((pos = _path.find("/")) != std::string::npos) && !pos)
				_path.erase(0, 1);
			root_path = conf.get_root();
			root_path.append(_path);
			_path = root_path;
		}
		std::cout << "updated_path: " << _path << std::endl;
		open_file(_path, conf);
	}
}
