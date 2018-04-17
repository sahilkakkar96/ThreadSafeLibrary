#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv) {

	printf("User can type ’help’ to see the list of commands\n");
    
	int status,i;
    char app[255],parseRun[255][255];
    char** cmd;
    //char *filename, *appname;
   
    while(1)
{
	status=0;
    printf("Which application to run - ");
    fgets(app , sizeof(app), stdin);

	if(strcmp(app,"\n")==0)
	{
		printf("Enter Correct Command to Run\n");
	}
    else if(strcmp(app,"help\n")==0)
    {
    	printf("\thelp - Prints the list of commands.\n\texit - for exitting the main application\n\trun X [flags]- where X can be any executable with or without path and flags are optional\n");
    }
    else if(strcmp(app,"exit\n")==0)
    { 
    	exit(EXIT_SUCCESS);
    }
    else 
    {
    	int q=0;
    	char *token;
		token = strtok(app," ");
		while(token!=NULL){
							strcpy(*(parseRun+q),token);
							q++;
							token = strtok(NULL," ");
						  }
		size_t rem= strlen(*(parseRun+q-1));
		if(parseRun[q-1][--rem]=='\n')
	    parseRun[q-1][rem]='\0';
		
		if(strcmp(*(parseRun),"run")==0)                              //run ls [flags]
	    {
	    	if(q==1)
	    	{
	    		printf("Enter Correct Command to Run\n");
	    	}
	    	else if(q>2)
	    	{
	    		cmd= calloc(q,sizeof(char*));
	    		*(cmd)=*(parseRun+1);
	    		int a=1;
	    		for(i=2;i<q;i++)
	    		{
	    			*(cmd+a)=*(parseRun+i);
	    			a++;
	    		}
	    		*(cmd+a)=NULL;
		    	pid_t pid,wpid;
		    	pid = fork();
		    	
		    	if(pid == 0)
		    	{
		    		if (execvp(*(parseRun+1), cmd)!=0)
			        {
			        	char changename[257];
						strcpy(changename,"./");
						strcpy(&changename[2],*(parseRun+1));
						*(cmd)=changename;
						
				    	if (execvp(changename, cmd)!=0)
						{
						  	perror("Wrong Executable Provided");
						   	exit(EXIT_FAILURE);
						}
			        }
		    		exit(0);
		    	}
		    	else if(pid == -1)
		    	{
		    		printf("FORK ERROR\n");
		    	}
		    	else while ((wpid = wait(&status)) > 0);
		    	
		    	free(cmd);
	    	}
	    	else
	    	{	
	    		char *cmd[] = { *(parseRun+1), NULL };
		    	pid_t pid,wpid;
		    	pid = fork();
		    	
		    	if(pid == 0)
		    	{
		    		if (execvp(*(parseRun+1), cmd)!=0)
			        {
				    	char changename[257];
						strcpy(changename,"./");
						strcpy(&changename[2],*(parseRun+1));
						*(cmd)=changename;
						
				    	if (execvp(changename, cmd)!=0)
						{
						  	perror("Wrong Executable Provided");
						   	exit(EXIT_FAILURE);
						}
					}
		    		exit(0);
		    	}
		    	else if(pid == -1)
		    	{
		    		printf("FORK ERROR\n");
		    	}
		    	else while ((wpid = wait(&status)) > 0);	
		    		
	    	}
	    }  
	    else printf("Enter Correct Command to Run\n");
    }
}
    
	return -1;
}
/*
FILE *f1;
	    f1 = fopen(filename, "r");
	    if(f1 == NULL) {
	      printf("FAILED TO PARSE FILE\n");
	      return(EXIT_FAILURE);
	    }
	    char num[100];
	    if(fgets (num, 100, f1)==NULL ) {
	      exit(EXIT_FAILURE);
						   				}
	    fclose(f1);
*/	    