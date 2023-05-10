/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:06 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 15:56:28 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/webserv.hpp"

int main(void)
{
	Server serv(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY, 10);

	serv.launcher();
	return (0);
}
