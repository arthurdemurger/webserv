/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:24:56 by hdony             #+#    #+#             */
/*   Updated: 2023/05/16 17:20:01 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/Parsing.hpp"

int main(int ac, char *argv[])
{
    Config config_inst;
    if (ac == 1 || ac == 2)
    {
        if (ac == 1)
            config_inst.ConfigParsing("../../config/default.conf");
        else
            config_inst.ConfigParsing(argv[1]);
    }
    return (0);
}