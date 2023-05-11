#ifndef PARSECONF
# define PARSECONF

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include "Server.hpp"

class ParseConf
{
private:
    std::ifstream               _ifs;
    std::string                 _content;
    int                         _server_nb;
    std::vector<int>            _vec_start_block;
    std::vector<int>            _vec_end_block;
    std::vector<std::string>    _vec_config;
    std::vector<Server>    _vec_server;

public:
    ParseConf();
    ~ParseConf();

    const std::vector<std::string>    &getVecServConf() const;
    const int   &getServerNb() const;

    std::string ConfigReading(std::string &path);
    void        ConfigParsing(std::string path);
    void        ServerCount();
    void        PopulateVecConfig();
    void        ServerBlockStart();
    void        ServerBlockEnd();
    void        PopulateServer();

    // void        ParseServer(std::string &ServerBlock, Server &Server);
    void        FindListenDir(std::string &ServerBlock, Server &Server);
    void        ServerBlockErase(std::string &ServerBlock);
};

#endif