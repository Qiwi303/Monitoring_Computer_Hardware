#pragma once

#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
//#include <except>
#include "ShmWrapper.h"
#include <iostream>
#include <cerrno>


class Client{
public:
    Client();
    void findServer();
    void run();    
    ~Client();

private:
    std::shared_ptr<ShmWrapper> point;
    int searchSock = -1;
    int dataSock = -1;
    int index = -1;
    sockaddr_in server{};
    //std::string serverIP = "255.255.255.255";
    //std::string serverName = "MONI";

};
