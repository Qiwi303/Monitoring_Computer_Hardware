#pragma once

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <thread>

#include "cpu.h"
#include "ram.h"

struct CpuTrack{
    int usage;
};

struct RamTrack{
    int total;      
    int avaible; 
};

struct Monitoring{
    CpuTrack cpu;
    RamTrack ram;
};


class DataCollector{
public:
    DataCollector();
    ~DataCollector();    

private:
    void startThreads();
 
    void cpuWorker();
    void ramWorker();

    std::vector<std::thread> threads;    

    int size = 20;
    int capacity;
    int fd;

    Monitoring* data;
    void* ptr = MAP_FAILED;
};
