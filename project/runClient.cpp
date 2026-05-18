#include "Client.h"

int main(){
    try{
        Client cl;
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
