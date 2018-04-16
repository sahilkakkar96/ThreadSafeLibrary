part1:	main
main:	main.c
	gcc	-Wall	-Werror	-g	-o	part1	main.c
part2:	cse320_functions
cse320_functions:	cse320_functions.c
	gcc	-Wall	-Werror	-g	-o	part2	cse320_functions.c	  	  									 	
clean:
	rm	-f	part1 part2