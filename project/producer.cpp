#include "DataCollector.h"

int main(){
    try{
        DataCollector dc;
    }    

    catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    }    
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }
    
    return 0;   
}
