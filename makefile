all: myshell

myshell: myshell.o
	gcc -Wall -g -m32 myshell.o -o myshell

myshell.o: myshell.c
	gcc -Wall -g -m32 -c myshell.c

.PHONY: clean

clean :
	rm *.o myshell
