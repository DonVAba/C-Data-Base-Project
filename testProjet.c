#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"

int main(void)

{
	char nomFichier[20];
	int size;
	Jeu *tJeux[40];

	printf("Saisir nom du fichier :");
	scanf("%s%*c",nomFichier);
	printf("\n");

	size=chargerJeux(nomFichier,tJeux,40);
	affichageJeux(size, tJeux);
	return 0;
	
}

