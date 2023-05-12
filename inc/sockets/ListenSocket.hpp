/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:13:50 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/10 11:12:57 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENSOCKET_HPP

# define LISTENSOCKET_HPP

#include "BindSocket.hpp"

class ListenSocket : public BindSocket
{
	private:
		int	_backlog;
		int	_isListening;

		ListenSocket();
	public:
		/*
		** ------------------------------- Canonical form --------------------------------
		*/
		ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
		ListenSocket(const ListenSocket &copy);
		~ListenSocket();

		/*
		** ------------------------------- Operator overload --------------------------------
		*/
		const ListenSocket	&operator=(const ListenSocket &copy);

		/*
		** ------------------------------- Accessors --------------------------------
		*/
		int					getBacklog(void) const;
		int					getIsListening(void) const;

		/*
		** ------------------------------- Methods --------------------------------
		*/
			class ListenException : public std::exception
		{
			public:
				virtual const char *what() const throw() { return "Listen failed."; };
		};

		/*
		** ------------------------------- Methods --------------------------------
		*/
		int				listening(void) const;
};

# endif