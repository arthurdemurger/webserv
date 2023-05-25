/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:23 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 14:55:50 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_HPP

#define LAUNCHER_HPP

#include "Webserv.hpp"

class Client;
class Parser;
class Server;

class Launcher
{
	private:
		Parser							_parser;
		std::map<int, Server>			_servers;
		std::map<int, Client>			_clients;
		fd_set							_read_pool;
		fd_set							_write_pool;
		int								_max_fd;

		void	accepter(int sock);
		void	add_request(int &client_sock);
		void	send_response(int client_sock);
	public:

		Launcher(void);
		~Launcher(void);
		Launcher(const Launcher &copy);
		Launcher &operator=(const Launcher &copy);

		void	setup(void);
		void	run(void);

		class SelectException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					perror("select");
					return ("");
				};
		};
};

#endif // LAUNCHER_HPP