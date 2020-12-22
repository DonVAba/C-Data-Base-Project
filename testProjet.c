#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"

/*void globale(void)
{
	char nomFichier[20];
	int size;
	Jeu *tJeux[40];
	choix=choixMenu();
	while ( choix != 10 )
	{
		if ( choix == 1)
		{
			size=chargerJeux(nomFichier,tJeux,40);
		}
		if( choix == 2)
		{
			size=chargerJeux(
		}
		if( choix == 3)
		{
				
		}
		
		choix = choixMenu();

}*/


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

