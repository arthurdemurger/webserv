/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:18 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/01 13:03:20 by ademurge         ###   ########.fr       */
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

	void		Response::set_full_response(std::string resp) { _full_response = resp; };

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


std::string	Response::build_error(Request &request)
{
	std::string	response;

	// if (request.get_status() == "404")
	response =  "HTTP/1.1 404 Not Found\n"
				"Content-Type: text/html\n\n";
	response += file_to_string("html/error/404.html");
	return (response);
}

std::string	Response::build_get_method(Request &request)
{
	std::string	response;

	if (request.get_status() >= "400")
		response = build_error(request);
	else if (request.get_status() == "200")
	{
		response = 	"HTTP/1.1 200 OK\n"
					"Content-Type: text/html\n\n";
		response += file_to_string(request.get_path());
	}
	return (response);
}

std::string	Response::build(Request &request)
{
	// std::cout << "status : " << request.get_status() << std::endl;
	// std::cout << "method : " << request.get_method() << std::endl;
	if (request.get_method() == "GET")
		return (build_get_method(request));
	return ("");
	// std::cout << request.get_method() << std::endl;
}
