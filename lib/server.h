#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <thread>
#include <vector>
#include "router.h"

class Server {
public:
    Server(int port);
    void start();
    void stop();
    void add_handler(std::string path, Handler* handler);
private:
    int m_port;
    int m_sockfd;
    bool m_running;
    //std::vector<std::thread> m_threads;
    Router m_router;
};

#endif // SERVER_H

