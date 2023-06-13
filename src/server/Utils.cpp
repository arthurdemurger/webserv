/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:24:14 by hdony             #+#    #+#             */
/*   Updated: 2023/06/13 13:54:06 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/server/Utils.hpp"

void    RemoveTab(std::string &key)
{
   size_t	pos;

	pos = key.find_first_not_of('\t', 0);
	if (pos != std::string::npos)
	{
		key.erase(0, pos);
	}
    while (!key.empty() && (key.back() == '\t')) 
	{
	   key.pop_back();
    }
}