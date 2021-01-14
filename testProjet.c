#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"


//------------------------------------


void testTrijeux(void)
{
	char nomFichier[20];
	int nbJeux,i;
	Jeux *tJeux[100];

	printf("\n");
	nbJeux=tailleTableau("jeux.don");
	chargerJeux("jeux.don",tJeux);
	printf("ID du Jeu\tType de Jeu\tNbe exemplaires\t\tNom du Jeu\n");
	printf("\n\n");
	for (i = 0; i < nbJeux; i++)
	{
		printf("%s\t\t%s\t\t%d\t%s\n",tJeux[i]->idJeu,tJeux[i]->typeJeu,tJeux[i]->nbExJeu,tJeux[i]->nomJeu);
	}
	printf("\n\n");
	affichageListeJeuxDisponibles(tJeux,nbJeux,"carte");
	for (i = 0; i < nbJeux; i++)
	{
		free(tJeux[i]);
	}
}


//------------------------------------


void testCreerAdherent(void)
{	
	int nbAdherent,i, chercherAdh, pos;
	Adherent **tAdherent, a, **temptAdherent;
	nbAdherent=tailleTableau("adherents.bin");
	if (nbAdherent==-1)
	{
		return;
	}
	tAdherent=(Adherent**) malloc (nbAdherent*sizeof(Adherent*));
	if(tAdherent == NULL)
	{
		printf("Problème sur malloc\n");
		return;
	}
	chargementBinaireTAdherents(tAdherent);
	printf("\n");
	for (i = 0; i < nbAdherent; i++)
	{
		printf("%s\t",tAdherent[i]->idAdherent);
		affichageDate(tAdherent[i]->dateInscription);
		printf("\t%s\t%s %s",tAdherent[i]->civilite,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent);
		printf("\n");
	}

	printf("\n\n");
	a=creerAdherent(tAdherent, nbAdherent, &chercherAdh);
	if (chercherAdh==-1)
	{
		nbAdherent=nbAdherent+1;
		temptAdherent=(Adherent**) realloc  (tAdherent, nbAdherent*sizeof(Adherent*));
		if (temptAdherent==NULL)
		{
			printf("Probléme sur realloc.\n");
			return;
		}

		tAdherent=temptAdherent;
		tAdherent[nbAdherent-1]=(Adherent *) malloc(sizeof(Adherent));
		if (tAdherent[nbAdherent-1]==NULL)
		{
			printf("Erreur durant l'allocation!\n");
			return;
		}
		pos=rechdichinsertAdherent(a.idAdherent, tAdherent, nbAdherent-1);
		printf("ch=%d\n", chercherAdh);
		printf("pos=%d\n", pos);
		insertionAdherent(tAdherent, a, pos, nbAdherent-1);
	}

	for (i = 0; i < nbAdherent; i++)
	{
		printf("%s\t",tAdherent[i]->idAdherent);
		affichageDate(tAdherent[i]->dateInscription);
		printf("\t%s\t%s %s",tAdherent[i]->civilite,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent);
		printf("\n");
	}
	for (i = 0; i < nbAdherent; i++)
	{
		free(tAdherent[i]);
	}

}



//------------------------------------

int main(void)

{
	//testTrijeux();
	//testCreerAdherent();
	menuGlobal();

	return 0;
	
}
