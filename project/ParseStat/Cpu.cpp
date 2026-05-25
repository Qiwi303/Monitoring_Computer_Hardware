#include "Cpu.h"

Cpu::Cpu(){
	fdStat = open("/proc/stat", O_RDONLY);
	if(fdStat < 0){
		throw std::runtime_error("Failed to open /proc/stat");
	}
    
    fdCpuInfo = open("/proc/cpuinfo", O_RDONLY);
	if(fdCpuInfo < 0){
		throw std::runtime_error("Failed to open /proc/cpuinfo");
	}

}

Cpu::~Cpu(){
	if(fdStat < 0){
		std::cerr<<"Invalid fd /proc/stat"<<std::endl;
	}
	else{
		int closed = close(fdStat);
		if(closed < 0){
			std::cerr<<"Failed to close fd /proc/stat"<<std::endl;
		}
	}

    if(fdCpuInfo < 0){
		std::cerr<<"Invalid fd /proc/cpuinfo"<<std::endl;
	}
	else{
		int closed = close(fdCpuInfo);
		if(closed < 0){
			std::cerr<<"Failed to close fd /proc/cpuinfo"<<std::endl;
		}
	}


}

std::vector<int> Cpu::calcTime(){	
	int size = 128;
	char buff[128];
	
	int rd = pread(fdStat, buff, size, 0);
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


uint32_t* Cpu::getCache(){
    uint32_t eax, ebx, ecx, edx;
    
    uint32_t coreCount = std::thread::hardware_concurrency();

    bool initialized = __get_cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
    if(initialized){
        cache[0] = ((ecx >> 24) + (edx >> 24)) * coreCount;
    }

    initialized = __get_cpuid(0x80000006, &eax, &ebx, &ecx, &edx);
    if(initialized){
          cache[1] = ((ecx >> 16) * coreCount)/1024;
          cache[2] = ((edx >> 18) * 512)/1024;
    }
    
    return cache;
}

/*uint32_t* Cpu::getCache(){
    uint32_t eax, ebx, ecx, edx;
    uint32_t coreCount = std::thread::hardware_concurrency();

    for(uint32_t i = 0; ; i++){
        __cpuid_count(0x4, i, eax, ebx, ecx, edx);
        
        uint32_t type  = eax & 0x1F;
        if(type == 0) break;

        uint32_t level = (eax >> 5) & 0x7;
        uint32_t ways  = ((ebx >> 22) & 0x3FF) + 1;
        uint32_t parts = ((ebx >> 12) & 0x3FF) + 1;
        uint32_t line  = (ebx & 0xFFF) + 1;
        uint32_t sets  = ecx + 1;
        uint32_t size  = ways * parts * line * sets;

        if(level == 1 && type == 1)
            cache[0] = (size * coreCount) / 1024;
        else if(level == 2)
            cache[1] = (size * coreCount) / (1024 * 1024);
        else if(level == 3)
            cache[2] = size / (1024 * 1024);
    }

    return cache;
}*/

int Cpu::getFreq(){
	int size = 256;
	char buff[256];
	
	int rd = pread(fdCpuInfo, buff, size, 0);
	if(rd == -1){
		std::cerr<<"Failed to read"<<std::endl;
		exit(1);
	}
    
    int index = parser::findNthChr(buff, '.', size, 1);
    index--;
    if(buff[index - 1] < '0' || buff[index - 1] > '9'){
        float value;
        auto [ptr, ec] = std::from_chars(buff + index, buff + index + 4, value);
        if (ec != std::errc()) {
            throw std::runtime_error("Failed to convert");
        } 
    
        return value;
    }

 
    int freq = parser::castToInt(buff, index, ' ');
    return freq;
}       
