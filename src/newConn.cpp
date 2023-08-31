#include "../lib/server.hpp"

void server::newConn()
{
    int cliFd;
    sockaddr_in cli;
    socklen_t cliLen;
    cliLen = sizeof(cli);

    if (FD_ISSET(this->serverFd, &readSupFd))
    {
        client tmp;
        cliFd = accept(this->serverFd, (sockaddr *)&cli, &cliLen);
        tmp.ipAddr = inet_ntoa(cli.sin_addr);
        tmp.cliFd = cliFd;
        this->clients.push_back(tmp);

		FD_SET(cliFd, &readFd);
        std::cout << "New Cli Conn!" << std::endl;
        status = 0;
    }
}