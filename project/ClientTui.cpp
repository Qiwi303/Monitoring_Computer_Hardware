#include "ClientTui.h"

ClientTui::ClientTui(): clientThread(&Client::run, &cl), 
                        screen(ScreenInteractive::Fullscreen()){
    buttons = Container::Vertical({});
        
    ftxui::InputOption option;
    option.on_enter = [this] {
        if (!inputIP.empty()) {
            addServer(inputIP); 
            inputIP.clear();
        }
    };

    inputField = ftxui::Input(&inputIP, "Enter server IP", option);
}

ClientTui::~ClientTui(){
    clientThread.join();
}

void ClientTui::refreshScreen(){
    while(running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        screen.PostEvent(Event::Custom);
    }
}

void ClientTui::addServer(std::string& ip){
    cl.addServer(ip);    
    auto newButton = Button(ip, [this, &ip]{
        if(cl.isServerAccessible(ip)){
            auto link = cl.getLink(ip);
            tp.changeLink(link);
        }
    });
    buttons->Add(newButton); 
}

void ClientTui::runTui(){
    auto servButtons = tp.getButtons();
    auto clientPart = ftxui::Container::Vertical({inputField, buttons});    
    auto tui = ftxui::Container::Horizontal({clientPart, servButtons});    

    auto mainComponent = Renderer(tui, [this, clientPart, servButtons]{
        ftxui::Element box = tp.serverPanel();
        
        return hbox({
                    vbox({
                        clientPart->Render()
                    }) | border,
                    
                    vbox({
                        servButtons->Render() | border, 
                        box | border
                    }) | border,
        });
    });
        
    std::thread refresh(&ClientTui::refreshScreen, this);
    
    screen.Loop(mainComponent);
    
    running = false;
    refresh.join();
}


