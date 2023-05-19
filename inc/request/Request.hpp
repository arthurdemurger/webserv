/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:09 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/19 11:24:08 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP

#define REQUEST_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unistd.h>

# define BUF_SIZE 30000

class Request
{
	private:
		std::string										_method;
		std::string										_path;
		std::unordered_map<std::string, std::string>	_headers;
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
		std::unordered_map<std::string, std::string>	getHeaders() const;

		/*
		** ------------------------------- METHODS --------------------------------
		*/
		int	parse(int fd);
};

#endif