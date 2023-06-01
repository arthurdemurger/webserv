/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:09 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/01 10:02:30 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP

#define REQUEST_HPP

#include "../../Webserv.hpp"
#include "../../../inc/server/Config.hpp"

class Request
{
	private:
		std::string										_method;
		std::string										_status;
		std::string										_path;
		std::map<std::string, std::string>				_headers;
		std::string										_body;
		bool											_isParsed;

	public:
		/*
		** ------------------------------- COPLIEN --------------------------------
		*/
		Request();
		Request(const Request &copy);
		Request	&operator=(const Request &copy);
		~Request();

		/*
		** ------------------------------- ACCESSORS --------------------------------
		*/
		std::string							get_method() const;
		std::string							get_body() const;
		std::string							get_path() const;
		std::string							get_status() const;
		std::map<std::string, std::string>	get_headers() const;
		bool								get_is_parsed() const;

		/*
		** ------------------------------- METHODS --------------------------------
		*/
		int		parse(int fd, Config config);
		void	parse_request_line(std::string &line, Config conf);
		void	parse_request_headers(std::string &line);
		void	trim_value(std::string &value);
		void	print_request();
		void	check_method();
		void	check_path(Config conf);
};

#endif