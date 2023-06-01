/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Launcher.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:23 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/01 12:39:58 by ademurge         ###   ########.fr       */
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
	private:
		Parser							_parser;
		std::map<int, Server>			_servers;
		std::map<int, Client>			_clients;
		fd_set							_read_pool;
		fd_set							_write_pool;
		int								_max_fd;
		std::string						_config_file;

		void	accepter(int sock);
		void	handle_request(int &client_sock, Client &client);
		void	handle_response(int &client_sock, Client &client);
		void	add_serv_to_sets(void);
		void	add_to_set(int fd, fd_set &set);
		void	remove_from_set(int fd, fd_set &set);
		void	setup();

	void	print_fd(void);

	public:
		Launcher(std::string conf_filename);
		~Launcher(void);
		Launcher(const Launcher &copy);
		Launcher &operator=(const Launcher &copy);

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