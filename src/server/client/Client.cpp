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
Client::Client(void)
{
}

Client::Client(int socket, int server_fd) : _serv_fd(server_fd), _sock(socket)
{

}

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

bool		Client::is_request_parsed(void) const { return (_request.get_is_parsed()); }

Config		Client::get_conf(void) const { return (_conf); }

/*
** ------------------------------- METHODS --------------------------------
*/

void	Client::add_request(Config conf)
{
	_request.parse(_sock, conf);
}

void	Client::send_response(void)
{
	// std::cout << _request.get_method() << " : " << _request.get_path() << std::endl;
	if (_request.get_method() == "GET")
	{
		std::string response = _response.build_get_method(_request);

		size_t bytesSend = send(_sock, response.c_str(), response.length(), 0);
	}

	if (_request.get_method() == "POST")
		_response.build_post_method(_request, _sock);
}