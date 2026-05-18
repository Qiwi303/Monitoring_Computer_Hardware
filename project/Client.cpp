#include "Client.h"

Client::Client(): point(std::make_shared<ShmWrapper>(false)){
    
    dataSock = socket(AF_INET, SOCK_STREAM, 0);
    if(dataSock == -1){
        throw std::runtime_error("Failed to create socket");
    }
    
    int opt = 1;
    int options = setsockopt(dataSock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
    if(options == -1){
        throw std::runtime_error("Failed to set socket option #1");
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons(Network::PORT);
    server.sin_addr.s_addr = htonl(INADDR_BROADCAST);
      
}


void Client::run(){
    while(true){
        int sended = sendto(dataSock, point->getPtr(), sizeof(Monitoring), 
                            0, (struct sockaddr*)&server, sizeof(server));
        if(sended == -1){
            //some log stuff;
        }
        sleep(2); 
    }

}

Client::~Client(){
    if(dataSock != -1){
        close(dataSock);
    }

}


