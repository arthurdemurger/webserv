/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 15:53:58 by ademurge         ###   ########.fr       */
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
		/*
		** ------------------------------- Methods --------------------------------
		*/
		void					activate(int protocol, int port, int backlog);
		/*
		** ------------------------------- Exceptions --------------------------------
		*/
		class ReadException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("read");
					return ("");
				};
		};
		class AcceptException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("accept");
					return ("");
				};
		};
		class FcntlException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("fcntl");
					return ("");
				};
		};
};


#endif