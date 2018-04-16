#include "cse320_functions.h"

void initiate_structs()
{
	int wnua;													//wnua - will not use again xD
	for(wnua=0;wnua<25;wnua++)
	{
		ainu[wnua] = aiu_default;
	}
	for(wnua=0;wnua<25;wnua++)
	{
		finu[wnua] = fiu_default;
	}
}

void *cse320_malloc(size_t size)
{
	if(aiu_var < 25)
	{
		if(ainu[aiu_var].addr==NULL)
		{
			void *mr = malloc(size);
			ainu[aiu_var].addr= mr;
			ainu[aiu_var].ref_count +=1;
			aiu_var++;
			return ainu[aiu_var-1].addr;
		}
		else return ainu[aiu_var].addr;	
	}
	else 
	{
		printf("Not enough memory\n");
		errno=ENOMEM;
		exit(-1);
	}
	
}

void cse320_free(void *ptr)
{
	int i;
	for(i=0;i<25;i++)
	{
		if(ainu[i].addr== ptr && ainu[i].ref_count>0)
		{
			ainu[i].ref_count -=1;
			ainu[i].addr=NULL;
			free(ainu[i].addr);
			return;
		}
	}
	printf("Free: Illegal address\n");
	errno = EFAULT;
	exit(-1);
}

FILE *cse320_fopen(char *filename, char *mode)
{
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
			return finu[fiu_var-1].fileptr;
		}
		else return finu[fiu_var].fileptr;	
	}
	else 
	{
		printf("Too many opened files\n");
		errno=ENFILE;
		exit(-1);
	}
}

int cse320_fclose(char *filename)
{
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
						return 0;
					}
					else
					{
						printf("Close: Ref count is zero\n");
						errno=EINVAL;
						exit(-1);
					}
				}
			}
			
		}
		printf("Close: Illegal filename\n");
		errno=ENOENT;
		exit(-1);
}

void cse320_clean()
{
	int i;
		for(i=0;i<25;i++)
		{
			if(finu[i].filename!=NULL)
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
		}
		
	for(i=0;i<25;i++)
	{
		if(ainu[i].addr!=NULL && ainu[i].ref_count>0)
		{
			ainu[i].ref_count=0;
			ainu[i].addr=NULL;
			free(ainu[i].addr);
		}
	}
}

/*** Just to check the implementation of cse320_functions ***/

int main(int argc, char** argv) {

	initiate_structs();
	int i;
	char **cmd;
	cmd= cse320_malloc(sizeof (char *));
	FILE *f1,*f2;
	f1= cse320_fopen("first","w");
	fprintf(f1,"%s","HELLO");
	f2= cse320_fopen("sec","w");
	fprintf(f2,"%s"," CHANGED");
	for(i=0;i<25;i++)
	{
		printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
	}
	for(i=0;i<25;i++)
	{
		printf("Filename of struct [%d] = %s , Reference Count = %d\n", i, finu[i].filename,finu[i].ref_count);
	}
	cse320_free(cmd);
	cse320_fclose("first");
	//cse320_fclose("sec");
	
	for(i=0;i<25;i++)
	{
		printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
	}
	for(i=0;i<25;i++)
	{
		printf("Filename of struct [%d] = %s , Reference Count = %d\n", i, finu[i].filename,finu[i].ref_count);
	}
	cse320_clean();
	for(i=0;i<25;i++)
	{
		printf("Address of struct [%d] = %p , Reference Count = %d\n", i, ainu[i].addr,ainu[i].ref_count);
	}
	for(i=0;i<25;i++)
	{
		printf("Filename of struct [%d] = %s , Reference Count = %d\n", i, finu[i].filename,finu[i].ref_count);
	}
return 0;	
}