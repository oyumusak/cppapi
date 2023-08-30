#include "../lib/server.hpp"

server::server()
{
    makeSv(this);
}

int server::createSoket(int port)
{
    struct sockaddr_in addr;

    this->serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverFd < 0)
    {
        std::cerr << "Server Socket Cannot Created!" << std::endl;
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(this->serverFd, (struct sockaddr *)&addr, sizeof(sockaddr_in)) < 0) {
        std::cerr << "Bind Failed!" << std::endl;
        close(this->serverFd);
        exit(EXIT_FAILURE);
    }

    if (listen(this->serverFd, 1024) == -1)
    {
        std::cerr << "Bind Failed!" << std::endl;
        close(this->serverFd);
        exit(EXIT_FAILURE);
    }

    return (this->serverFd);
}

void server::findMaxFd()
{
    this->maxFd = this->serverFd;
    for (std::vector<client>::iterator begin = this->clients.begin(); begin != this->clients.end(); begin++)
    {
        if (this->maxFd < (*begin).cliFd)
            this->maxFd = (*begin).cliFd;
    }
}

std::string	server::add_headers(std::string htmlstr, std::string type, int code)
{
	std::string headers;
	headers += "HTTP/1.1 " + std::to_string(code) + " OK\n";
	//headers += "Date: " + get_time_stamp() + "\n";
	headers += "Server: webserv/1.00\n";
	headers += "Content-Type: " + type + "\n";
	headers += "Content-Length: " + std::to_string(htmlstr.size()) + "\n";
	headers += "Connection: close\n";
	std::string res;
	res = headers + "\n" + htmlstr;
	return (res);
}

void server::createServer(int port)
{
    this->createSoket(port);
    this->status = 0;

    memset(&readFd, 0, sizeof(fd_set));
    memset(&writeFd, 0, sizeof(fd_set));
    memset(&writeSupFd, 0, sizeof(fd_set));
    memset(&readSupFd, 0, sizeof(fd_set));

	FD_SET(this->serverFd, &readFd);
    while(1)
    {
        this->findMaxFd();
        while (status == 0)
        {
            writeSupFd = writeFd;
            readSupFd = readFd;
            status = select(this->maxFd + 1, &readSupFd, &writeSupFd, NULL, 0);
        }
        if (status == -1)
        {
            std::cerr << "Select Error!" << std::endl;
			status = 0;
            continue;
        }
		this->newConn();
		this->reqHandler();
		this->respHandler();   
    }
}

void server::handlePost(std::string dir, std::function<std::string(client)> func)
{
    this->postFunctions.insert(std::make_pair(dir, func));
}

void server::handleGet(std::string dir, std::function<std::string(client)> func)
{
    this->getFunctions.insert(std::make_pair(dir, func));
}