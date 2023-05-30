/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:18 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/30 12:38:33 by ademurge         ###   ########.fr       */
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
std::string	Response::build_get_method(Request &request)
{
	std::ifstream file(request.get_path());

	std::cout << LIGHT_RED << request.get_path() << RESET << std::endl;

	std::string response;

	response =  "HTTP/1.1 200 OK\n"
				"Content-Type: text/html\n\n";

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			response += line + '\n';
		file.close();
	}
	else
	{
		std::cerr << "Erreur lors de l'ouverture du fichier : html/index.html" << std::endl;
	}
	return (response);
}

void	Response::build(Request &request)
{
	if (request.get_is_parsed())
	{
		if (request.get_method() == "GET")
		_full_response = build_get_method(request);
	}
	// std::cout << request.get_method() << std::endl;
}