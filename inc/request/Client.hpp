/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:56:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/24 11:59:29 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP

# define CLIENT_HPP

#include <iostream>
#include <unistd.h>
#include "Request.hpp"
#include "Response.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>

class Request;
class Response;

class Client
{
	private:
		int			_socket_fd;
		Request		_request;
		Response	_response;
		void		buildResponse();

	public:
		/*
		** ------------------------------- COPLIEN --------------------------------
		*/
		Client();
		Client(int socket);
		~Client();
		Client(const Client &copy);
		Client	&operator=(const Client &copy);

		/*
		** ------------------------------- ACCESSORS --------------------------------
		*/
		int		getSocket(void) const;
		Request	getRequest(void) const;
		void	setSocket(int sock_fd);

		/*
		** ------------------------------- METHODS --------------------------------
		*/
		int		addRequest();
		void	sendResponse();
};

#endif // CLIENT_HPP