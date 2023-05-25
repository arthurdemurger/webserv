/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 15:11:43 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

#define SERVER_HPP

#include "Socket.hpp"

class Socket;

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
		Server(const Server &copy);
		const Server &operator=(const Server &copy);
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