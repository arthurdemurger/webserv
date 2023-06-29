/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:24:08 by hdony             #+#    #+#             */
/*   Updated: 2023/06/05 11:42:26 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP

# define CGI_HPP

# include "../../Webserv.hpp"

class Cgi
{
		private:
			/*
			** ------------------------------- Attributes --------------------------------
			*/
			int			_status;
			std::string	_response;
		public:
				/*
			** ------------------------------- Canonical form --------------------------------
			*/
			Cgi();
			Cgi(const Cgi &copy);
			Cgi	 &operator=(const Cgi &copy);
			~Cgi();

			/*
			** ------------------------------- Accessors --------------------------------
			*/
			int			get_status(void) const;
			std::string	get_response(void) const;
			void		set_response(std::string rsp);

			/*
			** ------------------------------- Methods --------------------------------
			*/
			int launch(int sock, char **env, std::string path, std::string body);

};

# endif