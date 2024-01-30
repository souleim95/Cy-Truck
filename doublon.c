#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

// Structure pour stocker une ligne du fichier
typedef struct {
    int entier1;
    int entier2;
    char chaine1[MAX_LINE_LENGTH];
    char chaine2[MAX_LINE_LENGTH];
} Line;

// Fonction pour extraire le nom de la ville (en convertissant en majuscules pour la comparaison)
void extractCityName(const char *fullAddress, char *cityName) {
    while (*fullAddress && !isalpha(*fullAddress)) {
        fullAddress++;  // Ignorer les caractères non alphabétiques au début
    }

    while (*fullAddress && (isalpha(*fullAddress) || isspace(*fullAddress))) {
        *cityName++ = toupper(*fullAddress++);
    }

    *cityName = '\0';  // Ajouter la terminaison de la chaîne
}

// Fonction de comparaison pour qsort
int compare_lines(const void *a, const void *b) {
    char cityNameA[MAX_LINE_LENGTH];
    char cityNameB[MAX_LINE_LENGTH];

    extractCityName(((const Line *)a)->chaine1, cityNameA);
    extractCityName(((const Line *)b)->chaine1, cityNameB);

    return strcmp(cityNameA, cityNameB);
}

// Fonction pour supprimer les doublons sur les colonnes 1 et 3, ainsi que sur les colonnes 1 et 4
int removeDuplicates(Line *lines, int numLines) {
    int newNumLines = 1;  // Nouveau nombre de lignes (au moins 1 ligne présente)
    
    for (int i = 1; i < numLines; i++) {
        if (lines[i].entier1 != lines[i - 1].entier1 || strcmp(lines[i].chaine1, lines[i - 1].chaine1) != 0 ||
            strcmp(lines[i].chaine2, lines[i - 1].chaine2) != 0) {
            // Ligne différente de la précédente
            lines[newNumLines++] = lines[i];
        }
    }

    return newNumLines;
}

int main(void) {
    FILE *inputFile = fopen("result.csv", "r");
    FILE *outputFile = fopen("output.csv", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    Line *lines;
    int numLines = 0;

    // Compter le nombre de lignes dans le fichier
    while (fscanf(inputFile, "%*d;%*d;%*[^;];%*[^\n]") == 0) {
        numLines++;
    }

    // Allouer de la mémoire pour stocker les lignes
    lines = malloc(numLines * sizeof(Line));
    if (lines == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    // Retourner au début du fichier
    fseek(inputFile, 0, SEEK_SET);

    // Lire les lignes du fichier et les stocker dans le tableau
    for (int i = 0; i < numLines; i++) {
        if (fscanf(inputFile, "%d;%d;%[^;];%[^\n]", &lines[i].entier1, &lines[i].entier2, lines[i].chaine1, lines[i].chaine2) != 4) {
            fprintf(stderr, "Erreur lors de la lecture de la ligne %d.\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    // Trier le tableau avec qsort
    qsort(lines, numLines, sizeof(Line), compare_lines);

    // Supprimer les doublons
    int newNumLines = removeDuplicates(lines, numLines);

    // Écrire les lignes triées et sans doublons dans le fichier de sortie
    for (int i = 0; i < newNumLines; i++) {
        fprintf(outputFile, "%d;%d;%s;%s\n", lines[i].entier1, lines[i].entier2, lines[i].chaine1, lines[i].chaine2);
    }

    // Libérer la mémoire
    free(lines);

    // Fermer les fichiers
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

