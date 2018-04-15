part1:	main
main:	main.c
	gcc	-Wall	-Werror	-g	-o	part1	main.c	  	  									 	
clean:
	rm	-f	part1