#include "cse320_functions.h"

void initiate_structs()
{
	sem_init(&s, 0, 1);
	sem_init(&m, 0, 1);
	sem_init(&f, 0, 1);
	sem_init(&o, 0, 1);
	sem_init(&c, 0, 1);
	sem_init(&cc, 0, 1);
	sem_wait (&s);
	struct addr_in_use aiu_default= {NULL,0};
	struct files_in_use fiu_default= {.filename=NULL, .ref_count=0};
	int wnua;													//wnua - will not use again xD
	for(wnua=0;wnua<25;wnua++)
	{
		ainu[wnua] = aiu_default;
	}
	for(wnua=0;wnua<25;wnua++)
	{
		finu[wnua] = fiu_default;
	}
	sem_post(&s);
}

void *cse320_malloc(size_t size)
{
	sem_wait (&m);
	if(aiu_var < 25)
	{
		if(ainu[aiu_var].addr==NULL)
		{
			void *mr = malloc(size);
			ainu[aiu_var].addr= mr;
			ainu[aiu_var].ref_count +=1;
			aiu_var++;
			sem_post (&m);
			return ainu[aiu_var-1].addr;
		}
		else
		{
			sem_post (&m);
			return ainu[aiu_var].addr;
		} 
				
	}
	else 
	{
		char msg[]="Not enough memory\n";
		write(1,msg,18);
		errno=ENOMEM;
		sem_post(&m);
		exit(-1);
	}
	
}

void cse320_free(void *ptr)
{
	sem_wait (&f);
	int i;
	for(i=0;i<25;i++)
	{
		if(ainu[i].addr== ptr && ainu[i].ref_count>0)
		{
			ainu[i].ref_count -=1;
			free(ainu[i].addr);
			ainu[i].addr=NULL;
			sem_post(&f);
			return;
		}
	}
	char msg[]="Free: Illegal address\n";
	write(1,msg,22);
	errno = EFAULT;
	sem_post(&f);
	exit(-1);
}

FILE *cse320_fopen(char *filename, char *mode)
{
	sem_wait (&o);
	int i;
	if(fiu_var < 25)
	{
		for(i=0;i<25;i++)
		{
			if(finu[i].filename!=NULL)
			{
				if((strcmp(filename,finu[i].filename)==0))
				{
					finu[i].ref_count +=1;
					sem_post(&o);
					return finu[i].fileptr;
				}
			}
			
		}
		if(finu[fiu_var].filename==NULL)
		{
			finu[fiu_var].filename=filename;
			finu[fiu_var].ref_count +=1;
			finu[fiu_var].fileptr= fopen(filename,mode);
			fiu_var++;
			sem_post(&o);
			return finu[fiu_var-1].fileptr;
		}
		else 
		{
			sem_post(&o);
			return finu[fiu_var].fileptr;
		}	
	}
	else 
	{
		char msg[]="Too many opened files\n";
		write(1,msg,22);
		errno=ENFILE;
		sem_post(&o);
		exit(-1);
	}
}

int cse320_fclose(char *filename)
{
	sem_wait (&c);
	int i;
		for(i=0;i<25;i++)
		{
			if(finu[i].filename!=NULL)
			{
				if((strcmp(filename,finu[i].filename)==0))
				{
					if(finu[i].ref_count>0)
					{
						finu[i].ref_count -=1;
						if(finu[i].ref_count==0)
						{
							finu[i].filename=NULL;
							fclose(finu[i].fileptr);
						}
						sem_post(&c);
						return 0;
					}
					else
					{
						printf("Close: Ref count is zero\n");
						errno=EINVAL;
						sem_post(&c);
						exit(-1);
					}
				}
			}
			
		}
		char msg[]="Close: Illegal filename\n";
		write(1,msg,24);
		errno=ENOENT;
		sem_post(&c);
		exit(-1);
}

void cse320_clean()
{
	sem_wait (&cc);
	int i;
		for(i=0;i<25;i++)
		{
			if(finu[i].ref_count>0)
			{
				finu[i].ref_count =0;
				finu[i].filename=NULL;
				if(finu[i].ref_count==0)
				{
					fclose(finu[i].fileptr);
				}
			}
		}
		
		
	for(i=0;i<25;i++)
	{
		if(ainu[i].ref_count>0)
		{
			ainu[i].ref_count=0;
			free(ainu[i].addr);
			ainu[i].addr=NULL;
		}
	}
	sem_post(&cc);
}

pid_t cse320_fork()
{
	sem_wait (&s);
	pid_t pid;
	
/*	struct itimerval timer_val;
	timer_val.it_value.tv_sec = 1;
  	timer_val.it_value.tv_usec = 1;																	
  	timer_val.it_interval=timer_val.it_value;					
  																			struct itimerval {
																               struct timeval it_interval; 
																               struct timeval it_value;    
																           };
																
																           struct timeval {
																               time_t      tv_sec;         
																               suseconds_t tv_usec;        
																           };
																 
   	
   	if(cse320_settimer(ITIMER_REAL,&timer_val,NULL)== -1) 
    {
    	perror("error calling setitimer()");
    	sem_post(&s);
    	exit(1);
  	}*/
  	pid = fork();
  	sem_post(&s);
   	return pid;
} 
int cse320_settimer(int which, const struct itimerval *new_value, struct itimerval *old_value)
{
	int i;
	sem_wait (&s);
	i=setitimer(which, new_value,old_value);
	sem_post(&s);
	return i;
}