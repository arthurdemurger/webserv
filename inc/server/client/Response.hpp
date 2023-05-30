/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:11 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/30 12:23:46 by ademurge         ###   ########.fr       */
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

		/*
		** ------------------------------- METHOD --------------------------------
		*/
		std::string	build_get_method(Request &request);
		void		build(Request &request);
};

#endif //RESPONSE_HPP