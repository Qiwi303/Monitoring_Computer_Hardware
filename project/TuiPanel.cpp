#include "TuiPanel.h"

TuiPanel::TuiPanel(){    
       
    components.push_back(std::make_shared<TuiMain>());
    components.push_back(std::make_shared<TuiCpu>());    
    components.push_back(std::make_shared<TuiRam>());
    
    
    buttons = Container::Horizontal({
            Button("main", [this] {block = TuiBlock::main;}),
            Button("cpu", [this] {block = TuiBlock::cpu;}),
            Button("ram", [this] {block = TuiBlock::ram;}),
    });
    
        
}

ftxui::Component TuiPanel::getButtons(){ return buttons ;}

ftxui::Element TuiPanel::serverPanel(){
        int index = static_cast<int>(block);
        return components[index]->getBox();  
}

void TuiPanel::changeLink(Monitoring* ptr){
    link = ptr;
    components[1]->changeLink((void*)&(link->cpu));
    components[2]->changeLink((void*)&(link->ram));
}


//TuiPanel::~TuiPanel(){}; 
