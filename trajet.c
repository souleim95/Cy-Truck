#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trajet.h"

Trajet* CreerTrajet(int a){
  Trajet* Tnew=malloc(sizeof(Trajet));
  if(Tnew==NULL){
    exit (445);
  }
  Tnew->eq=0;
  Tnew->fd=NULL;
  Tnew->fg=NULL;
  Tnew->trajet_id=a;
  return Tnew;
}

Trajet *rotationGaucheE(Trajet *a) {
  int eq_pivot;
  int eq_a;
  Trajet *pivot;
  //Effectue la rotation
  pivot = a->fd;
  a->fd = pivot->fg;
  pivot->fg = a;
  //Met a jour l'équlibre
  eq_a = a->eq;
  eq_pivot = pivot->eq;
  a->eq = eq_a - max(eq_pivot, 0) - 1;
  pivot->eq = min2(eq_a - 2, eq_a + eq_pivot - 2, eq_pivot - 1);
  a = pivot;
  return a;
}

Trajet *rotationDroiteE(Trajet *a) {
  int eq_pivot;
  int eq_a;
  Trajet *pivot;
  pivot = a->fg;
  a->fg = pivot->fd;
  pivot->fd = a;
  eq_a = a->eq;
  eq_pivot = pivot->eq;
  a->eq = eq_a - min(eq_pivot, 0) + 1;
  pivot->eq = max2(eq_a + 2, eq_a + eq_pivot + 2, eq_pivot + 1);
  a = pivot;
  return a;
}

Trajet *DoubleRGT(Trajet *a) {
  a->fd = rotationDroiteE(a->fd);
  return rotationGaucheE(a);
}

Trajet *DoubleRDT(Trajet *a) {
  a->fg = rotationGaucheE(a->fg);
  return rotationDroiteE(a);
}

// Fonction pour maj l'équilibre d'un nœud dans l'arbre
Trajet *equilibreTrajet(Trajet *a) {
  if (a->eq >= 2) {
    if (a->fd->eq >= 0) {
      return rotationGaucheE(a);
    }
    else {
      return DoubleRGT(a);
    }
  }
  else if (a->eq <= -2) {
    if (a->fg->eq <= 0) {
      return rotationDroiteE(a);
    }
    else {
      return DoubleRDT(a);
    }
  }
  return a;
}

Trajet *AvlTrajet(Trajet *a, int id, int *h) {
  if (a == NULL) {
    *h = 1;
    return CreerTrajet(id);
  }
  else if (id < a->trajet_id) {
    a->fg = AvlTrajet(a->fg, id, h);
    *h = -*h;
  }
  else if (id > a->trajet_id) {
    a->fd = AvlTrajet(a->fd, id, h);
  }
  else {
    *h = 0;
    return a;
  }
  if (*h != 0) {
    a->eq = a->eq + *h;
    a = equilibreTrajet(a);
    if (a->eq == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}

// Fonction de recherche d'un entier dans un arbre AVL
int recherche(Trajet* a, int id) {
    if (a == NULL){
        return 0; // L'élément n'est pas trouvé
}
    if (id == a->trajet_id){
        return 1; // L'élément est trouvé
}
    if (id < a->trajet_id){
        return recherche(a->fg, id);
}
    return recherche(a->fd, id);
}

Trajet *equilibreAVL2(Trajet *a) {

  if (a->eq >= 2) {
    if (a->fd->eq >= 0) {
      return rotationGaucheE(a);
    } else {
      return DoubleRGT(a);
    }
  } else if (a->eq <= -2) {
    if (a->fg->eq <= 0) {
      return rotationDroiteE(a);
    } else {
      return DoubleRDT(a);
    }
  }
  return a;
}

