#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>


std::vector<int> getMemInfo(const int fd){
	int size = 128;
	char buff[size];

	int rd = read(fd, buff, size);
	if(rd == -1){
		std::cerr<<"Failed to read"<<std::endl;
		exit(1);
	}
	
	lseek(fd, 0, SEEK_SET);

	char* pos = (char*)memchr(buff, 'k', size);
	int pos1 = pos - buff - 2;
	
	pos = (char*)memchr(buff + pos1 + 3, 'k', size - pos1 - 3);
	int pos2 = pos - buff - 2;

	pos = (char*)memchr(buff + pos2 +3, 'k', size - pos2 - 3);
	int pos3 = pos - buff -2;

	std::vector<int> res(2);
	long long pw = 1;

	for(int i = pos3; buff[i] != ' '; --i){
		res[1] += pw * (buff[i] - '0');
		pw*=10;
	}

	pw = 1;
	for(int i = pos1; buff[i] != ' '; --i){
		res[0] += pw * (buff[i] - '0');
		pw*=10;
	}
	
	return res;

}



int main(){
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
