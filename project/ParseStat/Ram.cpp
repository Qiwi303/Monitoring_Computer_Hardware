#include "Ram.h"

Ram::Ram(){
    fd = open("/proc/meminfo", O_RDONLY);
    if(fd < 0){
        throw std::runtime_error("Failed to open /proc/meminfo");
    }
} 
  Ram::~Ram(){
      if(fd < 0){
          std::cerr<<"Invalid fd /proc/meminfo"<<std::endl;
      }
      else{
          int closed = close(fd);
          if(closed < 0){
              std::cerr<<"Failed to close fd /proc/meminfo"<<std::endl;
          }
      }
  
 }


std::vector<float> Ram::getMemInfo(){
	int size = 128;
	char buff[128];

	int rd = pread(fd, buff, size, 0);
	if(rd == -1){
		std::cerr<<"Failed to read"<<std::endl;
		exit(1);
	}

	std::vector<float> res(2, 0);
	int index = parser::findNthChr(buff, 'k', size, 3);	

	res[1] = (parser::castToInt(buff, --index, ' ')) / 1024.0f;
	
	index = parser::findNthChr(buff, 'k', size, 1);
	res[0] = parser::castToInt(buff, --index, ' ') / 1024.0f;	

	return res;

}



