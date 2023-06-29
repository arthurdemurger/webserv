/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:56:10 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 14:03:40 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP

# define CLIENT_HPP

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
		Client(int socket, int server_fd);
		~Client();
		Client(const Client &copy);
		Client	&operator=(const Client &copy);

		/*
		** ------------------------------- ACCESSORS --------------------------------
		*/
		int		get_socket(void) const;
		int		get_server_fd(void) const;
		Config	get_conf(void) const;
		Request	get_request(void) const;
		void	set_socket(int sock_fd);
		bool	is_request_parsed(void) const;
		void	close_connection();
		/*
		** ------------------------------- METHODS --------------------------------
		*/
		std::string	add_request(Config conf);
		std::string	send_response();
};

#endif // CLIENT_HPP