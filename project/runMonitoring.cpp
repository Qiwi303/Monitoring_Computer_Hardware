#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cassert>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

//#daemon proccess creation
//	pid_t childPid = fork();
//	assert(childPid != -1);
//	if(childPid > 0) exit(0);

//	setsid();

//	childPid = fork();
//	assert(childPid != -1);
//	if(childPid > 0) exit(0);
  
//	execl("./a.out", "./a.out", nullptr);

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"  
#include "ftxui/component/component_base.hpp"      
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"  
#include "ftxui/dom/elements.hpp"  
#include "ftxui/screen/color.hpp"

#include "Structures.h"

#include <thread>
#include <chrono>

using namespace ftxui;

int main(){
    int fd = shm_open("/shared_data", O_RDONLY, 0444 );
    void* ptr = mmap(nullptr, 20, PROT_READ, MAP_SHARED, fd, 0);	
    Monitoring* data = static_cast<Monitoring*>(ptr);

    try{        
        int k = 0;
        std::string out;

        auto buttons = Container::Horizontal({
            Button("main", [&] {k = 0;}),
            Button("cpu", [&] {k = 1;}),
            Button("ram", [&] {k = 2;}),
        });
             
       
        auto component = Renderer(buttons, [&]{
            if(k == 0) out = "main";
            else if(k == 1){
                out = std::to_string(data->cpu.usage);
                out.resize(4);
                out = out + "%";
            }

            else out = std::to_string(data->ram.total);

            return vbox({
                   buttons->Render(),
                   text(out) | border,                   
     
                   });
            
        });    
         
        auto screen = ScreenInteractive::FitComponent();
 
        std::thread refresh_thread([&screen]() {
            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                screen.PostEvent(Event::Custom);
                }
        });    
    
        screen.Loop(component);
 
    
		/*while(true){
		
            std::vector<int> res = ram.getMemInfo();
            

		    Element document =
			    hbox({
			    text("CPU") | border,
		        text(cpu.calcUsage()) | border,
                text("Ram total") | border,
                text(std::to_string(res[0])) | border,
                text("Ram avaible")	| border,
                text(std::to_string(res[1])) | border,
	    });
		
		    auto screen = Screen::Create(
		    Dimension::Full(),
	            Dimension::Fit(document)
		    );
		
		    Render(screen, document);
		    screen.Print();
		    std::cout << screen.ResetPosition();	
		}*/
	
	} catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    }
    
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }

    if(ptr != MAP_FAILED){
        munmap(ptr, 20); 
    }    
    
    if(fd != -1){
        close(fd);
    }


	return 0;
}

