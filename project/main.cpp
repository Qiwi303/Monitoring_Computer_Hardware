#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
#include "parser.h"

std::vector<int> calcTime(const int fd){
	int ls = lseek(fd, 0, SEEK_SET);	
	if(ls == -1){
		std::cerr<<"Failed to lseek to start"<<std::endl;
		exit(1);
	}
	
	int size = 128;
	char buff[size];
	
	int rd = read(fd, buff, size);
	if(rd == -1){
		std::cerr<<"Failed to read"<<std::endl;
		exit(1);
	}
	
	parser cpu;
	char* ptr = cpu.findNthChr(buff + 5, ' ', size, 5);
	
	std::vector<int> res(2, 0);
	
	for(int i = 0; i < 5; ++i){
		if(i == 0 || i == 1) res[1]+= cpu.castToInt(ptr, size, ' ');
		else res[0] += cpu.castToInt(ptr, size,  ' ');
	}
		
	
	return res;
}

float calcUsage(const int fd){
	std::vector<int> res1 = calcTime(fd);
	sleep(1);
	std::vector<int> res2 = calcTime(fd);
	
	int total = res2[0] + res2[1] - res1[0] - res1[1];
	int active = res2[0] - res1[0];
	float usage = 100*(active*1.0/total);

	return 	usage;
}



int main(){	
	int fd = open("/proc/stat", O_RDONLY);
	if(fd == -1){
		std::cerr<<"Failed to open /proc/stat"<<std::endl;
		exit(1);
	}
	
	std::cout << std::fixed << std::setprecision(2);
	std::cout << '\n';
	while(true){	
		std::cout<<"\r"<<calcUsage(fd)<<"%  "<<std::flush;
	}

	close(fd);

	return 0;
}
