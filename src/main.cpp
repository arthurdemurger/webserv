/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:06 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/05 14:01:59 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"
#include "../inc/Launcher.hpp"
int main(int ac, char **av, char **env)
{
	if (ac <= 2)
	{
		std::string conf_filename = "";

		if (ac == 2)
			conf_filename = av[1];

		Launcher	launcher(conf_filename);

		launcher.run();
		return (EXIT_SUCCESS);
	}
	// std::string	form_data = "first_name=arthur&surname=demurger&message=GG";
	// std::string	query_string = "QUERY_STRING=" + form_data;
	// std::string	content_type = "CONTENT_TYPE=application/x-www-form-urlencoded";
	// std::string	content_length = "CONTENT_LENGTH=45";
	// std::string request_method = "REQUEST_METHOD=POST";
	// std::string path = "PATH=/Users/ademurge/.brew/bin:/Users/ademurge/.brew/bin:/Users/ademurge/.brew/bin:/Users/ademurge/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/ademurge/.brew/bin";


	// execve("docs/html/cgi/script.py", NULL, env);
	return (EXIT_FAILURE);
}
