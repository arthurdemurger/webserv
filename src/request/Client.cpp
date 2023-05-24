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

#include "../../inc/request/Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Client::Client(void) { }

Client::Client(int socket) : _socket_fd(socket) { }

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
		_socket_fd = copy._socket_fd;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSOR --------------------------------
*/
int			Client::getSocket(void) const { return (_socket_fd); }

Request		Client::getRequest(void) const { return (_request); }

void		Client::setSocket(int sock_fd) { _socket_fd = sock_fd; }

/*
** ------------------------------- METHODS --------------------------------
*/

int	Client::addRequest()
{
	return (_request.parse(_socket_fd));
	// std::cout << _request.getMethod() << std::endl;
	// std::cout << _request.getPath() << std::endl;
	// std::cout << _request.getHeaders() << std::endl;
	// std::cout << _request.getBody() << std::endl;
}

void	Client::sendResponse()
{
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
	size_t bytesSend = send(_socket_fd, response.c_str(), response.length(), 0);
}
