#pragma once

#include <sys/stat.h>
#include <thread>
#include <iostream>

#include "ShmWrapper.h"

#include "ParseStat/Cpu.h"
#include "ParseStat/Ram.h"

#include <csignal>
#include <atomic>
#include <chrono>
class DataCollector{
public:
    DataCollector();
    ~DataCollector();    

private:
    void startThreads(); 
    void cpuWorker();
    void ramWorker();

    void static signal_handler(int signal);

    std::vector<std::thread> threads;    

    int size = sizeof(Monitoring);

    std::atomic<bool> run = true;
    static DataCollector* curr;
    
    std::shared_ptr<ShmWrapper> point;
};

