/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:20:19 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 13:20:12 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/server/client/Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Client::Client(void) { }

Client::Client(int socket, int server_fd) : _serv_fd(server_fd), _sock(socket) { }

Client::Client(const Client &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Client::~Client(void) { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Client	&Client::operator=(const Client &copy)
{
	if (this != &copy)
	{
		_request = copy._request;
		_sock = copy._sock;
		_serv_fd = copy._serv_fd;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSOR --------------------------------
*/
int			Client::get_socket(void) const { return (_sock); }

int			Client::get_server_fd(void) const { return (_serv_fd); }

Request		Client::get_request(void) const { return (_request); }

void		Client::set_socket(int sock_fd) { _sock = sock_fd; }

bool		Client::is_request_parsed(void) const { return (_request.getIsParsed()); }

/*
** ------------------------------- METHODS --------------------------------
*/

int	Client::add_request()
{
	return (_request.parse(_sock));
	// std::cout << _request.getMethod() << std::endl;
	// std::cout << _request.getPath() << std::endl;
	// std::cout << _request.getHeaders() << std::endl;
	// std::cout << _request.getBody() << std::endl;
}

void	Client::send_response(void)
{
	// _response.buildResponse(_request);

	std::ifstream file("html/index.html");
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
	size_t bytesSend = send(_sock, response.c_str(), response.length(), 0);
}
