#pragma once

#include "TuiComp.h"

using namespace ftxui;

class TuiRam: public TuiComp{
public:
    TuiRam(RamTrack* _data): data(_data){}
    ftxui::Element getBox() override{
        return vbox({
               text("total: " + std::to_string(data->total) + " kb") | border, 
               text("avaible: " + std::to_string(data->avaible) + " kb") | border, 
        });
    }
private:
    RamTrack* data;
};
