#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <semaphore.h>



void initiate_structs();
void *cse320_malloc(size_t size);       		 				//function returns a pointer to the allocated memory, or NULL if the request fails.
void cse320_free(void *ptr);									//ptr − This is the pointer to a memory block previously allocated with malloc, calloc or realloc to be deallocated. 
																//		If a null pointer is passed as argument, no action occurs.
FILE *cse320_fopen(char *filename, char *mode);					//This function returns a FILE pointer. Otherwise, error message displayed and the global variable errno is set to indicate the error.
int cse320_fclose(char *filename);
void cse320_clean();

struct addr_in_use
{
	void* addr;
	int ref_count; 												//(initial value should be zero)	
};
extern struct addr_in_use aiu_default;
typedef struct addr_in_use aiu;


struct files_in_use
{
	char* filename;
	int ref_count; 												//(initial value should be zero)
	FILE *fileptr;
};
extern struct files_in_use fiu_default;
typedef struct files_in_use fiu;

aiu ainu[25];
fiu finu[25];