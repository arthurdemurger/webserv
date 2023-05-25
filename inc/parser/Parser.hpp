/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:04:44 by hdony             #+#    #+#             */
/*   Updated: 2023/05/25 16:16:54 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* Classe qui va parser le config file et instancier tous les serveurs du launchers. */

#ifndef PARSER_HPP

#define PARSER_HPP

class Parser
{
	private:
		/*
		** ------------------------------- Attributes --------------------------------
		*/

	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		Parser();
		Parser(const Parser &rhs);
		Parser &operator=(const Parser &rhs);
		~Parser();
};

#endif