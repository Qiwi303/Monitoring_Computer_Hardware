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
    int fd;

    Monitoring* data;
    void* ptr = MAP_FAILED;

    std::atomic<bool> run = true;
    static DataCollector* curr;

};

