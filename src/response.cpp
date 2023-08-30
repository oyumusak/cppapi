#include "../lib/server.hpp"

void server::respHandler()
{
    std::string resp = "404NotFound";

    for (std::vector<client>::iterator begin = clients.begin(); begin != clients.end() && status; begin++)
    {
        std::cout << (*begin).dir << std::endl;
        if (FD_ISSET((*begin).cliFd ,&writeSupFd))
        {
            if ((*begin).method == "POST")
            {
                for (std::map<std::string,std::function<std::string(client)> >::iterator it = postFunctions.begin(); it != postFunctions.end(); it++)
                {
                    if ((*it).first == (*begin).dir)
                    {
                        resp = (*it).second((*begin));
                        break;
                    }
                }
            }
            else if ((*begin).method == "GET")
            {
                for (std::map<std::string,std::function<std::string(client)> >::iterator it = getFunctions.begin(); it != getFunctions.end(); it++)
                {
                    if ((*it).first == (*begin).dir)
                    {
                        resp = (*it).second((*begin));
                        break;
                    }
                }
            } 
            resp = add_headers(resp, "text/html", 200);
            write((*begin).cliFd, resp.c_str(), resp.length());
			FD_CLR((*begin).cliFd, &readFd);
			FD_CLR((*begin).cliFd, &writeFd);
			close((*begin).cliFd);
			clients.erase(begin);
			status = 0;
			break;
        }
    }  
}