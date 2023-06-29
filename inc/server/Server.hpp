/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 15:15:05 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include "../Webserv.hpp"
#include "Socket.hpp"
#include "Config.hpp"

class Server
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/
		std::string				_name;
		Config					_config;
		std::vector<Socket>		_sockets;
		std::vector<int>		_fds;

		/*
		** ------------------------------- Methods --------------------------------
		*/
	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Server();
		Server(const Server &copy);
		Server &operator=(const Server &copy);
		~Server();

		/*
		** ------------------------------- Accessor --------------------------------
		*/
		Config					get_config(void) const;
		std::vector<int>		get_fds(void) const;
		std::string				get_name(void) const;
		std::vector<Socket>		get_sockets(void) const;

		void					set_name(std::string const &name);
		void					set_config(Config conf);
		/*
		** ------------------------------- Methods --------------------------------
		*/
		int					activate(int port, int backlog);
		int					configure(Config conf);
};


#endif