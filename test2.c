#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	printf("USER PROGRAM GOING TO SLEEP\n");
	sleep(12);
	printf("USER PROGRAM RAN AFTER SLEEP\n");
	return 0;
}