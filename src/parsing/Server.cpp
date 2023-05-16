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

#include "./inc/Parsing.hpp"

Server::Server(std::string &ServerBlock) {
    std::istringstream iss(ServerBlock);
    std::string line;
    getline(iss, line);
    while (getline(iss, line))
    {
        std::istringstream iss_line(line);
        std::string key, value, location;
        getline(iss_line, key, ' ');
        RemoveTab(key);
        getline(iss_line, value, ';');
        setter(key, value, iss, location);
    }
    PrintServer();
}


Server::Server(const Server &rhs)
{
    *this = rhs;
}

Server &Server::operator=(const Server &rhs)
{
    if (this != &rhs)
    {
        this->_port = rhs._port;
        this->_host = rhs._host;
        this->_server_name = rhs._server_name;
        this->_error_page = rhs._error_page;
        this->_client_max_body_size = rhs._client_max_body_size;
        this->_root = rhs._root;
        this->_index = rhs._index;
        this->_location = rhs._location;
    }
    return (*this);
}

Server::~Server() {}

void    Server::setter(std::string &key, std::string &value, std::istringstream &iss, std::string &location)
{
    if (!key.compare("listen"))
         setPortMBS(key, value);
    else if (!key.compare("host"))
        setHostDir(value);
    else if (!key.compare("server_name"))
        setServerNameDir(value);
    else if (!key.compare("error_page"))
        setErrorPageDir(value);
    else if (!key.compare("client_max_body_size"))
        setPortMBS(key, value);
    else if (!key.compare("root"))
        this->_root = value;
    else if (!key.compare("index"))
        this->_index = value;
    else if (!key.compare("location"))
    {
        getline(iss, location, '}');
        this->_location.push_back(Location(location, value));
    }
}


void    Server::PrintServer()
{
    std::cout << "SERVER BLOCK START\n";

    for (std::vector<int>::iterator it = this->_port.begin(); it != this->_port.end(); ++it)
    {
        std::cout << "port: " << *it << std::endl;
    }
    std::cout << "host: " << this->_host << std::endl;
    for (std::vector<std::string>::iterator it = this->_server_name.begin(); it != this->_server_name.end(); ++it)
    {
        std::cout << "server name: " << *it << std::endl;
    }
    for (std::map<int, std::string>::iterator it = this->_error_page.begin(); it != this->_error_page.end(); ++it)
    {
        std::cout << "Error code: " << it->first << std::endl;
        std::cout << "Error page: " << it->second << std::endl;   
    }
    std::cout << "CMBS: " << this->_client_max_body_size << std::endl;
    std::cout << "root: " << this->_root << std::endl;
    std::cout << "index: " << this->_index << std::endl;
    for (std::vector<Location>::iterator it = this->_location.begin(); it != this->_location.end(); ++it)
    {
        std::cout << "location type: " << it->getLocationType() << std::endl;
        std::cout << "root: " << it->getRoot() << std::endl;
        std::cout << "autoindex: " << it->getAutoindex() << std::endl;
        for (std::vector<std::string>::iterator itA = it->getAllowMethods().begin(); itA != it->getAllowMethods().end(); ++itA)
        {
            std::cout << "allow methods: " << *itA << std::endl;
        }
        std::cout << "index: " << it->getIndex() << std::endl;
        std::cout << "return: " << it->getReturn() << std::endl;
        std::cout << "alias: " << it->getAlias() << std::endl;
    }

    std::cout << "SERVER BLOCK END\n";
    std::cout << "\n";
}

void    Server::setPortMBS(std::string &key, std::string &value)
{
    // std::cout << "value: " << value << std::endl;
    int i, port;

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
    if (!key.compare("listen"))
    {
        port = atoi(value.c_str());
        this->_port.push_back(port);
    }
    else
        this->_client_max_body_size = atoi(value.c_str());
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
    this->_host = value;
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
}