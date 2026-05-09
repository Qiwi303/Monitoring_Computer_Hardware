#include "Client.h"

Client::Client(){
    sock = socket(AF_INET, SOCK_DGRAM, SO_REUSEADDR | SO_RCVTIMEO);
    if(sock == -1){
        throw std::runtime_error("Failed to create socket");
    }
    
    int opt = 1;
    int options = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(options == -1){
        throw std::runtime_error("Failed to set socket option #1");
    }
    
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    options = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if(options == -1){
        throw std::runtime_error("Failed to set socket option #2");
    }
         

    server.sin_family = AF_INET;
    server.sin_port = htons(Network::PORT);
    server.sind_addr.s_addr = htonl(INADDR_ANY);

    int binded = bind(sock, (sockaddr*)&server, sizeof(server));

    if(binded == -1){
        throw std::runtime_error("Failed to bind socket to server");
    }

}

void Client::findServer(){
    int attempts = 0;
    char buff[128];   
    socklen_t len = sizeof(server);
    int n = -1;
    
    while(attempts < 3){
        n = recvfrom(sock, buff, sizeof(buf) - 1, 0, (sockaddr*)&server, &len);
        
        if(n != -1){
            buff[n] = '\0';
            if(serverName == buff) break;
        }
        
        attempts++;
    }
    
    if(attempts == 3){
        throw std::runtime_error("Failed to find server");
    }
}


void Client::run(){
    

    while(true){
        

    }

}

