/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:09 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 15:15:46 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP

#define REQUEST_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <unistd.h>
#include <fcntl.h>

# define BUF_SIZE 5

class Request
{
	private:
		std::string										_method;
		std::string										_path;
		std::map<std::string, std::string>				_headers;
		std::string										_body;

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
		std::string										getMethod() const;
		std::string										getBody() const;
		std::string										getPath() const;
		std::map<std::string, std::string>				getHeaders() const;

		/*
		** ------------------------------- METHODS --------------------------------
		*/
		int		parse(int fd);
		void	parse_request_line(std::string &line);
		void	parse_request_headers(std::string &line);
		void	trim_value(std::string &value);
		void	print_request();
};

#endif