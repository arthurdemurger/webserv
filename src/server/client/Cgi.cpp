/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:37:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/08 16:36:21 by hdony            ###   ########.fr       */
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

void Cgi::launch(int client_sock, char **env, std::string path, std::string body)
{
	int pipe_in[2]; // Tube pour l'entrée standard du script CGI
	int pipe_out[2]; // Tube pour la sortie du script CGI
	pid_t pid;

	if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0) {
		perror("pipe");
		return;
	}
	if ((pid = fork()) < 0)
		throw Cgi::ForkException();

	if (!pid) // child process
	{
		// Processus enfant : exécute le script CGI
		close(pipe_in[1]);
		close(pipe_out[0]);

		// Rediriger l'entrée standard (stdin) vers le côté de lecture du tube d'entrée
		dup2(pipe_in[0], STDIN_FILENO);
		close(pipe_in[0]);

		// Rediriger la sortie standard (stdout) vers le côté d'écriture du tube de sortie
		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_out[1]);

		execve(path.c_str(), NULL, env);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else // parent process
	{
		close(pipe_in[0]);
		close(pipe_out[1]);

		// Écrire les données de la requête POST dans le tube d'entrée du script CGI
		write(pipe_in[1], body.c_str(), body.length());
		close(pipe_in[1]);

		char buffer[1000];

		int n;
		while ((n = read(pipe_out[0], buffer, BUF_SIZE)) > 0) {
			write(client_sock, buffer, n);
		}
		close(pipe_out[0]);

		waitpid(pid, NULL, 0);
	}
}

