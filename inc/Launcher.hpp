/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:23 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 12:36:42 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_HPP

#define LAUNCHER_HPP

#include "Webserv.hpp"
#include "server/Server.hpp"
#include "server/client/Client.hpp"
#include "parser/Parser.hpp"

class Launcher
{
	protected:
		std::map<int, Server>			_servers;
	
	private:
		Parser							_parser;
		std::map<int, Client>			_clients;
		fd_set							_read_pool;
		fd_set							_write_pool;
		int								_max_fd;
		std::string						conf_filename;

		void	accepter(int sock);
		void	add_request(int &client_sock);
		void	send_response(int client_sock);
		void	add_serv_to_set(void);
		void	add_to_set(int fd, fd_set &set);
		void	remove_from_set(int fd, fd_set &set);

	public:
		Launcher(std::string conf_filename);
		~Launcher(void);
		Launcher(const Launcher &copy);
		Launcher &operator=(const Launcher &copy);

		void	setup(void);
		void	run(void);
		std::map<int, Server>	&getServer();

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