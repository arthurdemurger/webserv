/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:04:44 by hdony             #+#    #+#             */
/*   Updated: 2023/05/24 15:30:11 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Parsing.hpp"

class   Server;

class Config
{
private:
	/*
	** ------------------------------- Attributes --------------------------------
	*/
	std::string					_content;
	int							_server_nb;
	std::vector<int>			_vec_start_block;
	std::vector<int>			_vec_end_block;
	std::vector<std::string>	_vec_config;
	std::vector<Server>			_vec_server;

public:
	/*
	** ------------------------------- Canonical form --------------------------------
	*/
	Config();
	Config(const Config &rhs);
	Config &operator=(const Config &rhs);
	~Config();

	/*
	** ------------------------------- Accessors --------------------------------
	*/
	const std::vector<std::string>	&getVecServConf() const;
	const int						&getServerNb() const;

	/*
	** ------------------------------- Methods --------------------------------
	*/
	std::string ConfigReading(std::string &path);
	void		ConfigParsing(std::string path);
	void		ServerCount();
	void		PopulateVecConfig();
	void		ServerBlockStart();
	void		ServerBlockEnd();
	void		PopulateServer();
};

#endif