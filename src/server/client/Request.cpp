/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/09 16:19:08 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/server/client/Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Request::Request() : _isParsed(false), _autoindex(false) { }

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
bool								Request::get_autoindex() const { return (_autoindex); };
std::string							Request::get_location() const { return (_location); };

/*
** ------------------------------- METHODS --------------------------------
*/

//trim /r/n body
void	Request::parse(int fd, Config conf)
{
	std::stringstream	ss, buffer;
	char				buff[BUF_SIZE];
	std::string			line;
	std::string			request;
	int					i, n;

	i = 0;


	this->_status = CODE_200;
	bzero(buff, BUF_SIZE);
	n = read(fd, buff, BUF_SIZE);
	std::string data(buff, n);

	std::ofstream file("request_log", std::ios::out | std::ios::app);
    if (file.is_open())
	{
		file << "********** REQUEST **********\n" << data << "********** END **********\n" << std::endl;
		file.close();
	}

	ss << data;
	while (getline(ss, line))
	{
		if (i == 0)
			parse_request_line(line, conf);
		else if (i > 0 && line.find(":") != std::string::npos)
			parse_request_headers(line);
		else
		{
			buffer << ss.rdbuf();
			this->_body = buffer.str();
			check_body_size(fd, conf);
			break;
		}
		i++;
	}
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
	this->_status = CODE_405;
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
		this->_status = CODE_400;
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
		{
			_headers[key] = value;
			// std::cout << key << _headers[key] << std::endl;
		}
	}
}

void	Request::trim_value(std::string &value)
{
	int	i = 0, j = 0;

	while (value[i])
	{
		if (value[i] == ' ' && value[i + 1] == ' ')
			j++;
		i++;
	}
	value.erase(0, j);
}

void	Request::parse_path(std::string path)
{
	std::istringstream	ss(path);
	std::string			line;
	int					c = 0;

	while(getline(ss, line, '/'))
	{
		if (c == 1)
			this->_location = line;
		else if (c == 3)
			this->_file = line;
		c++;
	}
}

std::vector<std::string> Request::check_location_file(std::string root, const std::string& path)
{
	std::vector<std::string> result;
	if (path == "/")
	{
		result.push_back("/");
		result.push_back("");
	}
	else
	{
		size_t pos = path.find('/', 1);
		if (pos != std::string::npos)
		{
			result.push_back(path.substr(0, pos));
			result.push_back(path.substr(pos + 1));
		}
		else
		{
			std::string	tmp = root + path;
			if (opendir(tmp.c_str()))
			{
				result.push_back(path);
				result.push_back("");
			}
			else
			{
				result.push_back("/");
				result.push_back(path.substr(1, path.size() - 1));
			}
		}
	}

	return result;
}

void	Request::open_file(std::string path, Config conf)
{
	std::ifstream ifs(path);
	if (ifs.fail())
	{
		_path = conf.get_root();
		this->_status = CODE_404;
	}
}

bool	Request::check_allowed_method(Location loc)
{
	std::vector<std::string>	location = loc.getAllowMethods();
	bool						flag = false;

	for (std::vector<std::string>::iterator it = location.begin(); it != location.end(); ++it)
	{
		if (!this->_method.compare(*it))
			flag = true;
	}
	return (flag);
}

void	Request::check_body_size(int fd, Config &conf)
{
	int			ret, n;
	char 		buffer[BUF_SIZE];

	if (_body.size() > conf.get_CMBS())
		this->_status = CODE_413;
	if (!_headers["Content-Length"].empty())
	{
		while (_body.size() != (ret = std::stoi(_headers["Content-Length"])))
		{
			std::string	response =  "HTTP/1.1 100 Continue";
			send(fd, response.c_str(), response.size(), 0);
			while ( (n = read(fd, buffer, BUF_SIZE)))
				_body.append(buffer);
		}
	}
}

void	Request::check_path(Config conf)
{
	std::vector<Location>			loc = conf.get_location();
	std::vector<Location>::iterator	it;
	std::string						root_path, substr = "/";
	int								c = 0, count = 0, index = 0;
	size_t							pos;

	std::vector<std::string> vec = check_location_file(conf.get_root(), _path);
	_location = vec[0];
	_file = vec[1];

	for (it = loc.begin(); it != loc.end(); ++it)
	{
		if (!_location.compare(it->getLocationType()))
		{
			// std::cout << it->getLocationType() << " | autoindex : " << it->getAutoindex() << std::endl;
			if (!check_allowed_method(*it))
			{
				this->_status = CODE_405;
				break ;
			}
			root_path = it->getRoot();
			if (_file.empty())
			{
				if (it->getAutoindex() == true)
					_autoindex = true;
				else
					_file = it->getIndex();
			}
			root_path.append(_file);
			this->_path = root_path;
			open_file(root_path, conf);
			break ;
		}
	}

	if (it == loc.end())
	{
		this->_status = CODE_404;
		this->_path = conf.get_root();
	}
}
