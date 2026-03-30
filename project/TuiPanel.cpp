#include "TuiPanel.h"

TuiPanel::TuiPanel(): screen(ScreenInteractive::FitComponent()),
    point(std::make_shared<ShmWrapper>()){
            
    components.push_back(std::make_shared<TuiMain>());
    components.push_back(std::make_shared<TuiCpu>(&(point->getPtr()->cpu)));    
    components.push_back(std::make_shared<TuiRam>(&(point->getPtr()->ram)));
    
    auto exitTui = screen.ExitLoopClosure(); 
    
    buttons = Container::Horizontal({
            Button("main", [this] {block = TuiBlock::main;}),
            Button("cpu", [this] {block = TuiBlock::cpu;}),
            Button("ram", [this] {block = TuiBlock::ram;}),
            Button("quit", [exitTui] {exitTui();})
    });
    
        
}

void TuiPanel::refreshScreen(){
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        screen.PostEvent(Event::Custom);
    }
}

void TuiPanel::runTui(){
    auto mainComponent = Renderer(buttons, [this]{
        int index = static_cast<int>(block);
        ftxui::Element box = components[index]->getBox();
    
        return vbox({
                buttons->Render(),
                box  
        });
    });
        
    std::thread refresh(&TuiPanel::refreshScreen, this);
    
    screen.Loop(mainComponent);
    
    running = false;
    refresh.join();
}

//TuiPanel::~TuiPanel(){}; 
