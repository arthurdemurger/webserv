/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdony <hdony@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:39:51 by hdony             #+#    #+#             */
/*   Updated: 2023/05/11 11:40:39 by hdony            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string &ServerBlock) {
    std::istringstream iss(ServerBlock);
    std::string line;
    getline(iss, line);
    while (getline(iss, line))
    {
        // std::cout << "line: " << line << std::endl;
        // std::cout << "key: " << key << std::endl;
        // std::cout << "value: " << value << std::endl;
        std::istringstream iss_line(line);
        std::string key, value;
        getline(iss_line, key, ' ');
        RemoveTab(key);
        getline(iss_line, value, ';');
        if (!key.compare("listen"))
            setListenDir(value);
        else if (!key.compare("host"))
            setHostDir(value);
        else if (!key.compare("server_name"))
            setServerNameDir(value);
        else if (!key.compare("error_page"))
            setErrorPageDir(value);
        else if (!key.compare("client_max_body_size"))
            setListenDir(value);
        else if (!key.compare("root"))
            this->_root = value;
        else if (!key.compare("index"))
            this->_root = value;
        else
        {
            
        }
    }
}

Server::~Server() {}

void    Server::RemoveTab(std::string &key)
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

void    Server::setListenDir(std::string &value)
{
    int i;

    i = 0;
    while (isdigit(value[i]))
    {
        i++;
    }
    if (i != value.size())
    {
        std::cout << "Error: listen directive format\n";
        exit(EXIT_FAILURE);   
    }
    if (!value.compare("listen"))
        this->_listen_dir = atoi(value.c_str());
    else
        this->_client_max_body_size = atoi(value.c_str());
    // std::cout << "Listen Dir: " << this->_listen_dir << std::endl;
}

void    Server::setHostDir(std::string &value)
{

    std::istringstream iss(value);
    std::string token;
    int i;
    int count;

    count = 0;
    while (getline(iss, token, '.'))
    {
        for (std::string::iterator it = token.begin(); it != token.end(); ++it)
        {
            if (!isdigit(*it))
            {
                std::cout << "Error: Host Directive format\n";
                exit(EXIT_FAILURE);
            }
        }
        i = atoi(value.c_str());
        if (i < 0 || i > 255 )
        {
            std::cout << "Error: Host Directive format\n";
            exit(EXIT_FAILURE);
        }
        count++;
    }
    if (count != 4)
    {
        std::cout << "Error: Host Directive format\n";
        exit(EXIT_FAILURE);
    }
}

void    Server::setServerNameDir(std::string &value)
{
    std::istringstream iss(value);
    std::string token;

    while (getline(iss, token, ' '))
    {
        this->_server_name.push_back(token);
        // std::cout << "token: " << token << std::endl;
    }
}

void    Server::setErrorPageDir(std::string &value)
{
    std::istringstream iss(value);
    std::string token;
    int         key;
    std::string val;
    int i = 1;

    while (getline(iss, token, ' '))
    {
        if (!(i % 2))
            val = token;
        else
        {
            key = atoi (token.c_str());
        }
        i++;
    }
    this->_error_page.insert(std::pair<int, std::string>(key, val));
    // for (std::map<int, std::string>::iterator it = this->_error_page.begin(); it != this->_error_page.end(); ++it)
    // {
    //     std::cout << "key: " << it->first << std::endl;
    //     std::cout << "value: " << it->second << std::endl;   
    // }
}

void    Server::setRootDir(std::string &value)
{

}

void    Server::ServerBlockErase(std::string &ServerBlock)
{
    ServerBlock.erase(0, ServerBlock.find(";") + 1);
    std::cout << "Updated  string: " << ServerBlock << std::endl;
}