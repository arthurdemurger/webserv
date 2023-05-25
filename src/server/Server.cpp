/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:10:49 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 16:14:29 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Server::Server()
{

}

Server::Server(const Server &copy)
{
	*this = copy;
}

/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Server::~Server() { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Server &Server::operator=(const Server &copy)
{
	if (this != &copy)
	{
		_socket = copy._socket;
		_serv_fd = copy._serv_fd;
		_read_set = copy._read_set;
		_write_set = copy._write_set;
		_config = copy._config;
	}
	return (*this);
}

/*
** ------------------------------- ACCESSOR --------------------------------
*/
Config					Server::get_config(void) const { return (_config); }
int						Server::get_fd(void) const { return (_serv_fd); }
std::string				Server::get_name(void) const { return (_name); }
std::vector<int>		Server::get_read_set(void) const { return (_read_set); }
Socket					Server::get_socket(void) const { return (_socket); }
std::vector<int>		Server::get_write_set(void) const { return (_write_set); }

/*
** ------------------------------- METHODS --------------------------------
*/

/* Private Methods */


/* Public Methods */

