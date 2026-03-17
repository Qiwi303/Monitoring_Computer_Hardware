#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cassert>
#include "cpu.h"
#include "ram.h"

//#daemon proccess creation
//	pid_t childPid = fork();
//	assert(childPid != -1);
//	if(childPid > 0) exit(0);

//	setsid();

//	childPid = fork();
//	assert(childPid != -1);
//	if(childPid > 0) exit(0);
//	
//	execl("./a.out", "./a.out", nullptr);

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;

int main(){
	try{	
        Cpu cpu;        
        Ram ram;
		while(true){
		
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
		}
	
	} catch(const std::runtime_error& e){
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    }
    
    catch(...){
        std::cerr<<"An unknown exception"<<std::endl;
    }


	return 0;
}

