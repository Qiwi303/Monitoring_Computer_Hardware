#pragma once

#include "TuiComp.h"
#include <algorithm>
using namespace ftxui;

class TuiRam: public TuiComp{
public:
    TuiRam(){}
    
    void changeLink(void* link) override{
        if(link == nullptr){
            std::cerr<<"invalid link"<<std::endl;
        }
        else data = (RamTrack*)link;
    }
 
   
    ftxui::Element getGraph(){
        int height = 18;
        int width = 50;
        auto c = ftxui::Canvas(width, height);
        int size = std::min(width - 1, 59);
        for(int i = 0; i < size - 1; ++i){
            float val1 = data->usageHistory[i];
            float val2 = data->usageHistory[i + 1];
                
            int y1 = height -  static_cast<int>(val1*(height - 1));
            int y2 = height -  static_cast<int>(val2*(height - 1));

            c.DrawPointLine(i, y1,
                            i + 1, y2,
                             ftxui::Color::Red); 
        }

        return ftxui::canvas(std::move(c));
    }

    ftxui::Element getText(){
        std::string total = std::to_string(data->total);
        total.insert(1, ".");
        total.resize(4);
            
        std::string avaible = std::to_string(data->avaible);
        avaible.insert(1, ".");
        avaible.resize(4);

        return vbox({
               text("total: " + total +  " Gb") | border, 
               text("avaible: " +avaible + " Gb") | border, 
        });
    }    

    ftxui::Element getBox() override {
        return vbox({
            getGraph(),
            getText()
        });

    }

private:
    RamTrack* data;
};
