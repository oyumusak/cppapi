#include "../lib/server.hpp"

void server::reqHandler()
{
    int readed;

    for (std::vector<client>::iterator begin = this->clients.begin(); begin != this->clients.end() && status; begin++)
    {
        if (FD_ISSET((*begin).cliFd, &readSupFd))
        {
            char buff[1024];
            readed = read((*begin).cliFd, buff, 1024);
            if (readed == -1)
            {
				FD_CLR((*begin).cliFd, &readFd);
				FD_CLR((*begin).cliFd, &writeFd);
                close((*begin).cliFd);
                clients.erase(begin);
                std::cerr << "Read Error!" << std::endl;
            }
            else if (readed == 0)
            {
				FD_CLR((*begin).cliFd, &readFd);
				FD_CLR((*begin).cliFd, &writeFd);
                close((*begin).cliFd);
                clients.erase(begin);
                std::cout << "Connection Closed From Client!" << std::endl;
            }
            else
            {
				buff[readed] = 0;
                (*begin).req += buff;
				(*begin).reqParser(buff);
                //std::cout << (*begin).req << std::endl;
                FD_CLR((*begin).cliFd, &readFd);
                FD_SET((*begin).cliFd, &writeFd);
            }
            status = 0;
            break;
        }
    }
}