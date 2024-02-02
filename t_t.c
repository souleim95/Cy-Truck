#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trajet.h"
#include "arbre.h"
#include "other.h"
#define TAILLE_VILLE 35
#define MAX_VILLES 10



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

int comparerVilles(const void *a, const void *b) {
    const Avl *villeA = *(const Avl **)a;
    const Avl *villeB = *(const Avl **)b;
    return strcmp(villeA->nom, villeB->nom);
}

int main(void) {

  FILE *fichier = fopen("result.csv", "r");

  if (fichier == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    exit(EXIT_FAILURE);
  }

  Avl *racine=NULL;
  int entier1, entier2;
  char chaine1[75];
  char chaine2[75];
  int *h=malloc(sizeof(int));
  // Lire chaque ligne du fichier
  while (fscanf(fichier, "%d;%d;%[^;\n];%[^;\n]", &entier1, &entier2, chaine1, chaine2) == 4) {
    // Vous avez maintenant les entiers et les chaînes de caractères de la ligne
    // Assurez-vous d'initialiser la racine à NULL avant d'insérer des éléments


      // Appel de la fonction d'insertion AVL avec la chaîne de caractères et le trajet_id
      racine = insertionAVL_D(racine, chaine1, entier1, entier2, h);


      racine = insertionAVL(racine, chaine2, entier1,h);

  }

  // Fermer le fichier
  fclose(fichier);
Avl *topVilles[MAX_VILLES];
    int nbVillesTop = 0;

    parcoursPrefixe(racine, topVilles, &nbVillesTop);

    qsort(topVilles, nbVillesTop, sizeof(Avl *), comparerVilles);


    for (int i = 0; i < nbVillesTop && i < MAX_VILLES; i++) {
        printf("%s;%d;%d\n", topVilles[i]->nom, topVilles[i]->traverse, topVilles[i]->depart);
    }

  return 0;
}
