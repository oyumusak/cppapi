#pragma once
# include "map"
# include "iostream"
# include "unistd.h"

class client
{
    public:
        void	reqParser(char *req);
        int cliFd;
        std::string req;
        std::string method;
        std::string dir;
        std::string queryString;
        std::string protocol;
        std::string serverName;
        std::map<std::string, std::string>	headers;
        int postLen;
        std::string postVal;
        int status;
};