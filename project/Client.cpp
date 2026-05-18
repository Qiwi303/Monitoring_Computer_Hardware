#include "Client.h"

Client::Client(){
    searchSock = socket(AF_INET, SOCK_DGRAM, 0);
    if(searchSock == -1){
        throw std::runtime_error("Failed to create socket");
    }
    
    int opt = 1;
    int options = setsockopt(searchSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(options == -1){
        throw std::runtime_error("Failed to set socket option #1");
    }
    
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    options = setsockopt(searchSock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if(options == -1){
        throw std::runtime_error("Failed to set socket option #2");
    }
         
    server.sin_family = AF_INET;
    server.sin_port = htons(Network::PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    
    int binded = bind(searchSock, (sockaddr*)&server, sizeof(server));
    
    if(binded == -1){
        throw std::runtime_error("Failed to bind socket to server");
    }
    
}

void Client::findServer(){ 
    int attempts = 0;
    char buff[128];
    socklen_t len = 128;  
    int n = -1;
    
    while(attempts < 3){
        n = recvfrom(searchSock, buff, sizeof(buff) - 1, 0, (sockaddr*)&server, &len);
        
        if(n != -1){
            buff[n] = '\0';
            if(Network::serverName == buff) break;
        }
        
        attempts++;
    }
    
    if(attempts == 3){
        throw std::runtime_error("Failed to find server");
    }

    server.sin_port = htons(Network::PORT);
    
}


void Client::run(){
    while(true){
        findServer();
    
        dataSock = socket(AF_INET, SOCK_STREAM, 0);

        int connected = connect(dataSock, (sockaddr*)&server, sizeof(server));
        if(connected == -1){
            throw std::runtime_error("Failed to conenct to server");
        }

        while(true){
            int sended = send(dataSock, point->getPtr(), sizeof(Monitoring), 0);
            if(sended == -1){
                break;
            }
            sleep(1); 
        }

        close(dataSock);
        dataSock = -1;
    }
}

Client::~Client(){
    if(dataSock != -1){
        close(dataSock);
    }
    
    if(searchSock != -1){
        close(searchSock);
    }

}
:wq

