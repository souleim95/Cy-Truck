#ifndef TRAJET_H
#define TRAJET_H

#include "other.h"

typedef struct trajet {
  int trajet_id;
  struct trajet* fd;
  struct trajet* fg;
  int eq;
} Trajet;

Trajet* CreerTrajet(int a);

Trajet *rotationGaucheE(Trajet *a);

Trajet *rotationDroiteE(Trajet *a);

Trajet *DoubleRGT(Trajet *a);

Trajet *DoubleRDT(Trajet *a);

Trajet *equilibreTrajet(Trajet *a);

Trajet *AvlTrajet(Trajet *a, int id, int *h);

int recherche(Trajet* a, int id);

Trajet *equilibreAVL2(Trajet *a);

#endif
