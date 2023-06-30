/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/30 16:26:00 by hdony            ###   ########.fr       */
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
		_status = copy._status;
		_path = copy._path;
		_raw_path = copy._raw_path;
		_host = copy._host;
		_headers = copy._headers;
		_body = copy._body;
		_isParsed = copy._isParsed;
		_isChunked = copy._isChunked;
		_location = copy._location;
		_file = copy._file;
		_autoindex = copy._autoindex;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSORS --------------------------------
*/
std::string							Request::get_method() const { return (_method); };
std::string							Request::get_body() const { return (_body); };
std::string							Request::get_path() const { return (_path); };
std::string							Request::get_raw_path() const { return (_raw_path); };
std::string							Request::get_status() const { return (_status); };
std::map<std::string, std::string>	Request::get_headers() const { return (_headers); };
bool								Request::get_is_parsed() const { return (_isParsed); };
bool								Request::get_autoindex() const { return (_autoindex); };
std::string							Request::get_location() const { return (_location); };

void								Request::set_body(std::string body) { _body = body; };
void								Request::set_status(std::string status) { _status = status; };

/*
** ------------------------------- METHODS --------------------------------
*/

int	Request::parse(int fd, Config conf)
{
	std::stringstream	ss, buffer;
	char				buff[BUF_SIZE + 1];
	std::string			line;
	std::string			request;
	int					i = 0;
	int				n = 0;
	this->_isChunked = false;
	this->_status = CODE_200;
	bzero(buff, BUF_SIZE);
	std::string data;

	n = read(fd, buff, BUF_SIZE);
	if (n < 0)
		return (-1);
	data.append(buff);
	while (n == BUF_SIZE)
	{
		n = read(fd, buff, BUF_SIZE);
		data.append(buff);
	}
	if (n < 0)
		return (-1);


	// std::ofstream file("request_log", std::ios::out | std::ios::app);
	// if (file.is_open())
	// {
	// 	file << "********** REQUEST **********\n" << data << "********** END **********\n" << std::endl;
	// 	file.close();
	// }

	ss << data;
	while (getline(ss, line))
	{
		if (i == 0)
			parse_request_line(line, conf);
		else if (i > 0 && line.find(":") != std::string::npos)
			parse_request_headers(line, conf);
		else
		{
			buffer << ss.rdbuf();
			this->_body = buffer.str();
			check_body_size(fd, conf);
			trim_body();
			if (_isChunked)
			{
				_body = parse_chunk_request();
			}
			break;
		}
		i++;
	}
	_isParsed = true;
	return (0);
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
			size_t pos;
			if ((pos = str.find("?")) != std::string::npos)
			{
				_path = str.substr(0, pos);
				_headers["Query-String"] = str.substr(pos + 1, str.size() - 1);
			}
			else
				this->_path = str;
			this->_raw_path = str;
			check_path(conf);
		}
		i++;
	}
	if (i != 3)
		this->_status = CODE_400;
}

void	Request::parse_request_headers(std::string &line, Config conf)
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
		}
		if (_headers.count("Transfer-Encoding") && _headers["Transfer-Encoding"] == "chunked")
		{
			_isChunked = true;
		}
		else if (_headers.count("Host"))
		{
			size_t pos = _headers["Host"].find(":");
			this->_host =  _headers["Host"].substr(0, pos);
 			if (this->_host.compare(conf.get_host()))
			{
				this->_status = CODE_400;
			}
		}
	}
}

void	Request::trim_value(std::string &value)
{
	size_t	pos;

	pos = value.find_first_not_of(32, 0);
	if (pos != std::string::npos)
	{
		value.erase(0, pos);
	}
	while (!value.empty() && (value.back() == '\r' || value.back() == '\n'))
	{
	   value.pop_back();
	}
}

std::vector<std::string> Request::check_location_file(std::string root, const std::string& path)
{
	_raw_path = path;
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

	int	size = 0;
	(void) fd;

	if (!_headers["Content-Length"].empty())
		size = std::stoi(_headers["Content-Length"]);

	if (size > conf.get_CMBS())
		this->_status = CODE_413;

}


void	Request::trim_body()
{
	while (!_body.empty() && (_body.back() == '\r' || _body.back() == '\n'))
	{
	   _body.pop_back();
	}
}

std::string	Request::parse_chunk_request()
{
	std::istringstream iss(_body);
	std::string line, util, new_body;

	// Read and process each chunk
	while (std::getline(iss, line)) {
		// Parse the chunk size
		size_t chunkSize = std::stoul(line, nullptr, 16);
		if (chunkSize == 0) {
			// Zero-length chunk indicates the end of the request body
			break;
		}

		// Read the chunk data
		std::string chunkData(chunkSize, '\0');
		iss.read(&chunkData[0], chunkSize);
		// Append the chunk to the reconstructed request body
		new_body.append(chunkData);
		// Discard the line break after each chunk
		getline(iss, util);
	}
	return (new_body);
}

void	Request::check_path(Config conf)
{
	std::vector<Location>			loc = conf.get_location();
	std::vector<Location>::iterator	it;
	std::string						root_path, substr = "/";

	std::vector<std::string> vec = check_location_file(conf.get_root(), _path);
	_location = vec[0];
	_file = vec[1];

	for (it = loc.begin(); it != loc.end(); ++it)
	{
		if (!_location.compare(it->getLocationType()))
		{
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
