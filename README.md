# Homework #4
Do not cheat and good luck!

It will be great (and useful for you) if you will document your work in this README and write a sort of documentation for your homework. We may give few extra credits for good documentation.

/******************** DOCUMENTATION **********************/
--------
PART 1 : 
--------

1. To compile write "make part1"
2. To run write "./part1"
3. To see the list of commands type 'help'

--------
PART 2 : 
--------
	NOTE: For Part 2 and 3 compile using format -> "gcc -o Objectfile_Name Objectfile_Name.c cse320_functions.c -lpthread"

1. Insert this statement as the first line of your code -> #include "cse320_functions.h" 
2. Call "initiate_structs()" in the very beginning of your main. This is to give the default 0 value to the ref_counts for both the structs.
3. User can now use the thread safe cse320_functions() as :

	- void *cse320_malloc(size_t size);       		 				//This function returns a pointer to the allocated memory and keeps ref_counts
	- void cse320_free(void *ptr);									//ptr − This is the pointer to a memory block previously allocated with cse320_malloc to be deallocated. 																
	- FILE *cse320_fopen(char *filename, char *mode);				//This function returns a FILE pointer. Unlike the normal fopen(), cse320_fopen returns same FILE* when trying to open same filename.
	- int cse320_fclose(char *filename);							//This function decrements the reference counts to a particular filename and if it is 0 this closes its FILE*
	- void cse320_clean();											//This function cleans up any resources allocated by cse320_malloc or cse320_fopen that wasn't freed or closed 
	
	NOTE: cse320_clean() has to be called as the last line of user's main()

4. Information about structs so that user can print information stored in them :
	- struct addr_in_use
	  {
		  void* addr;
		  int ref_count; 													
	  };       
	- struct files_in_use
	  {
		  char* filename;
		  int ref_count; 												
		  FILE *fileptr;
	  };      
	- addr_in_use can be accessed through the word "ainu[index]"
	- files_in_use can be accessed through the word "finu[index]"
	
--------
PART 3 : 
--------	

