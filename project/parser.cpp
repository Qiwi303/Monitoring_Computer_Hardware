#include "parser.h"

char* parser::findNthChr(char* buff, char key, int size, int count){
	char* ptr = buff;

	for(int i = 0; i < count; ++i){
		ptr = (char*)memchr(ptr, key, size - (ptr - buff));
		if(ptr == nullptr) return nullptr;
		ptr++;
	}
	
	return ptr - 1;

}

int parser::castToInt(char* ptr, int& size, char stop){
	long long pw = 1;
	long long res = 0;
	int i = size - 1;
	for(; ptr[i] != stop; --i){
		res+= pw*(ptr[i] - '0');
		pw*=10;
	}

	size-=i;
	ptr-= size; 	

	return res;
}
