/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:11 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/01 10:36:47 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP

# define RESPONSE_HPP

#include "../../Webserv.hpp"
#include "Request.hpp"

class Response
{
	private:
		std::string	_version;
		std::string	_status_code;
		std::string	_date;
		std::string	_content_type;
		std::string	_content_length;
		std::string	_body;
		std::string	_full_response;

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
		std::string	get_full_response(void) const;
		void		set_full_response(std::string resp);

		/*
		** ------------------------------- METHOD --------------------------------
		*/
		std::string		build_get_method(Request &request);
		std::string		build_error(Request &request);
		std::string		build(Request &request);
};

#endif //RESPONSE_HPP