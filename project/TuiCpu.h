#pragma once
#include "TuiComp.h"


class TuiCpu: public TuiComp{
public:
    TuiCpu(CpuTrack* _data): data(_data){}
    ftxui::Element getBox() override{
        return vbox({
            text(std::to_string(data->usage) + "%") | border 
        });
    }
private:
    CpuTrack* data
};
