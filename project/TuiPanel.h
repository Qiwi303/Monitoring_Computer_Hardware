#pragma once

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cassert>
#include <sys/stat.h>


#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"  
#include "ftxui/component/component_base.hpp"      
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"  
#include "ftxui/dom/elements.hpp"  
#include "ftxui/screen/color.hpp"


#include <thread>
#include <chrono>

#include "ShmWrapper.h"

#include "TuiParts/TuiComp.h"
#include "TuiParts/TuiMain.h"
#include "TuiParts/TuiCpu.h"
#include "TuiParts/TuiRam.h"




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
