/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:37:52 by ademurge          #+#    #+#             */
/*   Updated: 2023/06/06 17:38:28 by hdony            ###   ########.fr       */
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

/* 
A CGI script reads the POST string from the STDIN and send their content to the STDOUT.
Redirect std::in & std::out to the read and write end of the pipe
*/
void Cgi::executeCGI(const std::string& cgiPath, char* const* envp) {
  // std::cout << "env: " << envp << std::endl;
  //creation du pipe
	int pipefd[2];
    if (pipe(pipefd) == -1) {
      perror("pipe");
      return;
    }

    //creation d'un nouveau processus en dupliquant l'existant
	pid_t pid = fork();
    if (pid == 0)
    {
      // Child process
      close(pipefd[0]); // Close the read end of the pipe, nothing to read from 

      // Redirect stdout to the write end of the pipe as the cgi script writes on stdout
      if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        close(pipefd[1]);
        exit(EXIT_FAILURE);
      }
    /*
      To clarify, after duplicating the write end of the pipe using dup2, it is generally a good practice to close the original file descriptor (in this case, pipefd[1]) to ensure proper resource management.
      Closing the original file descriptor does not affect the duplicated file descriptor that is now connected to the pipe.
    */
    close(pipefd[1]); // Close the write end of the pipe
    // Execute the CGI program, write to the fd
      if (execvp(cgiPath.c_str(), envp) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
      }
    } 
    else if (pid < 0) {
      // Handle fork error, if any
      perror("fork");
    } 
    else {
      // Parent process
      close(pipefd[1]); // Close the write end of the pipe

      // Read the output from the CGI program
      char buffer[1024];
      ssize_t bytesRead;
      std::string output;

      while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        std::cout << "buffer: " << buffer;
        write(6, buffer, strlen(buffer));
	  	  output.append(buffer, bytesRead);
      }

      close(pipefd[0]); // Close the read end of the pipe

      int status;
      waitpid(pid, &status, 0);
      // Handle the exit status of the child process if needed

      // std::cout << "CGI Program Output:\n" << output << std::endl;
    }
  }
