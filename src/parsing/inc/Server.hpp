#ifndef SERVER
# define SERVER

# include "Parsing.hpp"

class   Location;

class Server
{
private:
    std::vector<int>            _port;
    std::string                 _host;
    std::vector<std::string>    _server_name;
    std::map<int, std::string>  _error_page;
    int                         _client_max_body_size;
    std::string                 _root;
    std::string                 _index;
    std::vector<Location>       _location;

public:
    Server(std::string &ServerBlock);
    ~Server();

    
    void    PrintServer();
    
    void    setPortMBS(std::string &key, std::string &rhs);
    void    setHostDir(std::string &rhs);
    void    setServerNameDir(std::string &rhs);
    void    setErrorPageDir(std::string &rhs);
    void    setClientMaxBodySize(std::string &rhs);
    void    setRootDir(std::string &value);

    // std::vector<int>    &getPort();
};

#endif
