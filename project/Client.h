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
#include <mutex>
#include <atomic>

class Client{
public:
    Client();
    ~Client();
    void run();
    void addServer(const std::string& ip);
    bool isServerAccessible(const std::string& ip);
    Monitoring* getLink(const std::string& ip);
    void stopRunning();

    void removeServer(const std::string& ip);

private:
    std::mutex mtx;
    int dataSock = -1;
    int epollfd = -1;
    sockaddr_in server{};
    std::unordered_map<int, std::string> sysMap;
    std::unordered_map<std::string, Monitoring> serverInfo;
    std::unordered_map<int, std::vector<char>> serverBuf;
    std::vector<struct epoll_event> events;
    int monSize = sizeof(Monitoring);

    std::atomic<bool> running = true;
};
