all:item.o
	gcc main.c item.o -o main -Wall -std=c99 -pedantic-errors 

clean:
	rm -f *.o *.zip *.bin main

run:
	./main

checkmem:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

item.o:
	gcc -c item.c