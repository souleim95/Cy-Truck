#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

Avl *creerAvl(char *nom, int trajet_id) {
  Avl *pnew = malloc(sizeof(Avl));
  if (pnew == NULL) {
    exit(1);
  }
  strcpy(pnew->nom, nom);
  pnew->depart = 0;
  pnew->traverse = 1;
  pnew->fd = NULL;
  pnew->fg = NULL;
  pnew->equilibre = 0;
  pnew->trajet=CreerTrajet(trajet_id);
  return pnew;
}

Avl *creerAvlD(char *nom, int trajet_id) {
  Avl *pnew = malloc(sizeof(Avl));
  if (pnew == NULL) {
    exit(1);
  }
  strcpy(pnew->nom, nom);
  pnew->depart = 1;
  pnew->traverse = 1;
  pnew->fd = NULL;
  pnew->fg = NULL;
  pnew->equilibre = 0;
  pnew->trajet=CreerTrajet(trajet_id);
  return pnew;
}

Avl *rotationG(Avl *a) {
  int eq_pivot;
  int eq_a;
  Avl *pivot;
  pivot = a->fd;
  a->fd = pivot->fg;
  pivot->fg = a;
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - max(eq_pivot, 0) - 1;
  pivot->equilibre = min2(eq_a - 2, eq_a + eq_pivot - 2, eq_pivot - 1);
  a = pivot;
  return a;
}

Avl *rotationD(Avl *a) {
  int eq_pivot;
  int eq_a;
  Avl *pivot;
  pivot = a->fg;
  a->fg = pivot->fd;
  pivot->fd = a;
  eq_a = a->equilibre;
  eq_pivot = pivot->equilibre;
  a->equilibre = eq_a - min(eq_pivot, 0) + 1;
  pivot->equilibre = max2(eq_a + 2, eq_a + eq_pivot + 2, eq_pivot + 1);
  a = pivot;
  return a;
}

Avl *DoubleRG(Avl *a) {
  a->fd = rotationD(a->fd);
  return rotationG(a);
}

Avl *DoubleRD(Avl *a) {
  a->fg = rotationG(a->fg);
  return rotationD(a);
}

Avl *equilibreAVL(Avl *a) {
  if (a->equilibre >= 2) {
    if (a->fd->equilibre >= 0) {
      return rotationG(a);
    } else {
      return DoubleRG(a);
    }
  } else if (a->equilibre <= -2) {
    if (a->fg->equilibre <= 0) {
      return rotationD(a);
    } else {
      return DoubleRD(a);
    }
  }
  return a;
}

Avl *insertionAVL_D(Avl *a, char *ville1, int trajet_id, int e, int *h) {
  if (a == NULL) {
    *h = 1;
    if(e == 1){
    return creerAvlD(ville1,trajet_id);
    }
    else{
    return creerAvl(ville1,trajet_id);
    }
  } else if (strcmp(ville1, a->nom) < 0) {
    a->fg = insertionAVL_D(a->fg, ville1, trajet_id, e, h);
    *h = -*h;
  } else if (strcmp(ville1, a->nom) > 0) {
    a->fd = insertionAVL_D(a->fd, ville1, trajet_id, e, h);
  } else {
    *h = 0;
if (e == 1) {
      a->depart += 1;
    }
 
        if(recherche(a->trajet,trajet_id) == 1) {
        return a;
        }
        int *h1=malloc(sizeof(int));
    // La ville n'a pas encore été traversée dans ce trajet, l'ajouter à la liste des trajets
    a->trajet=AvlTrajet(a->trajet, trajet_id , h1);
    a->traverse += 1;

    return a;
  }

  if (*h != 0) {
    a->equilibre = a->equilibre + *h;
    a = equilibreAVL(a);
    if (a->equilibre == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}

Avl *insertionAVL(Avl *a, char *ville1, int trajet_id, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvl(ville1,trajet_id);
  } else if (strcmp(ville1, a->nom) < 0) {
    a->fg = insertionAVL(a->fg, ville1, trajet_id, h);
    *h = -*h;
  } else if (strcmp(ville1, a->nom) > 0) {
    a->fd = insertionAVL(a->fd, ville1, trajet_id, h);
  } else {
    *h = 0;
    
        if(recherche(a->trajet,trajet_id) == 1) {
        return a;
        }
        int *h1=malloc(sizeof(int));
    // La ville n'a pas encore été traversée dans ce trajet, l'ajouter à la liste des trajets
    a->trajet=AvlTrajet(a->trajet, trajet_id , h1);
    a->traverse += 1;

    return a;
    

    
  }

  if (*h != 0) {
    a->equilibre = a->equilibre + *h;
    a = equilibreAVL(a);
    if (a->equilibre == 0) {
      *h = 0;
    } else {
      *h = 1;
    }
  }
  return a;
}

