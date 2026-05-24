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

#include "Client.h"


enum class TuiBlock{
    main,
    cpu,
    ram
};


class TuiPanel{
public:
    TuiPanel();
    ~TuiPanel() = default;
    ftxui::Element serverPanel();
    void changeLink(Monitoring* ptr);
    ftxui::Component getButtons();    

private: 
    
    TuiBlock block = TuiBlock::main; 
    ftxui::Component buttons;
    std::vector<std::shared_ptr<TuiComp>> components;
    Monitoring* link = nullptr;
};
