#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"

int main(void)

{
	//testTrijeux();
	testCreerAdherent();
	return 0;
	
}

//------------------------------------


void testTrijeux(void)
{
	char nomFichier[20];
	int size,i;
	Jeux *tJeux[20];

	/*printf("Saisir nom du fichier :");
	scanf("%s",nomFichier);*/
	printf("\n");
	size=chargerJeux("test2.don",tJeux,20);
	printf("ID du Jeu\tType de Jeu\tNbe exemplaires\t\tNom du Jeu\n");
	printf("\n\n");
	for (i = 0; i < size; i++)
	{
		printf("%s\t\t%s\t\t%d\t%s\n",tJeux[i]->idJeu,tJeux[i]->typeJeu,tJeux[i]->nbExJeu,tJeux[i]->nomJeu);
	}
	printf("\n\n");
	affichageListeJeuxDisponibles(tJeux,size,"carte");
	for (i = 0; i < size; i++)
	{
		free(tJeux[i]);
	}
}


//------------------------------------



void testCreerAdherent(void)
{	
	int size,i;
	Adherent *tAdherent[50],a;
	size=chargerAdherents("adherent.txt",tAdherent,50);
	printf("\n");
	for (i = 0; i < size; i++)
	{
		printf("%s\t",tAdherent[i]->idAdherent);
		affichageDate(tAdherent[i]->dateInscription);
		printf("\t%s\t%s %s",tAdherent[i]->civilite,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent);
		printf("\n");
	}

	printf("\n\n");
	a=creerAdherent(tAdherent,size);
	tAdherent[size]=(Adherent *) malloc(sizeof(Adherent));

		if (tAdherent[size]==NULL)
		{
			printf("Error : problem during allocation !\n");
			return;
		}
	*tAdherent[size]=a;
	size=size+1;

	for (i = 0; i < size; i++)
	{
		printf("%s\t",tAdherent[i]->idAdherent);
		affichageDate(tAdherent[i]->dateInscription);
		printf("\t%s\t%s %s",tAdherent[i]->civilite,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent);
		printf("\n");
	}
	for (i = 0; i < size; i++)
	{
		free(tAdherent[i]);
	}

}

