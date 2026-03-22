#pragma once

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <thread>

#include "cpu.h"
#include "ram.h"
#include "Structures.h"

#include <csignal>
#include <atomic>

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

    int size = 20;
    int fd;

    Monitoring* data;
    void* ptr = MAP_FAILED;

    std::atomic<bool> run = true;
    static DataCollector* curr;

};

