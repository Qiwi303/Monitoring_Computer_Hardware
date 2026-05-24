#pragma once
#include "TuiComp.h"


class TuiMain: public TuiComp{
public:
    ftxui::Element getBox() override{
        return vbox({
            text("main") | border 
        });
    }
    void changeLink(void* link) override{}
private:
};
