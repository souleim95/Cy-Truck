#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl1.h"
#include "trajet.h"
#include "fonction_utilitaire.h"
#define TAILLE_VILLE 35
#define MAX_VILLES 10


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
