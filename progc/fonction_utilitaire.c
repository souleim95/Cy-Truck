#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"fonction_utilitaire.h"



int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

int min(int a, int b) {
  if (a >= b) {
    return b;
  }
  return a;
}

int min2(int a, int b, int c) {
 return min(min(a, b), c); 
 }

int max2(int a, int b, int c) { 
return max(max(a, b), c); 
}

int comparerVilles(const void *a, const void *b) {
    const Avl *villeA = *(const Avl **)a;
    const Avl *villeB = *(const Avl **)b;
    return strcmp(villeA->nom, villeB->nom);
}
  

void parcoursPrefixe(Avl *racine, Avl** topVilles, int *nbVilles) {
    if (racine != NULL) {
        parcoursPrefixe(racine->fg, topVilles, nbVilles);

        if (*nbVilles < MAX_VILLES) {
            topVilles[(*nbVilles)++] = racine;
        } else {
            int minVisites = topVilles[0]->traverse;
            int minIndex = 0;

            for (int i = 1; i < MAX_VILLES; i++) {
                if (topVilles[i]->traverse < minVisites) {
                    minVisites = topVilles[i]->traverse;
                    minIndex = i;
                }
            }

            if (racine->traverse > minVisites) {
                topVilles[minIndex] = racine;
            }
        }

        parcoursPrefixe(racine->fd, topVilles, nbVilles);
    }
}

