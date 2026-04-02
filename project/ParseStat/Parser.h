#pragma once

#include <cstring>

namespace parser{
	int findNthChr(char* buff, char key, int size, int count);
	int castToInt(char* ptr, int& size, char stop);
}
