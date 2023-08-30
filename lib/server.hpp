#pragma once

# include <iostream>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <string.h>
# include <unistd.h>
# include <vector>
# include "client.hpp"
# include <functional>
# include <csignal>

class server
{
    private:

        int maxFd;
        fd_set readFd;
        fd_set writeFd;
        fd_set writeSupFd;
        fd_set readSupFd;
        int status;
        std::map<std::string, std::function<std::string(client)> > postFunctions;
        std::map<std::string, std::function<std::string(client)> > getFunctions;
    public:
        int serverFd;
        std::vector<client> clients;
        server(); //default constructor
        int createSoket(int port);
        void createServer(int port);
        void findMaxFd(void);
        void newConn();
        void reqHandler();
        void respHandler();
        void handlePost(std::string dir, std::function<std::string(client)> func);
        void handleGet(std::string dir, std::function<std::string(client)> func);
        std::string	add_headers(std::string htmlstr, std::string type, int code);
};

server *makeSv(server *tmp);