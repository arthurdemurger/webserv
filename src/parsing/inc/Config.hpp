#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Parsing.hpp"

class   Server;

class Config
{
private:
    std::ifstream               _ifs;
    std::string                 _content;
    int                         _server_nb;
    std::vector<int>            _vec_start_block;
    std::vector<int>            _vec_end_block;
    std::vector<std::string>    _vec_config;
    std::vector<Server>         _vec_server;

public:
    Config();
    ~Config();

    const std::vector<std::string>    &getVecServConf() const;
    const int   &getServerNb() const;

    std::string ConfigReading(std::string &path);
    void        ConfigParsing(std::string path);
    void        ServerCount();
    void        PopulateVecConfig();
    void        ServerBlockStart();
    void        ServerBlockEnd();
    void        PopulateServer();

    // void        PrintServer(Server &rhs);
};

#endif