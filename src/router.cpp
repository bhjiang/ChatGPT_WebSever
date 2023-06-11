#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "router.h"

void Router::add_handler(std::string path, Handler* handler) {
    m_routes.push_back({path, handler});
}

void Router::route(int connfd) {
    // Read request
    char buf[4096];
    int n = read(connfd, buf, sizeof(buf));
    if (n < 0) {
        std::cerr << "Error: Failed to read request" << std::endl;
        return;
    }

    // Parse request
    std::string request(buf, n);
    //std::cout<<request;
    size_t pos = request.find(" ");
    if (pos == std::string::npos && !request.empty()) {
        std::cerr << "Error: Invalid request" << std::endl;
        std::cout << request << std::endl;
        return;
    }
    std::string method = request.substr(0, pos);
    request.erase(0, pos + 1);
    pos = request.find(" ");
    if (pos == std::string::npos && !request.empty()) {
        std::cerr << "Error: Invalid request" << std::endl;
        std::cout << request << std::endl;
        return;
    }
    std::string path = request.substr(0, pos);
    request.erase(0, pos + 1);
	
    // Find handler for path
    Handler* handler = nullptr;
    for (auto& route : m_routes) {
        if (route.path == path) {
            handler = route.handler;
            break;
        }
    }

    // Handle request
    if (handler) {
        Request req(method, path, request);
        Response res;
        handler->handle(req, res);
        std::string response = res.to_string();
        if (write(connfd, response.c_str(), response.size()) < 0) {
            std::cerr << "Error: Failed to write response" << std::endl;
        }
    } else {
        std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
        if (write(connfd, response.c_str(), response.size()) < 0) {
            std::cerr << "Error: Failed to write response" << std::endl;
        }
    }
}

