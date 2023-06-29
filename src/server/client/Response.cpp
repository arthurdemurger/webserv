/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:18 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 15:44:57 by ademurge         ###   ########.fr       */
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

	if (!file.fail())
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

std::string	Response::build_error(Request &request, int status)
{
	std::string response =  "HTTP/1.1 " + request.get_status() + "\n";

	response += "Content-Type: text/html\n\n";

	if (_error_pages[status].empty())
		response += file_to_string("www/error/default_error.html");
	else
		response += file_to_string(_error_pages[status]);

	return (response);
}

std::string	Response::build_cgi(Request &request, int sock)
{
	std::string content_type = "CONTENT_TYPE=" + request.get_headers()["Content-Type"];
	std::string content_length = "CONTENT_LENGTH=" + request.get_headers()["Content-Length"];
	std::string request_method = "REQUEST_METHOD=" + request.get_method();
	std::string script_name = "SCRIPT_NAME=" + request.get_path();
	std::string server_protocol = "SERVER_PROTOCOL=HTTP/1.1";
	std::string	query_string = "QUERY_STRING=" + request.get_headers()["Query-String"];
	long long length = FILE_SIZE_MAX;
	if (!request.get_headers()["Content-Length"].empty())
		length = stoll(request.get_headers()["Content-Length"]);

	char* env[] = {&content_type[0], &content_length[0], &request_method[0], &script_name[0],
				   &server_protocol[0], &query_string[0], NULL};

	Cgi	cgi;

	if (cgi.launch(sock, env, request.get_path(), request.get_body()) < 0)
		return ("");

	if (cgi.get_status() != 0)
	{
		request.set_status(CODE_500);
		cgi.set_response(build_error(request, 500));
	}
	return (cgi.get_response());
}

std::string	Response::build_get_method(Request &request)
{
	std::string	response = 	"HTTP/1.1 " + request.get_status() + "\n";

	if (request.get_autoindex() == true)
		return (build_autoindex(request.get_path(), request.get_location()));
	if (request.get_path().find(".html") != std::string::npos)
		 response += "Content-Type: text/html\n";
	else if (request.get_path().find(".css") != std::string::npos)
		response += "Content-Type: text/css\n";
	else if (request.get_path().find(".ico") != std::string::npos)
		response += "Content-Type: image/ico\n";

	std::string body = file_to_string(request.get_path());
	response += "Content-Length: " + std::to_string(body.size());
	response += "\r\n\r\n" + body;
	return (response);
}

std::string	Response::build_delete_method(Request &request)
{
	std::string	response = 	"HTTP/1.1 204 No Content\n\n";

	remove(request.get_path().c_str());

	return (response);
}