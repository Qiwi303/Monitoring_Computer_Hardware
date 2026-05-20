#pragma once 

#include <vector>
#include <sys/socket.h>
#include <arpa/inte.h>
#include <unistd.h>
#include "Structures.h"
#include <map>
#include <thread>
#include <sys/epoll.h>

#define MAX_EVENTS 10

Class Server{
public:
    Server(){}
    ~Server();
    void run();

private:
    int dataSock = -1;
    int epollfd = -1;
    sockaddr_in server{};
    std::unordered_map<std::string, Monitoring> serverInfo;
    std::vector<struct epoll_event> events(MAX_EVENTS);
};
