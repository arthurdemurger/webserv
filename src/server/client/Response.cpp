/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:18 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/31 10:23:50 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/server/client/Response.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Response::Response(void) { }

Response::Response(const Response &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Response::~Response(void) { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Response	&Response::operator=(const Response &copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

/*
** ------------------------------- ACCESSORS --------------------------------
*/

	std::string	Response::get_full_response(void) const { return (_full_response); }


/*
** ------------------------------- METHODS --------------------------------
*/

std::string	Response::file_to_string(std::string filename) const
{
	std::ifstream	file(filename);
	std::string		str;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			str += line + '\n';
		file.close();
	}
	else
	{
		std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
	}
	return (str);
}


void	Response::build_error(Request &request)
{
	if (request.get_status() == "404")
	{
		_full_response = "HTTP/1.1 404 Not Found\n"
						 "Content-Type: text/html\n\n";
		_full_response += file_to_string("html/error/404.html");
	}
}

void	Response::build_get_method(Request &request)
{
	std::string	response;

	// ICI
	if (request.get_status() >= "400")
		build_error(request);
	else if (request.get_status() == "200")
	{
		_full_response = "HTTP/1.1 200 OK\n"
				   "Content-Type: text/html\n\n";
		_full_response += file_to_string("html/index.html");
	}
}

void	Response::build(Request &request)
{
	if (request.get_is_parsed())
	{
		if (request.get_method() == "GET")
			build_get_method(request);
	}
	std::cout << request.get_method() << std::endl;
}
