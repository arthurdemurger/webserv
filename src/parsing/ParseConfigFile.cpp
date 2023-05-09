/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfigFile.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:19:59 by hdony             #+#    #+#             */
/*   Updated: 2023/05/09 15:54:44 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfigFile.hpp"

ParseConfigFile::ParseConfigFile() {}

ParseConfigFile::~ParseConfigFile() {}

void    ParseConfigFile::ConfigReading(std::string path)
{
    
}

void    ParseConfigFile::ConfigParsing(std::string path)
{
    char            ch;
    std::ifstream   ifs;
    std::string     str;

    ifs.open(path, std::ofstream::in);
    if (ifs.fail())
    {
        std::cout << "error openin file\n";
        exit (EXIT_FAILURE);
    }
    while (std::getline(ifs, str))
    {
        std::cout << str << std::endl;
    }
}