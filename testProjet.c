#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"

int main(void)

{
	char nomFichier[20];
	int size,i;
	Jeux *tJeux[20];

	printf("Saisir nom du fichier :");
	scanf("%s",nomFichier);
	printf("\n");

	size=chargerJeux(nomFichier,tJeux,20);
	for (i = 0; i < size; i++)
	{
		printf("%s\t%s\t%s\t%d\n",tJeux[i]->idJeu,tJeux[i]->nomJeu,tJeux[i]->typeJeu,tJeux[i]->nbExJeu);
	}
	return 0;
	
}

