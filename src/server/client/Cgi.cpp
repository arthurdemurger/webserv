/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:37:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/29 17:12:08 by ademurge         ###   ########.fr       */
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
** ------------------------------- ACCESSOR --------------------------------
*/
int			Cgi::get_status(void) const { return (_status); };
std::string	Cgi::get_response(void) const { return (_response); };
void		Cgi::set_response(std::string rsp) { _response = rsp; };

/*
** ------------------------------- METHODS --------------------------------
*/

int Cgi::launch(int client_sock, char **env, std::string path, std::string body)
{
	std::string	response = "";
	int pipe_in[2]; // Tube pour l'entrée standard du script CGI
	int pipe_out[2]; // Tube pour la sortie du script CGI
	pid_t pid;
	int status;

	if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0)
	{
		perror("pipe");
		return (-1);
	}
	if ((pid = fork()) < 0)
	{
		perror("fork");
		return (-1);
	}

	if (!pid) // child process
	{
		// Processus enfant : exécute le script CGI
		close(pipe_in[1]);
		close(pipe_out[0]);

		// Rediriger l'entrée standard (stdin) vers le côté de lecture du tube d'entrée
		if (dup2(pipe_in[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (-1);
		}

		close(pipe_in[0]);

		// Rediriger la sortie standard (stdout) vers le côté d'écriture du tube de sortie
		if (dup2(pipe_out[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (-1);
		}

		close(pipe_out[1]);

		execve(path.c_str(), NULL, env);
		perror("execve");
		exit (EXIT_FAILURE);
	}
	else // parent process
	{
		close(pipe_in[0]);
		close(pipe_out[1]);

		// Écrire les données de la requête POST dans le tube d'entrée du script CGI
		if (write(pipe_in[1], body.c_str(), body.length()) < 0)
		{
			perror("write");
			return (-1);
		}
		close(pipe_in[1]);

		char buffer[BUF_SIZE];

		int n;
		while ((n = read(pipe_out[0], buffer, BUF_SIZE)) > 0)
		{
			response.append(buffer, n);
			if (write(client_sock, buffer, n) < 0)
			{
				perror("write");
				return (-1);
			}
		}
		if (n < 0)
		{
			perror("read");
			return (-1);
		}
		close(pipe_out[0]);

		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			_status = WEXITSTATUS(status);
	}
	_response = response;
	return (0);
}
