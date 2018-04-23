#include "cse320_functions.h"

int main(int argc, char** argv){
initiate_structs();
int status;
				char* test1 = cse320_malloc(50);
				strcpy(test1, "Hello, World! My name is Benjamin MIchalowicz!");
				printf("%s\n", test1);
				cse320_free(test1);
				cse320_settimer();
		pid_t p1;
		printf("Type 'help' for details on commands\n");
		char* prompt = "TestPtompt@btmichalowic.ubuntu> ";
		char command[255] = {'\0'};
		int i = 0;
		
prompt:
		
			for(i = 0; i<255; i++){
							command[i] = '\0';
			}
			printf("%s", prompt);
			scanf("%s", command);
			if(strcmp(command, "exit")==0)
							exit(0);
			else if(strcmp(command, "ls")==0){
							
							p1 = cse320_fork();
							
							if(p1==0){
											char* argv2[] = {"ls", "-a",  NULL};
											execvp("ls",argv2);
											perror("execvp error");
											exit(0);
							}
							goto prompt;
			}else if(strcmp(command, "clear")==0){
											char* argv2[] = {"clear", NULL};
											p1 = cse320_fork();
											if(p1==0){
											execvp("clear", argv2);
											perror("execvp error");
											}
											goto prompt;
			}else if(strcmp(command, "help")==0){
							printf("Help is for the directions\nls is to activate the 'ls' command\nexit is to exit the program\n\n");
							goto prompt;
			}else{
							printf("Unsupported command; try again\n\n");
							goto prompt;
			}
				exit(0); 
}
