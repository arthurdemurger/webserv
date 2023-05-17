/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/17 14:03:02 by ademurge         ###   ########.fr       */
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
void	Request::parse(int fd)
{
	/*	Une requête est prête à être lue dans le fd donnée en argument.
		Il faut donc récupérer toutes les infos nécessaires de la requête et les sauvegarder
		dans les différents attributs de cette classe.
	*/
	// std::string			line;
	// std::stringstream	ss;
	// char				buf[BUF_SIZE];
	// int					n;

	// // Lecture de la première ligne de la requête
	// n = read(fd, buf, BUF_SIZE);
	// std::string data(buf, n);
	// while (n > 0 && data.find("\r\n\r\n") == std::string::npos)
	// {
	// 	n = read(fd, buf, sizeof(buf));
	// 	data.append(buf, n);
	// }
	// ss.str(line);
	// ss >> _method >> _path;

	// // Lecture des headers
	// while (getline(ss, line) && line != "\r") {
	//   std::size_t pos = line.find(": ");
	//   std::string key = line.substr(0, pos);
	//   std::string value = line.substr(pos + 2);
	//   _headers[key] = value;
	// }

	// // Lecture du corps de la requête
	// getline(ss, _body);
}