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


class Server{
public:
    Server();
//    void findServer();
    void run();    
    ~Server();

private:
    std::shared_ptr<ShmWrapper> point;
//    int searchSock = -1;
    int dataSock = -1;
    int clientSock = -1;
    int index = -1;
    sockaddr_in server{};
    sockaddr_in clients{};    
    
    //std::string serverIP = "255.255.255.255";
    //std::string serverName = "MONI";

};
