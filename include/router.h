#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
#include "handler.h"
#include <unordered_map>

class Router {
public:
    void add_handler(std::string cgi, Handler* handler);
    void route(int connfd);
private:
    struct Route {
        std::string cgi;
        Handler* handler;
    };
    std::vector<Route> routes;
};

#endif // ROUTER_H

