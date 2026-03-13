#include "parser.h"

namespace parser{
int findNthChr(char* buff, char key, int size, int count){
	char* ptr = buff;

	for(int i = 0; i < count; ++i){
		ptr = (char*)memchr(ptr, key, size - (ptr - buff));
		if(ptr == nullptr) return -1;
		ptr++;
	}
	
	return ptr - 2 - buff;

}

int castToInt(char* ptr, int& size, char stop){
	long long pw = 1;
	long long res = 0;
	int i = 0;
	for(; ptr[size - i] != stop; ++i){
		res+= pw*(ptr[size - i] - '0');
		pw*=10;
	}
	i++;
	size-=i;
	ptr-= size; 	

	return res;
}
}
