#ifndef PARSECONFIGFILE

# define PARSECONFIGFILE

# include "iostream"
# include "fstream"

class ParseConfigFile
{
private:
    /* data */
public:
    ParseConfigFile();
    ~ParseConfigFile();

    void    ConfigParsing(std::string path);
    void    ConfigReading(std::string path);
};

#endif