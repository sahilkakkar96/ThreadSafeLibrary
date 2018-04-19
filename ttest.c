#include "cse320_functions.h"

void *myMalloc(void *vargp)
{	
    cse320_malloc(sizeof (char *));   
}
void *myFree(void *vargp)
{	
    cse320_free(ainu[2].addr);   
}
void *myFopen(void *vargp)
{	
    cse320_fopen("first","w"); 
    cse320_fopen("sec","w"); 
    cse320_fopen("first","w"); 
}
void *myFclose(void *vargp)
{	
    cse320_fclose("first");   
}
void *myClean(void *vargp)
{	
    cse320_clean();   
}
int main()
{
	initiate_structs();
	char *b;
    int i;
    pthread_t tid;
 
    for (i = 0; i < 10; i++)
    {
         pthread_create(&tid, NULL, myMalloc, NULL);
         pthread_join(tid,(void**)&b);
    }
    
    
 	for (i = 0; i < 10; i++)
    printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
    
    pthread_create(&tid, NULL, myFree, NULL);
        pthread_join(tid,(void**)&b);
 	for (i = 0; i < 10; i++)
    printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
    
    
    pthread_create(&tid, NULL, myFopen, NULL);
        pthread_join(tid,(void**)&b);
 	for (i = 0; i < 10; i++)
    printf("Filename of struct [%d] = %s , Reference Count = %d\n", i, finu[i].filename,finu[i].ref_count);
    
    pthread_create(&tid, NULL, myFclose, NULL);
        pthread_join(tid,(void**)&b);
 	for (i = 0; i < 10; i++)
    printf("Filename of struct [%d] = %s , Reference Count = %d\n", i, finu[i].filename,finu[i].ref_count);
    
     pthread_create(&tid, NULL, myClean, NULL);
        pthread_join(tid,(void**)&b);
 	for (i = 0; i < 10; i++)
 	printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
 	for (i = 0; i < 10; i++)
    printf("Filename of struct [%d] = %p , Reference Count = %d\n", i, finu[i].filename,finu[i].ref_count);
    
    pthread_exit(NULL);
    
    return 0;
}