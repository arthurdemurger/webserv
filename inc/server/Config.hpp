/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:04:44 by hdony             #+#    #+#             */
/*   Updated: 2023/05/25 14:53:26 by ademurge         ###   ########.fr       */
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
		Config(const Config &rhs);
		Config &operator=(const Config &rhs);
		~Config();

};

#endif