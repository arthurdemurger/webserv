/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:37:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/05 14:07:10 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/server/client/Cgi.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Cgi::Cgi() { }

Cgi::Cgi(const Cgi &copy) { *this = copy; }


/*
** ------------------------------- DESTRUCTOR --------------------------------
*/
Cgi::~Cgi() { }

/*
** ------------------------------- OPERATOR OVERLOAD --------------------------------
*/
Cgi &Cgi::operator=(const Cgi &copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

/*
** ------------------------------- METHODS --------------------------------
*/

void	Cgi::launch(int client_sock, char **env, std::string path)
{
	pid_t	pid;

	// int size = 0;
	ICI
		printf("%s\n", env[0]);
		printf("%s\n", env[1]);
		printf("%s\n", env[2]);
		printf("%s\n", env[3]);
		ICI
	// std::cout << "PATH : " << path << std::endl;

	if ((pid = fork()) < 0)
		throw Cgi::ForkException();

	if (!pid) /* child process */
	{
		dup2(client_sock, STDOUT_FILENO);

		execve("docs/html/cgi/script.py", NULL, env);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else /* parent process */
	{
		waitpid(pid, NULL, 0);
	}
}