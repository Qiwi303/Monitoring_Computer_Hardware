#pragma once 

#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Structures.h"
#include <unordered_map>
#include <thread>
#include <sys/epoll.h>
#include <iostream> 
#include <fcntl.h>
#include <string.h>

class Client{
public:
    Client();
    ~Client();
    void run();
    void addServer(std::string& ip);
    bool isServerAccessible(std::string& ip);
    Monitoring* getLink(std::string& ip);
private:
    int dataSock = -1;
    int epollfd = -1;
    sockaddr_in server{};
    std::unordered_map<int, std::string> sysMap;
    std::unordered_map<std::string, Monitoring> serverInfo;
    std::unordered_map<int, std::vector<char>> serverBuf;
    std::vector<struct epoll_event> events;
    int monSize = sizeof(Monitoring);
};
