/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:21:37 by hdony             #+#    #+#             */
/*   Updated: 2023/05/24 15:31:33 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
# define SERVER

# include "Parsing.hpp"

class   Location;

class Server
{
private:
	/*
	** ------------------------------- Attributes --------------------------------
	*/
	std::vector<int>			_port;
	std::string					_host;
	std::vector<std::string>	_server_name;
	std::map<int, std::string>	_error_page;
	int							_client_max_body_size;
	std::string					_root;
	std::string					_index;
	std::vector<Location>		_location;

public:
	/*
	** ------------------------------- Canonical form --------------------------------
	*/
	Server(std::string &ServerBlock);
	Server(const Server &rhs);
	Server &operator=(const Server &rhs);
	~Server();

	/*
	** ------------------------------- Accessors --------------------------------
	*/
	void	setPortMBS(std::string &key, std::string &rhs);
	void	setHostDir(std::string &rhs);
	void	setServerNameDir(std::string &rhs);
	void	setErrorPageDir(std::string &rhs);
	void	setClientMaxBodySize(std::string &rhs);
	void	setRootDir(std::string &value);

	/*
	** ------------------------------- Methods --------------------------------
	*/
	void	PrintServer();
	void	setter(std::string &key, std::string &value, std::istringstream &iss, std::string &location);
};

#endif
