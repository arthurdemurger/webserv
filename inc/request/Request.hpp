/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:09 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/12 12:14:58 by ademurge         ###   ########.fr       */
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
		std::string										_method;
		std::string										_path;
		std::unordered_map<std::string, std::string>	_headers;
		std::string										_body;


	public:
		Request();
		Request(const Request &copy);
		Request	&operator=(const Request &copy);
		~Request();

		void	parse(int fd);
};

#endif