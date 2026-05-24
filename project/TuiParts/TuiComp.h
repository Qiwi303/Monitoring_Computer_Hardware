#pragma once

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"  
#include "ftxui/component/component_base.hpp"      
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"  
#include "ftxui/dom/elements.hpp"  
#include "ftxui/screen/color.hpp"

#include <cstring>
#include "../Structures.h"

using namespace ftxui;


class TuiComp{
public:
    virtual ftxui::Element getBox() = 0;
    virtual void changeLink(void* link) = 0;
    virtual ~TuiComp() = default;
};
