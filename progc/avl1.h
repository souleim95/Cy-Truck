#ifndef AVL1_H
#define AVL1_H
#include "trajet.h"
#include "fonction_utilitaire.h"



typedef struct avl {
  char nom[50];
  int depart;
  int traverse;
  struct avl *fd;
  struct avl *fg;
  int equilibre;
  Trajet *trajet;
} Avl;



Avl *rotationG(Avl *a);

Avl *rotationD(Avl *a);

Avl *DoubleRG(Avl *a);


Avl *DoubleRD(Avl *a);

Avl *equilibreAVL(Avl *a);
Avl *creerAvl(char *nom, int trajet_id);
Avl *creerAvlD(char *nom, int trajet_id);
Avl *insertionAVL_D(Avl *a, char *ville1, int trajet_id, int e, int *h);
Avl *insertionAVL(Avl *a, char *ville1, int trajet_id, int *h) ;

#endif 
