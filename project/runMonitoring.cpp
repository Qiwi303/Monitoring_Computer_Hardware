#include "TuiPanel.h"
#include <stdexcept>

int main(){
    try{
        TuiPanel monitoring;
        monitoring.runTui();
    }
    
    catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    }    
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }

    return 0;
}
