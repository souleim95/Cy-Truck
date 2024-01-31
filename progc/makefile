all: exec

traitement_t.o: traitement_t.c
	gcc -o traitement_t.o -c traitement_t.c

fonction_utilitaire.o: fonction_utilitaire.c avl1.h
	gcc -o fonction_utilitaire.o -c fonction_utilitaire.c

trajet.o: trajet.c fonction_utilitaire.h
	gcc -o trajet.o -c trajet.c
		
avl.o: avl1.c fonction_utilitaire trajet.h
	gcc -o avl1.o -c avl1.c



exec: traitement_t.o avl1.o trajet.o fonction_utilitaire.o
	gcc traitement_t.o avl1.o trajet.o fonction_utilitaire.o -o exec

clean:
	rm -f *.o
	rm -f exec

