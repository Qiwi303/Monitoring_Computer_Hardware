#pragma once

#include "Structures.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <memory>
#include <unistd.h>

class ShmWrapper{
public:
    ShmWrapper(const bool _creator): creator(_creator){
        int flags = creator ? O_CREAT | O_RDWR : O_RDONLY;

        fd = shm_open("/shared_data", flags, 0666);
        if(fd < 0){
            throw std::runtime_error("Failed to shm_open shared_data");
        }

        if(creator){
            int trunc = ftruncate(fd, size);
            if(trunc < 0){
                throw std::runtime_error("Failed to truncate shared_data");
            }
        }
        int prot = creator ? (PROT_READ | PROT_WRITE) : PROT_READ;
        ptr = mmap(nullptr, size , prot, MAP_SHARED, fd, 0);
        if(ptr == MAP_FAILED){
            if(fd != -1) close(fd);
            throw std::runtime_error("Failed to mmap shared_data");
        }

        data = static_cast<Monitoring*>(ptr);
    }

    Monitoring* getPtr(){ return data; }
    
    ~ShmWrapper(){ 
        if(ptr != MAP_FAILED) munmap(ptr, size); 
        if(fd != -1) close(fd);
        if(creator) shm_unlink("/shared_data");
    }

private:
    bool creator;
    int size = sizeof(Monitoring);
    int fd = -1;
    void* ptr = MAP_FAILED;
    Monitoring* data = nullptr;
};

