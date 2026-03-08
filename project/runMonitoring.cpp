#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cassert>

int main(){
	pid_t childPid = fork();
	assert(childPid != -1);
	if(childPid > 0) exit(0);

	setsid();

	childPid = fork();
	assert(childPid != -1);
	if(childPid > 0) exit(0);
	
	execl("./a.out", "./a.out", nullptr);
	
	return 0;
}

