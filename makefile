
#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -O3

#  Sources
SOURCES =  wordmorph.c Tabela.c Grafos.c ficheiros.c LinkedList.c procura.c

#  Objects
OBJECTS = wordmorph.o Tabela.o Grafos.o ficheiros.o LinkedList.o procura.o

wordmorph:	wordmorph.c
wordmorph:	$(OBJECTS)
		gcc -g -o $@ $(OBJECTS)

LinkedList.o: LinkedList.h LinkedList.c

Tabela.o: ficheiros.h Tabela.h Tabela.c

Grafos.o: ficheiros.h defs.h LinkedList.h Grafos.c

ficheiros.o: ficheiros.h Tabela.h ficheiros.c

procura.o: procura.h LinkedList.h Grafos.h defs.h procura.c

clean::
	rm -f *.o core a.out wordmorph *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
