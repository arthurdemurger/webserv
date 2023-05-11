/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:56 by hdony             #+#    #+#             */
/*   Updated: 2023/05/10 14:49:08 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConf.hpp"

int main(int ac, char *argv[])
{
    ParseConf config_parse_instance;
    if (ac == 1 || ac == 2)
    {
        if (ac == 1)
        {
            config_parse_instance.ConfigParsing("../../config/default.conf");
        }
        else
        {
            config_parse_instance.ConfigParsing(argv[1]);
        }
    }
    return (0);
}