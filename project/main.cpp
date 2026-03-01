#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
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

	char* newLine = (char*)std::memchr(buff, '\n', size);
	int len = newLine ? newLine - buff : size; 
	buff[len] = '\n';
	buff[len + 1] = '\0';
		
//	for(int i = 0; buff[i] != '\n'; ++ i){
//		std::cout<<buff[i];
//	}
//	std::cout<<std::endl;

	std::vector<int> res(2);
	long long pow = 1;
	int count = 1;
	int index = 1;

	

	int i = len - 1;
	for(; count < 6; --i){
		if(buff[i] == ' ' ) count++;
	}
	

	for(; count < 11; --i){
		if(buff[i] != ' '){
			res[index] += pow * (buff[i] - '0'); 	
			pow*=10;
		}

		else {
			pow = 1;
			count++;

			if(count == 8) index = 0;
		}


	}


//	std::cout<<res[0]<<" "<<res[1]<<std::endl;
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
	while(true){	
		std::cout<<calcUsage(fd)<<"%"<<std::endl;
	}

	//char* buff = {calcUsage(int fd)};
	//int wt = write(1, buff, 1);
	//if(wt == -1){
	//	std::cerr<<"Failed to write"<<std::endl;
	//	exit(1);
	//}



	close(fd);

	return 0;
}
