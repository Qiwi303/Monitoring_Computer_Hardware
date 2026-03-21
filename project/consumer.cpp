#include "dataCollector.h"


int main(){
    int fd = shm_open("/shared_data", O_RDONLY, 0444 );
    Monitoring* data = static_cast<Monitoring*>(mmap(nullptr, 20, PROT_READ, MAP_SHARED, fd, 0));
    while(true){
        std::cout<<data->ram.avaible<<std::endl;
    } 
    return 0;
}
