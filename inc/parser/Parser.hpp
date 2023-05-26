/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:04:44 by hdony             #+#    #+#             */
/*   Updated: 2023/05/26 11:22:24 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* Classe qui va parser le config file et instancier tous les serveurs du launchers. */

#ifndef PARSER_HPP

#define PARSER_HPP

# include "../server/Server.hpp"

class Server;

class Parser
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/
		std::string					_content;
		int							_server_nb;
    	std::vector<int>            _start_block;
    	std::vector<int>            _end_block;
    	std::vector<std::string>    _config;
    	std::vector<Server>    		_server;

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Parser();
		Parser(std::string path);
		Parser(const Parser &rhs);
		Parser &operator=(const Parser &rhs);
		~Parser();

		/*
		** ------------------------------- Methods --------------------------------
		*/
		std::string reading(std::string path);
		void    	server_count();
		void   		split_blocks();
		void		block_end();
		void		populate_server();
		
};

#endif