#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
#include "handler.h"

class Router {
public:
    void add_handler(std::string path, Handler* handler);
    void route(int connfd);
private:
    struct Route {
        std::string path;
        Handler* handler;
    };
    std::vector<Route> m_routes;
};

#endif // ROUTER_H

