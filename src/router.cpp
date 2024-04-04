#include <iostream>
#include<sstream>
#include <cstring>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "router.h"
#include "static_handler.h"

// using namespace std;

void Router::add_handler(std::string cgi, Handler* handler) {
    // routes.push_back({cgi, handler});
    routes[cgi]=handler;
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
    Request req;
    std::stringstream ss(request);
    std::string line;

    // 解析请求行
    std::getline(ss, line);
    std::string method, path, version;
    ss>>method>>path>>version;
    req.set_method(method);
    req.set_path(path);
    req.set_version(version);

    // 解析请求头
    while (std::getline(ss, line) && line != "\r") {
        auto pos = line.find(": ");
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 2);
            req.set_header(key,value);
        }
    }

    // 获取请求体
    std::string body;
    std::getline(ss, body);
    auto pos = line.find("&");
    if (pos != std::string::npos) {
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        req.set_param(key,value);
    }

    // Find handler for path
    // std::string path=req.get_path();
    // std::cout<<path<<std::endl;
    // Handler* handler = nullptr;
    // for (int i=1;i<routes.size();i++) {
    //     if (path.find(routes[i].cgi) != std::string::npos) {
    //         handler = routes[i].handler; //多态
    //         break;
    //     }
    // }

    // Handle request
    Response res;
    if (!routes.count(path.substr(1))) {
        // std::cout<<"No StaticHandler"<<std::endl;
        routes["static"]->handle(req, res);//多态
    } else {// 默认使用StaticHandler
        // std::cout<<"StaticHandler"<<std::endl;
        routes[path.substr(1)]->handle(req, res);//多态
    }

    // Write response
    std::string response = res.to_response();
    if (write(connfd, response.c_str(), response.size()) < 0) {
        std::cerr << "Error: Failed to write response" << std::endl;
    }
}

