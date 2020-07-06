./search.cli: main.c stats.c search.c
	gcc -o ./search.cli main.c stats.c search.c

clean: 
	rm *.o

