/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:11 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/26 12:36:57 by hdony            ###   ########.fr       */
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
		std::string _body;

	public:
		/*
		** ------------------------------- COPLIEN --------------------------------
		*/
		Response();
		~Response();
		Response(const Response &copy);
		Response &operator=(const Response &copy);

		/*
		** ------------------------------- METHOD --------------------------------
		*/
		void	buildResponse(Request &request);
};

#endif //RESPONSE_HPP