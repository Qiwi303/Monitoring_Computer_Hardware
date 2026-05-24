#include "TuiPanel.h"
#include <thread>
#include <chrono>
#include "Client.h"

class ClientTui{
public:
    ClientTui();
    ~ClientTui();
    
    void refreshScreen();
    void runTui();
    void addServer(std::string& ip);    

private:
    std::thread clientThread;
    Client cl;
    
    TuiPanel tp; 
    ftxui::ScreenInteractive screen;    


    std::atomic<bool> running{true};
    
    ftxui::Component buttons;

    std::string inputIP;
    ftxui::Component inputField;
};


