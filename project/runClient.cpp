#include "ClientTui.h"

int main(){
    try{ 
        ClientTui cl;  
        cl.runTui();
    }
    catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    
    }
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }

    return 0;
}
