#include "../lib/server.hpp"

server *getSetServer(server *sw, int param)
{
    static server *data = 0;

    if (param == 1)
        data = sw;
    return (data);
}

void	end(int signal, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)signal;
	(void)siginfo;

    server *server = getSetServer(0, 0);

    for(std::vector<client>::iterator begin = server->clients.begin(); begin != server->clients.end(); begin++)
    {
        close((*begin).cliFd);
    }
    close(server->serverFd);
    std::cout << "Signal Handler Running!" << std::endl;
	exit(0);
}



server *makeSv(server *tmp)
{
	static struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = end;

    sigaction(SIGINT, &act, NULL);

    getSetServer(tmp, 1);

    return (tmp);
}