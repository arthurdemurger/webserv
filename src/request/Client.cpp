/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:20:19 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/17 16:40:07 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/request/Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Client::Client(void) { }

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
int		Client::getSocket(void) const { return (_socket_fd); }

Request		Client::getRequest(void) const { return (_request); }


void	Client::setSocket(int sock_fd) { _socket_fd = sock_fd; }

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
	std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<!doctype html><html><head><title>This is the title of the webpage!</title></head><body><p>This is an example paragraph.</p></body></html>";
	size_t bytesSend = send(_socket_fd, response.c_str(), response.size(), 0);
}
