#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include "cse320_functions.h"

int main(int argc, char** argv) {

//	initiate_structs();
	printf("USER PROGRAM GOING TO SLEEP\n");
	sleep(5);
	printf("USER PROGRAM RAN AFTER SLEEP\n");
	
/*	pid_t pid;
	pid=cse320_fork();
	if(pid==0)
	{
		char *args[]={"ls",NULL};
		execvp("ls",args);
		exit(0);
	}
*/
return 0;	
}