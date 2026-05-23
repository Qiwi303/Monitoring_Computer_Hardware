#include "Client.h" 

Client::Client(){
        events.resize(10);
        epollfd = epoll_create1(0);
        if(epollfd < 0){
            throw std::runtime_error("Failed to create epollfd");
        }
}


void Client::run(){
    while(true){
        int error = 0;
        socklen_t len = sizeof(error);   
        
        int evCount = epoll_wait(epollfd, events.data(), 10, -1);
        if(evCount < 0){
            throw std::runtime_error("Failed epoll_wait");
        }

        for(int i = 0; i < evCount; ++i){
            int sock = events[i].data.fd;
            if (events[i].events & (EPOLLERR | EPOLLHUP)) {
                serverInfo.erase(sysMap[sock]);
                sysMap.erase(sock);
                close(sock);
            }

            if(events[i].events & EPOLLOUT){
                
                int res = getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len);
                if(res < 0){
                    std::cerr<<"Failed getsockopt"<<std::endl;
                    close(sock);
                    continue;
                }

                else if(error != 0){
                    error = 0;
                    std::cerr<<"Connection was failed"<<std::endl;
                    close(sock);
                    continue;
                }
                
                else{
                    //connected
                                        

                    struct epoll_event ev{};
                    ev.events = EPOLLIN;           
                    ev.data.fd = sock;
                    
                    res = epoll_ctl(epollfd, EPOLL_CTL_MOD, sock, &ev);
                    if(res < 0){
                        std::cerr<<"Failed to change epoll mod "<<sysMap[sock]<<std::endl;
                        sysMap.erase(sock);
                        close(sock);
                    }  
                }
                
            }
            else if(events[i].events & EPOLLIN){


                auto& buf = serverBuf[sock];
                buf.resize(buf.size() + monSize);
                int res = recv(sock, serverBuf[sock].data() + buf.size() -monSize, monSize, 0);
                buf.resize(buf.size() - monSize + res);           
    
                if(res > 0){

                    
                    while(buf.size() >= monSize){
                        Monitoring tmp;
                        memcpy(&tmp, buf.data(), monSize);
                        serverInfo[sysMap[sock]] = tmp;
                        buf.erase(buf.begin(), buf.begin() + monSize);
                    
                    }
                }
 
                else if(res == 0 || (res < 0 && errno != EAGAIN && errno != EWOULDBLOCK)){
                    std::cerr<<"Server "<<sysMap[sock]<<" disconnected"<<std::endl;
                    serverInfo.erase(sysMap[sock]);
                    sysMap.erase(sock);
                    close(sock);
                }
    
                std::cout<<(serverInfo[sysMap[sock]]).cpu.usageHistory[59]<<std::endl;
            }
        }
    }
}

void Client::addServer(std::string& ip){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        std::cerr<<"Failed to create a socket for server "<<ip<<std::endl;
        return;
    }    
    int flags = fcntl(sock, F_GETFL, 0);    
    if(flags < 0){
        std::cerr<<"Failed to get flags"<<ip<<std::endl;
        close(sock);
        return;
    }

    flags |= O_NONBLOCK;
    int fcntlRes = fcntl(sock, F_SETFL, flags);
    if(fcntlRes < 0){
        std::cerr<<"Failed to set O_NONBLOCK "<<ip<<std::endl;
        close(sock);
        return;
    }

    struct sockaddr_in server{};
    
    server.sin_family = AF_INET;
    server.sin_port = htons(Network::PORT);
    inet_pton(AF_INET, ip.c_str(), &(server.sin_addr));
    
    int connected = connect(sock, (struct sockaddr*)& server, sizeof(server));
    if(connected < 0 && errno != EINPROGRESS){
      std::cerr<<"Failed to connect server "<<ip<<std::endl;
      close(sock);
      return;
    }

    struct epoll_event ev;    
    
    ev.events = EPOLLOUT;
    ev.data.fd = sock;
    int res = epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &ev);
    if(res < 0){
        std::cerr<<"Failed to add sock to epoll "<<ip<<std::endl;
        close(sock);
        return;
    }   
         
    sysMap[sock] = ip;
} 

Client::~Client(){
    for(auto& [sock, ip] : sysMap){
        close(sock);
    } 
    close(epollfd);
}






