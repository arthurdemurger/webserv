/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 11:25:46 by ademurge         ###   ########.fr       */
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
int	Request::parse(int fd)
{
	/*	Une requête est prête à être lue dans le fd donnée en argument.
		Il faut donc récupérer toutes les infos nécessaires de la requête et les sauvegarder
		dans les différents attributs de cette classe.
	*/
	char				buf[BUF_SIZE];
	int					n;

	n = read(fd, buf, BUF_SIZE);
	if (!n)
		return (0);
	std::string data(buf, n);
	std::cout << data << std::endl;
	return (1);
}