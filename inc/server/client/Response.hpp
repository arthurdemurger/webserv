/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:11 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/28 12:03:11 by ademurge         ###   ########.fr       */
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
		std::string					_version;
		std::string					_status_code;
		std::string					_date;
		std::string					_content_type;
		std::string					_content_length;
		std::string					_body;
		std::string					_full_response;
		std::map<int, std::string>	_error_pages;

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
		void	set_error_pages(std::map<int, std::string> error_pages);
		/*
		** ------------------------------- METHOD --------------------------------
		*/

		std::string					build_get_method(Request &request);
		std::string					build_cgi(Request &request, int sock);
		std::string					build_autoindex(std::string path, std::string location);
		std::vector<std::string>	get_files_current_directory(std::string path);
		std::string					build_delete_method(Request &request);
		std::string					build_error(Request &request, int status);
};

#endif //RESPONSE_HPPol