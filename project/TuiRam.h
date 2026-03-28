#pragma once

#include "TuiComp.h"

class TuiRam: public TuiComp{
public:
    TuiRam(RamTrack* _data): data(_data){}
    ftxui::Element getBox() override{
        return vbox({
               text("total: " + data->total + " kb") | border, 
               text("avaible: " + data->avaible + " kb") | border, 
        });
    }
private:
    RamTrack* data;
};
