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

#include "TuiParts/TuiComp.h"
#include "TuiParts/TuiMain.h"
#include "TuiParts/TuiCpu.h"
#include "TuiParts/TuiRam.h"


#include <thread>
#include <chrono>
#include "Client.h"

enum class TuiBlock{
//    main,
    cpu,
    ram
};


class ClientTui{
public:
    ClientTui();
    ~ClientTui();
    
    void refreshScreen();
    void runTui();
    void addServer(std::string& ip);    

private:
    std::thread clientThread;
    Client cl;
    
    ftxui::ScreenInteractive screen;    


    std::atomic<bool> running{true};
    
    TuiBlock block = TuiBlock::cpu;

    ftxui::Component clientButtons;
    ftxui::Component serverButtons;
    ftxui::Element serverBox = vbox({});    

    std::string inputIP;
    ftxui::Component inputField;
    
    std::vector<std::shared_ptr<TuiComp>> components;
    Monitoring* link = nullptr;
};


