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

class Cpu{
public:
	Cpu();		
	~Cpu();
	std::vector<int> calcTime();
	float calcUsage();

private:
	int fd;
};
