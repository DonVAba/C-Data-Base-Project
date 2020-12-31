#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"


//------------------------------------

/*
void testTrijeux(void)
{
	char nomFichier[20];
	int size,i;
	Jeux *tJeux[20];

	//printf("Saisir nom du fichier :");
	//scanf("%s",nomFichier);
	printf("\n");
	size=chargerJeux("jeux.don",tJeux,20);
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
*/

//------------------------------------


/*void testCreerAdherent(void)
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


void testEmprunt(void)
{
	ListeEmprunt le;
	Adherent *tAdherent[50],a;
	Jeux *tJeux[20];
	int nbJeux,nbAdherent;

	nbJeux=chargerJeux("jeux.don",tJeux,20);
	nbAdherent=chargerAdherents("test2.don",tAdherent,50);
	le=chargerListeEmprunt("emprunt.don",le);
	printf("\n");
	AfficherListeEmprunt(le,tAdherent,nbAdherent,tJeux,nbJeux);
}

void testChercherAdherent(void)
{
	int size,i;
	Adherent *tAdherent[50],a;
	size=chargerAdherents("test2.don",tAdherent,50);

	i=chercherAdherent("bamartel",tAdherent,size);
	printf("%d\n",i);

	for (i = 0; i < size; i++)
	{
		free(tAdherent[i]);
	}
}



/*void testFaireEmprunt(void)
{
	int sizeJ, sizeA, i;
	Adherent *tAdherent[50],a;
	
	Emprunt e;
	ListeEmprunt le;
	
	Jeux *tJeux[20];
	sizeJ=chargerJeux("jeux.don",tJeux,20);
	sizeA=chargerAdherents("test2.don",tAdherent,50);
	e=faireEmprunt(le, tJeux, tAdherent, sizeJ, sizeA);
	return;
}
*/

//------------------------------------

int main(void)

{
	//testTrijeux();
	//testCreerAdherent();
	//testEmprunt();
	//testChercherAdherent();
	//testFaireEmprunt();
	int i;
	menuGlobal();

	return 0;
	
}