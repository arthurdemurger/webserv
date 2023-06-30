/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:49:09 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/30 16:08:23 by hdony            ###   ########.fr       */
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
		std::string										_raw_path;
		std::string										_host;
		std::map<std::string, std::string>				_headers;
		std::string										_body;
		bool											_isParsed;
		bool											_isChunked;
		std::string										_location;
		std::string										_file;
		bool											_autoindex;

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
		std::string							get_raw_path() const;
		std::string							get_location() const;
		std::string							get_status() const;
		std::map<std::string, std::string>	get_headers() const;
		bool								get_is_parsed() const;
		bool								get_autoindex() const;

		void								set_body(std::string body);
		void								set_status(std::string status);

		/*
		** ------------------------------- METHODS --------------------------------
		*/
		int							parse(int fd, Config config);
		void						parse_request_line(std::string &line, Config conf);
		void						parse_request_headers(std::string &line, Config conf);
		void						trim_value(std::string &value);
		void						check_method();
		void						check_path(Config conf);
		void						parse_path(std::string path);
		std::vector<std::string>	check_location_file(std::string root, const std::string &path);
		bool						check_allowed_method(Location loc);
		void						open_file(std::string path, Config);
		void						print_request(void);
		void						check_body_size(int fd, Config &conf);
		void						trim_body();
		std::string					parse_chunk_request();
};

#endif