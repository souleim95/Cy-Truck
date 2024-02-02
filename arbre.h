#ifndef ARBRE_H
#define ARBRE_H
#include "other.h"
#include "trajet.h"



typedef struct avl {
  char nom[50];
  int depart;
  int traverse;
  struct avl *fd;
  struct avl *fg;
  int equilibre;
  Trajet *trajet;
} Avl;

Avl *creerAvl(char *nom, int trajet_id);

Avl *creerAvlD(char *nom, int trajet_id);

Avl *rotationG(Avl *a);

Avl *rotationD(Avl *a);

Avl *DoubleRG(Avl *a);

Avl *DoubleRD(Avl *a);

Avl *equilibreAVL(Avl *a);

Avl *insertionAVL_D(Avl *a, char *ville1, int trajet_id, int e, int *h);

Avl *insertionAVL(Avl *a, char *ville1, int trajet_id, int *h);

#endif
