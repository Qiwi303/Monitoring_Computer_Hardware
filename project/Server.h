#pragma once 

#include <vector>
#include <sys/socket.h>
#include <arpa/inte.h>
#include <unistd.h>
#include "Structures.h"
#include <map>
#include <thread>

Class Server{
public:
    Server(){}
    ~Server();
    void run();

private:
    int dataSock = -1;
    sockaddr_in server{};
    std::map<Structures> clients;
};
