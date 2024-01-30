#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avl {
  char nom[50];
  int depart;
  int traverse;
  struct avl *fd;
  struct avl *fg;
  int equilibre;
} Avl;

Avl *creerAvl(char *nom) {
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
  return pnew;
}

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

int min2(int a, int b, int c) { return min(min(a, b), c); }

int max2(int a, int b, int c) { return max(max(a, b), c); }

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

Avl *insertionAVL_D(Avl *a, char *ville1, int e, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvl(ville1);
  } else if (strcmp(ville1, a->nom) < 0) {
    a->fg = insertionAVL_D(a->fg, ville1,e, h);
    *h = -*h;
  } else if (strcmp(ville1, a->nom) > 0) {
    a->fd = insertionAVL_D(a->fd, ville1,e, h);
  } else {
    *h = 0;
         a->traverse+=1;      
    if (e == 1) {
      a->depart+=1;
          a->traverse-=1;     
    }
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

Avl *insertionAVL(Avl *a, char *ville1, int *h) {
  if (a == NULL) {
    *h = 1;
    return creerAvl(ville1);
  } else if (strcmp(ville1, a->nom) < 0) {
    a->fg = insertionAVL(a->fg, ville1, h);
    *h = -*h;
  } else if (strcmp(ville1, a->nom) > 0) {
    a->fd = insertionAVL(a->fd, ville1, h);
  } else {
    *h = 0;
    a->traverse+=1;
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

void parcoursPrefixe(Avl *a){
if(a!=NULL){
  printf("%s;%d;%d\n", a->nom, a->traverse, a->depart);
  parcoursPrefixe(a->fd);
    parcoursPrefixe(a->fg); 
}

}





int main(void) {

  FILE *fichier = fopen("output.csv", "r");

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
    
    if(strcmp(chaine1,chaine2)!=0){
    // Appel de la fonction d'insertion AVL avec la chaîne de caractères
    racine = insertionAVL_D(racine, chaine1, entier2, h);

    // Si vous souhaitez également insérer chaine2, décommentez la ligne suivante
     racine = insertionAVL(racine, chaine2, h);
     }
  }

  // Fermer le fichier
  fclose(fichier);

  parcoursPrefixe(racine);
  
  return 0;
}
