#include "dataCollector.h"

DataCollector* DataCollector::curr = nullptr;

void DataCollector::signal_handler(int signal){
    if(signal == SIGTERM || signal == SIGINT){
        curr->run = false;
    }
}

void DataCollector::cpuWorker(){
    Cpu cpu;
    while(run){
        data->cpu.usage = cpu.calcUsage();
    }
}

void DataCollector::ramWorker(){
    Ram ram;
    std::vector<int> res;
    while(run){
        res = ram.getMemInfo();
        data->ram.total = res[0];
        data->ram.avaible = res[1];
    }

}


void DataCollector::startThreads(){
    threads.emplace_back(&DataCollector::cpuWorker, this);
    threads.emplace_back(&DataCollector::ramWorker, this);
}

DataCollector::DataCollector(){
    fd = shm_open("/shared_data", O_CREAT | O_RDWR, 0666);
    if(fd < 0){
        throw std::runtime_error("Failed to shm_open shared_data");
    }
    
    int trunc = ftruncate(fd, size);
    if(trunc < 0){
        throw std::runtime_error("Failed to truncate shared_data");
    }

    ptr = mmap(nullptr, size, PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED){
        throw std::runtime_error("Failed to mmap shared_data");
    }
    
    data = static_cast<Monitoring*>(ptr);
    
    curr = this;

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
   
    DataCollector::startThreads();
}

DataCollector::~DataCollector(){    
    for(int i = 0; i < threads.size(); ++i){
        threads[i].join();
    }    

    if(ptr != MAP_FAILED){
        munmap(ptr, size); 
    }    
    
    if(fd != -1){
        close(fd);
    }
    
    shm_unlink("/shared_data");

}




