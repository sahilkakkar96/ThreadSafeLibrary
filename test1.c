#include "cse320_functions.h"

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