#include "cse320_functions.h"
sem_t c;
void *myThreadFun(void *vargp)
{
	
	sem_wait (&c);
	static int i;
    cse320_malloc(sizeof (char *));
   
	printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
	i++;
	sem_post(&c);

}
int main()
{
	initiate_structs();
	
	sem_init(&c, 0, 1);
    int i;
    pthread_t tid;
 
    // Let us create three threads
    for (i = 0; i < 10; i++)
         pthread_create(&tid, NULL, myThreadFun, NULL);
 	
    pthread_exit(NULL);
    return 0;
}