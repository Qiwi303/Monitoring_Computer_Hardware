#include "DataCollector.h"

DataCollector* DataCollector::curr = nullptr;

void DataCollector::signal_handler(int signal){
    if(signal == SIGTERM || signal == SIGINT){
        curr->run = false;
    }
}

void DataCollector::cpuWorker(){
    Cpu cpu;
    while(run){
        point->getPtr()->cpu.usage = cpu.calcUsage();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void DataCollector::ramWorker(){
    Ram ram;
    std::vector<int> res;
    while(run){
        res = ram.getMemInfo();
        point->getPtr()->ram.total = res[0];
        point->getPtr()->ram.avaible = res[1];
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
