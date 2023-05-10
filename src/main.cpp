/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:06 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 15:21:23 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

int main(void)
{
	while (true)
	{
		Server serv(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY, 10);

		serv.launcher();
	}
	return (0);
}
