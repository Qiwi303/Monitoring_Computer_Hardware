#include "Server.h"

int main(){
    try{
        Server sv;
        sv.run();
    }
    catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    
    }
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }

    return 0;
}
