#include "Server.h"

Server::Server(): point(std::make_shared<ShmWrapper>(false)){    
    dataSock = socket(AF_INET, SOCK_STREAM, 0);
    if(dataSock == -1){
        throw std::runtime_error("Failed to create socket");
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(Network::PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
      
    int binded = bind(dataSock, (struct sockaddr*)& server, sizeof(server));
    if(binded < 0){
        throw std::runtime_error("Failed to bind");
    } 
}


void Server::run(){
    int clientsInQ = 1;    

    int listened = listen(dataSock, clientsInQ);
    if(listened < 0){
        throw std::runtime_error("Failed to listend");
    }
      

    while(true){
        socklen_t len = sizeof(clients);
        clientSock = accept(dataSock, (struct sockaddr*)& clients, &len);
        if(clientSock < 0){
            throw std::runtime_error("Failed to accept clients");
        }
        
        int sended = 1;
        while(sended > 0){
            sended = send(clientSock, point->getPtr(), sizeof(Monitoring), 0);
            sleep(2); 
        }
    }
}

Server::~Server(){
    if(dataSock != -1){
        close(dataSock);
    }
    if(clientSock != -1){
        close(clientSock);
    }
}





