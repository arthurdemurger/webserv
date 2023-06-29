/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:06 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 17:55:24 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"
#include "../inc/Launcher.hpp"

int main(int ac, char **av)
{
	if (ac <= 2)
	{
		std::string conf_filename = "";

		if (ac == 2)
			conf_filename = av[1];

		try
		{
			Launcher	launcher(conf_filename);

			launcher.run();
		}
		catch (std::exception const &e)
		{
			std::cout << e.what() << std::endl;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
