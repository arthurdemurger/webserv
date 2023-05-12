#ifndef LOCATION
# define LOCATION

# include "Parsing.hpp"

class Location
{
    private:
        std::string _location_type;
        std::string _root;
        bool        _autoindex;
        std::vector<std::string>    _allow_methods;
        std::string _index;
        std::string _return;
        std::string _alias;

    public:
        Location(std::string LocationBlock, std::string LocationType);
        ~Location();

        void    setLocType(std::string &LocationType);
        void    setAllowMethods(std::string &value);

        std::string &getLocationType();
        std::string &getRoot();
        bool    &getAutoindex();
        std::vector<std::string>    &getAllowMethods();
        std::string &getIndex();
        std::string &getReturn();
        std::string &getAlias();

};

# endif