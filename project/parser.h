#pragma once

#include <cstring>

class parser{
public:
	char* findNthChr(char* buff, char key, int size, int count);
	int castToInt(char* ptr, int& size, char stop);
};
