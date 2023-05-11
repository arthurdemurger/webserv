#ifndef SERVER
# define SERVER

# include <iostream>
# include <vector>
# include <map>
# include <sstream>

class Server
{
private:
    std::vector<std::string>    _server_conf;
    int                         _listen_dir;
    std::string                 _host;
    std::vector<std::string>    _server_name;
    std::map<int, std::string>  _error_page;
    int                         _client_max_body_size;
    std::string                 _root;
    std::string                 _index;

public:
    Server(std::string &ServerBlock);
    ~Server();

    void    ServerBlockErase(std::string &ServerBlock);
    void    FindListenDir(std::string &ServerBlock);
    
    void    RemoveTab(std::string &key);
    
    void    setListenDir(std::string &rhs);
    void    setHostDir(std::string &rhs);
    void    setServerNameDir(std::string &rhs);
    void    setErrorPageDir(std::string &rhs);
    void    setClientMaxBodySize(std::string &rhs);
    void    setRootDir(std::string &value);
};

#endif
