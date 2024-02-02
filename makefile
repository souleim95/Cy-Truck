all: exec

t_t.o: t_t.c 
	gcc -o t_t.o -c t_t.c

other.o: other.c 
	gcc -o other.o -c other.c
		

trajet.o: trajet.c other.h 
	gcc -o trajet.o -c trajet.c
	
arbre.o: arbre.c other.h trajet.h
	gcc -o arbre.o -c arbre.c


exec: t_t.o arbre.o trajet.o other.o
	gcc t_t.o arbre.o trajet.o other.o -o exec

clean:
	rm -f *.o
	rm -f exec


