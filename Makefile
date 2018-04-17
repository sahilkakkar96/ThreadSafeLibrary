part1:	main
main:	main.c
	gcc	-Wall	-Werror	-g	-o	part1	main.c
part2:	test1
test1:	test1.c
	gcc	-Wall	-Werror	-g	-o	part2	test1.c	cse320_functions.c	  									 	
clean:
	rm	-f	part1 part2