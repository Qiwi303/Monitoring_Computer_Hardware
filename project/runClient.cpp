#include "Client.h"

int main(){
    try{
        std::string ip;
        std::cin>>ip;  
        
        Client cl;
        cl.addServer(ip);  
        cl.run();
    }
    catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    
    }
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }

    return 0;
}
