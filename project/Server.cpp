#include "Server.h" 

Server::Server(){
        beaconSock = socket(AF_INET, SOCK_DGRAM, 0);
        if(beaconSock < 0){
            throw std::runtime_error("Failed to create beaconSock");
        }    
    
        int opt = 1;
        int options = setsockopt(beaconSock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
        if(options < 0 ){
            throw std::runtime_error("Failed to open beaconSock");   
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(Network::PORT);
        server.sin_addr.s_addr = htonl(INADDR_BROADCAST);
        
        
   
    // int binded = bind(beaconSock, (sockaddr*)&server, sizeof(server));
    
        //if(binded == -1){
            //throw std::runtime_error("Failed to bind socket to server");
        //}
}


void Server::beacon(){
    while(true){
        int sended = sendto(beaconSock, Network::serverName, Network::serverName.size(),
                            (sockaddr*)&server, sizeof(server));
        if(sended == -1){
            throw std::runtime_error("Failed sendto");
        }    
    }
}

void Server::run(){   
    while(true){
        listen( ... );
        map[ ip ] = structure;   

    }

}

Server::~Server(){
    


}





 
