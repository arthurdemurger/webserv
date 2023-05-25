/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:06 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/25 16:35:09 by ademurge         ###   ########.fr       */
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
			conf_filename == av[1];

		Launcher	launcher(conf_filename);

		launcher.run();
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
