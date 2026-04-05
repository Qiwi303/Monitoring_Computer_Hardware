#include "DataCollector.h"

DataCollector* DataCollector::curr = nullptr;

void DataCollector::signal_handler(int signal){
    if(signal == SIGTERM || signal == SIGINT){
        curr->run = false;
    }
}

void DataCollector::cpuWorker(){
    Cpu cpu;
    uint32_t* cacheFromCpu = cpu.getCache();
    for (int i = 0; i < 4; ++i) {
        point->getPtr()->cpu.cache[i] = cacheFromCpu[i];
    }
    
    while(run){
        auto data = point->getPtr();
        std::memmove(&data->cpu.usageHistory[0], &data->cpu.usageHistory[1], 59 * sizeof(float));
        data->cpu.usageHistory[59] = cpu.calcUsage();
        data->cpu.freq = cpu.getFreq();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void DataCollector::ramWorker(){
    Ram ram;
    std::vector<float> res;
    auto data = point->getPtr();    

    while(run){
        res = ram.getMemInfo();
        data->ram.total = res[0];
        data->ram.avaible = res[1]; 
        
        std::memmove(&data->ram.usageHistory[0], &data->ram.usageHistory[1], 59 * sizeof(float));
        data->ram.usageHistory[59] = (1 - res[1]/res[0]);     
    
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

}


void DataCollector::startThreads(){
    threads.emplace_back(&DataCollector::cpuWorker, this);
    threads.emplace_back(&DataCollector::ramWorker, this);
}

DataCollector::DataCollector():
    point(std::make_shared<ShmWrapper>(true)){
    curr = this;

    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
   
    DataCollector::startThreads();
}

DataCollector::~DataCollector(){   
    for(int i = 0; i < threads.size(); ++i){
        threads[i].join();
    }   
}
