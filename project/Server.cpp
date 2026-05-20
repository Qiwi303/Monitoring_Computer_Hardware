#include "Server.h" 

Server::Server(){
        dataSock = socket(AF_INET, SOCK_STREAM, 0);
        if(dataSock < 0){
            throw std::runtime_error("Failed to create dataSock");
        }    
    
        server.sin_family = AF_INET;
        server.sin_port = htons(Network::PORT);
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        
        int binded = bind(beaconSock, (sockaddr*)&server, sizeof(server));
    
        if(binded == -1){
            throw std::runtime_error("Failed to bind socket to server");
        }
}


void Server::run(){   
    while(true){
        int evCount = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if(evCount < 0){
            throw std::runtime_error("Failed epoll_wait");
        }

        for(int i = 0; i < evCount; ++i){
            
        }

    }
}

void addServer(const char* ip){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        std::cerr<<"Failed to create a socket for server "<<ip<<std::endl;
        close(sock);
        return;
    }    

    int flags = O_NONBLOCK;
    int fcntlRes = fcntl(sock, F_SETFL, flags);
    if(fcntlRes < 0){
        std::cer<<"Failed to set O_NONBLOCK "<<ip<<std::endl;
        close(sock);
        return;
    }

    struct sockaddr_in server{};
    
    server.sin_family = AF_INET;
    server.sin_port = htons(Network::PORT);
    inet_pton(AF_INET, ip, &(server.sin_addr.s_addr));
    
    int connected = connect(sock, (struct sockaddr*)& server, sizeof(server));
    if(connected < 0 && errno != EINPROGRESS){
      std::cerr<<"Failed to connect server "<<ip<<std::endl;
      close(sock);
      return;
    }

    struct epoll_event ev;    
    
    ev.events = EPOLLIN;
    ev.data.fd = sock;
    int res = epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &ev);
    if(res < 0){
        std::cerr<<"Failed to add sock to epoll "<<ip<<std::endl;
        close(sock);
        return;
    }   
         
    sereversInfo[ip] = Monitoring();
} 

Server::~Server(){
    


}






