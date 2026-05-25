#include "ClientTui.h"

ClientTui::ClientTui(): clientThread(&Client::run, &cl), 
                        screen(ScreenInteractive::Fullscreen()){
    
    //components.push_back(std::make_shared<TuiMain>());
    components.push_back(std::make_shared<TuiCpu>());    
    components.push_back(std::make_shared<TuiRam>());
    
    auto exitTui = screen.ExitLoopClosure();  
    
    serverButtons = Container::Horizontal({
            //Button("main", [this] {block = TuiBlock::main;}),
            Button("cpu", [this] {block = TuiBlock::cpu;}),
            Button("ram", [this] {block = TuiBlock::ram;}),
            Button("quit", [this, exitTui] {
                cl.stopRunning();
                exitTui();
            })
    });


    clientButtons = Container::Vertical({});
        
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

/*void ClientTui::addServer(std::string& ip){
    std::string currIP = ip;
    cl.addServer(currIP);
  
   auto newButton = Button(currIP, [this, currIP]{
        std::thread([this, currIP]{
            if(cl.isServerAccessible(currIP)){
                link = cl.getLink(currIP);
                components[0]->changeLink((void*)&(link->cpu));
                components[1]->changeLink((void*)&(link->ram));
            }
            screen.PostEvent(Event::Custom);
        }).detach();
    });     
  
    clientButtons->Add(newButton); 
}*/

void ClientTui::addServer(std::string& ip){
    std::string currIP = ip;
    cl.addServer(currIP);

    auto ipButton = Button(currIP, [this, currIP]{
        std::thread([this, currIP]{
            if(cl.isServerAccessible(currIP)){
                link = cl.getLink(currIP);
                components[0]->changeLink((void*)&(link->cpu));
                components[1]->changeLink((void*)&(link->ram));
            }
            screen.PostEvent(Event::Custom);
        }).detach();
    });

    auto delButton = Button("x", [this, currIP]{
        cl.removeServer(currIP);
        link = nullptr;
        screen.PostEvent(Event::Custom);
    });

    auto row = Container::Horizontal({ipButton, delButton});
    clientButtons->Add(row);
}


void ClientTui::runTui(){ 
    auto clientPart = ftxui::Container::Vertical({inputField, clientButtons});    
    auto tui = ftxui::Container::Horizontal({clientPart, serverButtons});    

    auto mainComponent = Renderer(tui, [this, clientPart]{
        int index = static_cast<int>(block);
        if(link != nullptr) serverBox = components[index]->getBox();  

        return hbox({
                    vbox({
                        clientPart->Render()
                    }) | border,
                    
                    vbox({
                        serverButtons->Render() | border, 
                        serverBox | border
                    }) | border,
        });
    });
        
    std::thread refresh(&ClientTui::refreshScreen, this);
    
    screen.Loop(mainComponent);
    
    running = false;
    refresh.join();
}

 
