/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:24:14 by hdony             #+#    #+#             */
/*   Updated: 2023/05/24 15:33:15 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing/Parsing.hpp"

void    RemoveTab(std::string &key)
{
	int i = 0;
	int j = 0;
	while (key[j])
	{
		if (key[i] == '\t')
			i++;
		j++;
	}
	key.erase(0, i);
}