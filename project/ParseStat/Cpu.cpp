#include "Cpu.h"

Cpu::Cpu(){
	fd = open("/proc/stat", O_RDONLY);
	if(fd < 0){
		throw std::runtime_error("Failed to open /proc/stat");
	}
}

Cpu::~Cpu(){
	if(fd < 0){
		std::cerr<<"Invalid fd /proc/stat"<<std::endl;
	}
	else{
		int closed = close(fd);
		if(closed < 0){
			std::cerr<<"Failed to close fd /proc/stat"<<std::endl;
		}
	}

}

std::vector<int> Cpu::calcTime(){
	int ls = lseek(fd, 0, SEEK_SET);	
	if(ls == -1){
		std::cerr<<"Failed to lseek to start"<<std::endl;
		exit(1);
	}
	
	int size = 128;
	char buff[128];
	
	int rd = read(fd, buff, size);
	if(rd == -1){
		std::cerr<<"Failed to read"<<std::endl;
		exit(1);
	}
	
	int index = parser::findNthChr(buff + 5, ' ', size - 5, 5);
	std::vector<int> res(2, 0);
	

	for(int i = 0; i < 5; ++i){
		if(i == 0 || i == 1) res[1]+= parser::castToInt(buff, index, ' ');
		else res[0] += parser::castToInt(buff, index,  ' ');
	}
		
	
	return res;
}

float Cpu::calcUsage(){
	std::vector<int> res1 = calcTime();
	sleep(1);
	std::vector<int> res2 = calcTime();
	
	int total = res2[0] + res2[1] - res1[0] - res1[1];
	int active = res2[0] - res1[0];
	float usage = 100*(active*1.0/total);
	return 	usage;
}



