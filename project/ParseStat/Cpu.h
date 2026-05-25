#pragma once

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <iomanip>
#include "Parser.h"
#include <stdexcept>
#include <cerrno>
#include <cpuid.h>
#include <cstdint>
#include <thread>
#include <charconv>

class Cpu{
public:
	Cpu();		
	~Cpu();
	std::vector<int> calcTime();
	float calcUsage();
    uint32_t* getCache();
    int getFreq();
private:
	int fdStat = -1;
    int fdCpuInfo = -1;
    uint32_t cache[3] = {0, 0, 0};
};
