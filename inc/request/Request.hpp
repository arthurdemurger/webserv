/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:09 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/11 10:44:44 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP

#define REQUEST_HPP

#include <iostream>
#include <string>
#include <unordered_map>

class Request
{
	private:
		std::string method;
		std::string path;
		std::unordered_map<std::string, std::string> headers;
		std::string body;

		void	parser(std::string request);
		Request();

	public:
		Request(std::string request);
		Request(const Request &copy);
		Request	&operator=(const Request &copy);
		~Request();
};

#endif