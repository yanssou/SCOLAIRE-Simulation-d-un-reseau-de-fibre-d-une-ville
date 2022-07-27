CFLAGS = -g -ggdb -Wall -Wextra -pedantic -lm
CC = gcc

PROGRAMS = ChaineMain test RReseau main

.PHONY: all clean

.SUFFIX:

all: $(PROGRAMS)

main : main.o Chaine.o Reseau.o gestionStructures.o SVGwriter.o gestionReseau.o Hachage.o ArbreQuat.o

RReseau : ReconstitueReseau.o Chaine.o Reseau.o gestionStructures.o SVGwriter.o gestionReseau.o Hachage.o ArbreQuat.o
	$(CC) -o $@ $(CFLAGS) $^

ChaineMain : ChaineMain.o Chaine.o gestionStructures.o SVGwriter.o 
	$(CC) -o $@ $(CFLAGS) $^

test : jeux_de_tests.o Chaine.o gestionStructures.o SVGwriter.o Reseau.o gestionReseau.o Hachage.o ArbreQuat.o
	$(CC) -o $@ $(CFLAGS) $^

ChaineMain.o : ChaineMain.c
	gcc -c $(CFLAGS) $^

Chaine.o : Chaine.c SVGwriter.c
	gcc -c $(CFLAGS) $^ 

jeux_de_tests.o : jeux_de_tests.c
	gcc -c $(CFLAGS) $^

gestionStructures.o : gestionStructures.c
	gcc -c $(CFLAGS) $^

SVGwriter.o : SVGwriter.c
	gcc -c $(CFLAGS) $^

Reseau.o : Reseau.c 
	gcc -c $(CFLAGS) $^

ReconstitueReseau.o : ReconstitueReseau.c 
	gcc -c $(CFLAGS) $^

gestionReseau.o : gestionReseau.c 
	gcc -c $(CFLAGS) $^

Hachage.o : Hachage.c
	gcc -c $(CFLAGS) $^

ArbreQuat.o : ArbreQuat.c Chaine.c 
	gcc -c $(CFLAGS) $^

main.o : main.c
	gcc -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(PROGRAMS)