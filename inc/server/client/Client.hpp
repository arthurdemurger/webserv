/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:56:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/30 12:44:11 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP

# define CLIENT_HPP

#include "../../Webserv.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "../Config.hpp"

class Client
{
	private:
		int			_serv_fd;
		int			_sock;
		Request		_request;
		Response	_response;
		Config		_conf;

	public:
		/*
		** ------------------------------- COPLIEN --------------------------------
		*/
		Client();
		Client(int socket, int server_fd, Config config);
		~Client();
		Client(const Client &copy);
		Client	&operator=(const Client &copy);

		/*
		** ------------------------------- ACCESSORS --------------------------------
		*/
		int		get_socket(void) const;
		int		get_server_fd(void) const;
		Request	get_request(void) const;
		void	set_socket(int sock_fd);
		bool	is_request_parsed(void) const;

		/*
		** ------------------------------- METHODS --------------------------------
		*/
		int		add_request();
		void	send_response();
};

#endif // CLIENT_HPP