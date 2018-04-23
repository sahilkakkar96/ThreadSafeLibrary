
#include "cse320_functions.h"

int main(int argc, char** argv) {

	initiate_structs();
	printf("USER PROGRAM GOING TO SLEEP\n");
	sleep(2);
	printf("USER PROGRAM RAN AFTER SLEEP\n");
	cse320_settimer();
	pid_t pid;
	pid=cse320_fork();
	if(pid==0)
	{
		//char *args[]={"ls",NULL};
		//execvp("ls",args);
	sleep(15);
		printf("First fork");
		exit(0);
	}
	pid= cse320_fork();
	if(pid==0)
	{
		//char *args[]={"ls",NULL};
		//execvp("ls",args);

		printf("First fork");
		exit(0);
	}
	
	
return 0;	
}