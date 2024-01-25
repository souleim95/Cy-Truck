#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <operations.h>

int main(int argc, char **argv)
{
	int i=0;

	/*
	printf("\n\n");

	for (i=0; i<argc; i++)
	{
		printf("\nArgument N° %d = %s", i, argv[i]);
	}

	printf("\n\n");
	*/

	if (argc != 3)
	{
		printf("\n");
		printf("Erreur de paramètres, suivre la syntaxe suivante : \n");
		printf("	./main <fichier_csv> <type_trateiemnt>\n\n");
		printf(" Tel-que : \n");
		printf(" 	<fichier_csv> : fichier des données à traitement ....\n");
		printf(" 	<type_traiement> : t ou s\n");

		return 1;
	}

	if (strcmp( argv[2], "t" ) == 0)
	{
		traitement_t(argv[1]);
	}
	else if (strcmp( argv[2], "s" ) == 0)
	{
		traitement_s(argv[1]);
	}
	else{
		printf("\nErreur de type de traitement ...\n\n");
	}

	return 0;
}