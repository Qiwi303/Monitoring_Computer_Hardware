#pragma once
#include "TuiComp.h"


class TuiCpu: public TuiComp{
public:
    TuiCpu(){}
    
    void changeLink(void* link) override{
        if(link == nullptr){
            std::cerr<<"invalid link"<<std::endl;
        }
        else data = (CpuTrack*)link;
    }

 /*   ftxui::Element getGraph(){
        return graph([&](int width, int height) {
            std::vector<int> out;
            for (int i = 0; i < width; i++) {
                float val = data->usageHistory[i % 60]; 
                out.push_back(val);        
            }
            return out;
        }) | color(Color::Green); 
    }*/
    
ftxui::Element getGraph(){
    if(data == nullptr) return ftxui::text("no data");
    int height = 20;
    int width = 50;
    auto c = ftxui::Canvas(width, height);
    int size = std::min(width - 1, 59);

    for(int i = 0; i < size - 1; ++i){
        float val1 = data->usageHistory[i] / 100.0f;
        float val2 = data->usageHistory[i + 1] / 100.0f;

        int y1 = height - 1 - std::max(1, static_cast<int>(val1 * (height - 2)));
        int y2 = height - 1 - std::max(1, static_cast<int>(val2 * (height - 2)));

        for(int y = y1; y < height; ++y)
            c.DrawPoint(i, y, ftxui::Color::GreenLight);
        c.DrawPointLine(i, y1, i + 1, y2, ftxui::Color::Green);
    }

    c.DrawPointLine(0, height - 1, size - 1, height - 1, ftxui::Color::Green);

    return ftxui::canvas(std::move(c));
}
    

    ftxui::Element getText(){
        std::string l1 = std::to_string(data->usageHistory[59]);
        l1.resize(4); 
        l1 = l1 + "%";

        std::string freq = std::to_string(data->freq);
        freq.insert(1, ".");
        freq = freq + " MHz";
        return 
            hbox({
                vbox({
                    text("usage: " + l1) | border,
                    text("freq: " + freq) | border
                }),
                vbox({
                    text("L1 " + std::to_string(data->cache[0]) + " kb"),
                    text("L2 " + std::to_string(data->cache[1]) + "   mb"),
                    text("L3 " + std::to_string(data->cache[2]) + "  mb"),
                }) | border
            });
    }


    ftxui::Element getBox(){
        return vbox({
            getGraph(),       
            getText(),
        });
    }

private:
    CpuTrack* data = nullptr;
};
