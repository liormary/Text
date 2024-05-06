myText: myText.o
	gcc -g -ansi -Wall -pedantic myText.o -o myText
myText.o: myText.c
	gcc -c -g -ansi -Wall -pedantic myText.c -o myText.o
