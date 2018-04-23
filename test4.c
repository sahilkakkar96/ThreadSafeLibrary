#include "cse320_functions.h"

int main(int argc, char** argv){
initiate_structs();

cse320_settimer();
/*
pid_t pid[10];
int i;
	for (i = 0; i < 10; i++) {
  if ((pid[i] = cse320_fork()) < 0) {
    perror("fork");
    abort();
  } else if (pid[i] == 0) {
    printf("HOW many times\n");
    exit(0);
  }

}
*/
//char *args[]={"ps","-h",NULL};
cse320_fork();
cse320_fork();	
//execvp("ps",args);
printf("HOW many times from %d\n",getpid());
//sleep(2);
return 0;
}