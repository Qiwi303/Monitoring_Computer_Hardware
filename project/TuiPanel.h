#pragma once

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cassert>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"  
#include "ftxui/component/component_base.hpp"      
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"  
#include "ftxui/dom/elements.hpp"  
#include "ftxui/screen/color.hpp"

#include "Structures.h"

#include <thread>
#include <chrono>

#include <stdexcept>

#include "TuiComp.h"
#include "TuiMain.h"
#include "TuiCpu.h"
#include "TuiRam.h"


class ShmWrapper{
public:
    ShmWrapper(){
        fd = shm_open("/shared_data", O_RDONLY, 0444 );
        if(fd < 0){
            throw std::runtime_error("Failed to shm_open shared_data");
        }

        ptr = mmap(nullptr, 20, PROT_READ, MAP_SHARED, fd, 0);
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
    }

private:
    int size = sizeof(Monitoring);
    int fd;
    void* ptr;
    Monitoring* data = nullptr;
};



enum class TuiBlock{
    main,
    cpu,
    ram
};


class TuiPanel{
public:
    TuiPanel();
    ~TuiPanel() = default;

    void refreshScreen();
    void runTui();

private:
    std::shared_ptr<ShmWrapper> point; 
    ftxui::ScreenInteractive screen;
    
    TuiBlock block = TuiBlock::main; 
    ftxui::Component buttons;
    std::vector<std::shared_ptr<TuiComp>> components;
    std::atomic<bool> running{true};    
};
