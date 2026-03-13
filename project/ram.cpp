#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"

namespace ram{

std::vector<int> getMemInfo(const int fd){
	int size = 128;
	char buff[128];

	int rd = read(fd, buff, size);
	if(rd == -1){
		std::cerr<<"Failed to read"<<std::endl;
		exit(1);
	}
	
	int ls = lseek(fd, 0, SEEK_SET);
	if(ls == -1){
		std::cerr<<"Failed to lseek"<<std::endl;
	}	

	std::vector res(2, 0);
	int index = parser::findNthChr(buff, 'k', size, 3);	

	res[1] = parser::castToInt(buff, --index, ' ');
	
	index = parser::findNthChr(buff, 'k', size, 1);
	res[0] = parser::castToInt(buff, --index, ' ');	

	return res;

}



display	(){
	int fd = open("/proc/meminfo", O_RDONLY);
	if(fd == -1){
		std::cerr<<"Failed to open /proc/meminfo"<<std::endl;
		exit(1);
	}	
	
	std::vector<int> res;

	while(true){
		res = getMemInfo(fd);
		std::cout<<"\r"<<(res[0])<<" "<<(res[1])<<std::flush;	
		sleep(1);
	}

	close(fd);

	return 0;
}
}
