/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:37:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/05 15:34:07 by ademurge         ###   ########.fr       */
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
	int		pipefd[2];
	pid_t	pid;


	if (pipe(pipefd) < 0)
		perror("pipe");
	if ((pid = fork()) < 0)
		throw Cgi::ForkException();

	if (!pid) /* child process */
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(path.c_str(), NULL, env);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else /* parent process */
	{
		waitpid(pid, NULL, 0);
		char buffer[1000];

		close(pipefd[1]);

		int n = read(pipefd[0], buffer, 1000);
		write (client_sock, buffer, strlen(buffer));
		close(pipefd[0]);
	}
}
