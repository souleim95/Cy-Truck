#ifndef FONCTION_UTILITAIRE_H
#define FONCTION_UTILITAIRE_H

int max(int a, int b);

int min(int a, int b);

int min2(int a, int b, int c);

int max2(int a, int b, int c);

int comparerVilles(const void *a, const void *b);
void parcoursPrefixe(Avl *racine, Avl** topVilles, int *nbVilles);
#endif
