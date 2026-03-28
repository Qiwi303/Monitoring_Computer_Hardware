#include "TuiPanel.h"

TuiPanel::TuiPanel(){
    components.push_back(std::make_shared<TuiCpu>(&(point->data->CpuTrack)));    
    components.push_back(std::make_shared<TuiRam>(&(point->data->RamTrack)));

    point = std::make_shread<ShmWrapper>();
    
    buttons = Container::Horizontal({
            Button("main", [&] {block = TuiBlock::main;}),
            Button("cpu", [&] {block = TuiBlock::cpu;}),
            Button("ram", [&] {k = TuiBlock::ram;}),
    });
    
        
}

ftxui::Element TuiPanel::setBox(){
    int index = static_cast<int>(block);
    ftxui::Element box = components[index]->getBox();
    
    return vbox({
        buttons->Render(),
        box  
    });
 
}

void TuiPanel::refreshScreen(bool& running){
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        screen.PostEvent(Event::Custom);
    }
}

void TuiPanel::runTui(){
    mainComponent = Renderer(buttons, SetBox);
    auto screen = ScreenInteractive::FitComponent();
        

    bool running = true;
    std::thread refresh(refreshScreen, running);
    
    screenLoop(component);
    
    running = false;
    refresh.join();

}

TuiPanel::~TuiPanel(){


}; 
