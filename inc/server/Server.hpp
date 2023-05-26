/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 12:02:44 by hdony            ###   ########.fr       */
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
		Socket					_socket;
		int						_serv_fd;
		std::vector<int>		_read_set;
		std::vector<int>		_write_set;

		/*
		** ------------------------------- Methods --------------------------------
		*/

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Server();
		Server(std::string config);
		Server(const Server &copy);
		Server &operator=(const Server &copy);
		~Server();

		/*
		** ------------------------------- Accessor --------------------------------
		*/
		Config					get_config(void) const;
		int						get_fd(void) const;
		std::string				get_name(void) const;
		std::vector<int>		get_read_set(void) const;
		Socket					get_socket(void) const;
		std::vector<int>		get_write_set(void) const;

		/*
		** ------------------------------- Methods --------------------------------
		*/

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