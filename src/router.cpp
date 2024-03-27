#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "router.h"
#include "static_handler.h"

void Router::add_handler(std::string cgi, Handler* handler) {
    routes.push_back({cgi, handler});
}

void Router::route(int connfd) {
    // Read request
    char buf[4096];
    int n = read(connfd, buf, sizeof(buf));
    if (n < 0) {
        std::cerr << "Error: Failed to read request" << std::endl;
        return;
    }

    std::string request(buf, n);
    Request req(request);
	
    // Find handler for path
    std::string path=req.get_path();
    std::cout<<path<<std::endl;
    Handler* handler = nullptr;
    for (int i=1;i<routes.size();i++) {
        if (path.find(routes[i].cgi) != std::string::npos) {
            handler = routes[i].handler;
            break;
        }
    }

    // Handle request
    Response res;
    if (handler) {
        // std::cout<<"No StaticHandler"<<std::endl;
        handler->handle(req, res);
    } else {// 默认使用StaticHandler
        // std::cout<<"StaticHandler"<<std::endl;
        handler=routes[0].handler;
        handler->handle(req, res);
    }
    std::string response = res.to_response();
    if (write(connfd, response.c_str(), response.size()) < 0) {
        std::cerr << "Error: Failed to write response" << std::endl;
    }
}

