/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:04:44 by hdony             #+#    #+#             */
/*   Updated: 2023/06/29 15:05:53 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* Classe avec toute la config d'un serveur : port, location, ... */

#ifndef CONFIG_HPP

#define CONFIG_HPP

#include "../Webserv.hpp"
#include "Location.hpp"
#include "Utils.hpp"

class Config
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/
		std::vector<int>			_port;
		std::string					_host;
		std::vector<std::string>	_server_name;
		std::vector<std::string>	_allow_methods;
		std::map<int, std::string>	_error_page;
		int							_client_max_body_size;
		std::string					_root;
		std::string					_index;
		std::vector<Location>		_location;

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Config();
		Config(std::string server_block);
		Config(const Config &rhs);
		Config &operator=(const Config &rhs);
		~Config();

		/*
		** ------------------------------- Accessors --------------------------------
		*/
		void	setPortMBS(std::string &key, std::string &rhs);
		void	setHostDir(std::string &rhs);
		void	setServerNameDir(std::string &rhs);
		void	setErrorPageDir(std::string &rhs);
		void	setClientMaxBodySize(std::string &rhs);
		void	setRootDir(std::string &value);

		std::string					get_name(void) const;
		std::string					get_root(void) const;
		std::string					get_index(void) const;
		std::string					get_host(void) const;
		std::vector<int>			get_ports(void) const;
		std::vector<Location>		get_location(void) const;
		int							get_CMBS(void) const;
		std::map<int, std::string>	get_error_pages(void) const;
		/*
		** ------------------------------- Methods --------------------------------
		*/
		void	setter(std::string &key, std::string &value, std::istringstream &iss, std::string &location);
		void	print_server();

};

#endif