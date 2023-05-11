/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/11 11:18:44 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/request/Request.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Request::Request(std::string request)
{
	parser(request);
}

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
		method = copy.method;
		path = copy.path;
		headers = copy.headers;
		body = copy.body;
	}
	return (*this);
}

/*
** ------------------------------- METHODS --------------------------------
*/
void	Request::parser(std::string request)
{
	(void) request;
}