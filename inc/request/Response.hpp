/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:20:11 by ademurge          #+#    #+#             */
/*   Updated: 2023/05/12 12:22:33 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP

# define RESPONSE_HPP

#include <iostream>

class Response
{
	private:

	public:
		/*
		** ------------------------------- COPLIEN --------------------------------
		*/
		Response();
		~Response();
		Response(const Response &copy);
		Response &operator=(const Response &copy);
};


#endif //RESPONSE_HPP