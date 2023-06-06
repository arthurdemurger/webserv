/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:11 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/06 11:06:56 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP

# define RESPONSE_HPP

#include "../../Webserv.hpp"
#include "Request.hpp"
#include "Cgi.hpp"

class Response
{
	private:
		std::string	_version;
		std::string	_status_code;
		std::string	_date;
		std::string	_content_type;
		std::string	_content_length;
		std::string	_body;

		std::string	file_to_string(std::string filename) const;
	public:
		/*
		** ------------------------------- COPLIEN --------------------------------
		*/
		Response();
		~Response();
		Response(const Response &copy);
		Response &operator=(const Response &copy);

		/*
		** ------------------------------- ACCESSORS --------------------------------
		*/

		/*
		** ------------------------------- METHOD --------------------------------
		*/

		std::string		build_body(std::string filename);
		std::string		build_get_method(Request &request);
		void			build_post_method(Request &request, int sock);
		std::string		build_error(Request &request);
};

#endif //RESPONSE_HPP