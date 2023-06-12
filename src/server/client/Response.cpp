/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:18 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/12 11:09:40 by hdony            ###   ########.fr       */
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
void	Response::set_error_pages(std::map<int, std::string> error_pages) { _error_pages = error_pages; };

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

std::vector<std::string>	Response::get_files_current_directory(std::string path)
{
    std::vector<std::string> files;
    DIR* directory;
    struct dirent* entry;

    directory = opendir(path.c_str());
    if (directory != nullptr) {
        // Lire les entrées du répertoire
        while ((entry = readdir(directory)) != nullptr) {
            // Ignorer les entrées spéciales "." et ".."
            if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
                files.push_back(std::string(entry->d_name));
            }
        }

        // Fermer le répertoire
        closedir(directory);
    }

    return files;
}

std::string	Response::build_autoindex(std::string path, std::string location)
{
	std::vector<std::string>	files = get_files_current_directory(path);
	std::string					body = file_to_string("www/auto_index.html");

	for (std::vector<std::string>::reverse_iterator it = files.rbegin(); it != files.rend(); it++)
	{
		size_t	pos = body.find("</ul></div>");

		if (pos != std::string::npos)
		{
			if (location == "/")
				body.insert(pos, "<li><a href=\"/" + (*it) + "\">" + (*it) + "</a></li>");
			else
				body.insert(pos, "<li><a href=\"" + location + "/" + (*it) + "\">" + (*it) + "</a></li>");

		}
	}

	std::string	response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
	response += body;

	return (response);
}

std::string	Response::build_body(std::string filename)
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

std::string	Response::build_error(Request &request, int status)
{
	std::string	response =  "HTTP/1.1 " + request.get_status() + "\n";

	response += "Content-Type: text/html\n\n";

	if (_error_pages[status].empty())
		response += file_to_string("www/error/default_error.html");
	else
		response += file_to_string(_error_pages[status]);

	return (response);
}

std::string	Response::build_post_method(Request &request, int sock)
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
		return (cgi.launch(sock, env, request.get_path(), request.get_body()));
}

std::string	Response::build_get_method(Request &request)
{
	std::string	response = 	"HTTP/1.1 " + request.get_status() + "\n";

	if (request.get_autoindex() == true)
		return (build_autoindex(request.get_path(), request.get_location()));
	if (request.get_path().find(".html") != std::string::npos || request.get_path().find(".php") != std::string::npos)
		 response += "Content-Type: text/html\n";
	else if (request.get_path().find(".css") != std::string::npos)
		response += "Content-Type: text/css\n";
	else if (request.get_path().find(".ico") != std::string::npos)
		response += "Content-Type: image/ico\n";

	std::string body = file_to_string(request.get_path());
	response += "Content-Length: " + std::to_string(body.size());
	response += "\n\n" + body;
	return (response);
}

std::string	Response::build_delete_method(Request &request)
{
	std::string	response = 	"HTTP/1.1 204 No Content\n\n";

	remove(request.get_path().c_str());

	return (response);
}