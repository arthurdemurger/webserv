/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:04:44 by hdony             #+#    #+#             */
/*   Updated: 2023/05/25 16:55:42 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* Classe avec toute la config d'un serveur : port, location, ... */

#ifndef CONFIG_HPP

#define CONFIG_HPP

#include "../Webserv.hpp"

class Config
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Config();
		Config(std::string path);
		Config(const Config &rhs);
		Config &operator=(const Config &rhs);
		~Config();

};

#endif