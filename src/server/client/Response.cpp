/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:18 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/07 12:50:27 by hdony            ###   ########.fr       */
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
		std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
	return (str);
}

std::string	Response::build_body(std::string filename)
{
	std::ifstream	file(filename);
	std::string		str;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			size_t	pos;

			// if ((pos = line.find("<head>")) != std::string::npos)
			// 	line.insert(pos, "<style>" + file_to_string("html/styles.css") + "</style>");
			str += line + '\n';
		}
		file.close();
	}
	else
		std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
	return (str);
}

std::string	Response::build_error(Request &request)
{
	std::string	response;

	// if (request.get_status() == "404")
	response =  "HTTP/1.1 404 Not Found\n"
				"Content-Type: text/html\n\n";
	response += file_to_string("docs/html/error/404.html");

	return (response);
}

void	Response::build_post_method(Request &request, int sock)
{
	std::string content_type = "CONTENT_TYPE=" + request.get_headers()["Content-Type"];
	std::string content_length = "CONTENT_LENGTH=" + request.get_headers()["Content-Length"];
	std::string request_method = "REQUEST_METHOD=" + request.get_method();
	std::string script_name = "SCRIPT_NAME=" + request.get_path();
	std::string server_protocol = "SERVER_PROTOCOL=HTTP/1.1";
	std::string server_name = "SERVER_NAME=localhost";
	std::string server_port = "SERVER_PORT=8000";

	char* env[] = {&content_type[0], &content_length[0], &request_method[0], &script_name[0],
				   &server_protocol[0], &server_name[0], &server_port[0], NULL};

	Cgi	cgi;

	if (!request.get_body().empty())
		 cgi.launch(sock, env, request.get_path(), request.get_body());
}

std::string	Response::build_get_method(Request &request)
{
	std::string	response;

	if (request.get_status() >= "400")
		response = build_error(request);
	else if (request.get_status() == "200")
	{
		response = 	"HTTP/1.1 200 OK\n";
		if (request.get_path().find(".html") != std::string::npos)
			response += "Content-Type: text/html\n\n";
		else if (request.get_path().find(".css") != std::string::npos)
			response += "Content-Type: text/css\n\n";
		else if (request.get_path().find(".ico") != std::string::npos)
			response += "Content-Type: image/ico\n\n";
		response += file_to_string(request.get_path());
	}
	return (response);
}
