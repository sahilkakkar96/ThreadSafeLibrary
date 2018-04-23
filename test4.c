#include "cse320_functions.h"

int main(int argc, char** argv){
initiate_structs();
int pi=getpid();
pid_t pid;
cse320_settimer();
if(pid=cse320_fork()==0)
{
	sleep(5);
}
cse320_fork();
if(getpid()==pi)	
while(1);
return 0;
}