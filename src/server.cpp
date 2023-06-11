#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include "server.h"
#include "threadpool.h"

Server::Server(int port) :
    m_port(port),
    m_sockfd(-1),
    m_running(false)
{}

void Server::start() {
    // Create socket
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd < 0) {
        std::cerr << "Error: Failed to create socket" << std::endl;
        return;
    }

    // Bind socket to address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        //std::cerr << "Error: Failed to bind socket to address" << std::endl;
		perror("bind failed");       
        return;
    }

    // Listen for connections
    if (listen(m_sockfd, 10) < 0) {
       // std::cerr << "Error: Failed to listen for connections" << std::endl;
       perror("listen failed");
	   	return;
    }

    // Start accepting connections in a separate thread
    m_running = true;
    ThreadPool pool(10); // 创建线程池，大小为10
    while (m_running) {
    int connfd = accept(m_sockfd, NULL, NULL);
    if (connfd >= 0) {
        pool.add_task([connfd, this]() {
            m_router.route(connfd);
            close(connfd);
        });
    }
	} 

}

void Server::stop() {
    m_running = false;
    close(m_sockfd);
}

void Server::add_handler(std::string path, Handler* handler) {
    m_router.add_handler(path, handler);
}

