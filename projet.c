#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"

//---------------------- DATE ------------------------------------------------

Date lireDate(FILE *flot)
{
	Date d;
	fscanf(flot,"%d%d%d", &d.jour, &d.mois, &d.annee);
 	return d;
}

void affichageDate(Date d)
{
	printf("%d/%d/%d\n",d.jour,d.mois,d.annee);
}


//---------------------- JEUX ------------------------------------------------

int chargerJeux(char* fileName, Jeu* tJeux[], int maxsize) // Loading the game's file

{
	FILE *flot;
	Jeu j;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	j=lireJeu(flot); // LIRE JEU + AFFICHER JEU A FAIRE !!
	while(!feof(flot))
	{
		if (i==maxsize)
		{
			printf("Table is full !\n");
			fclose(flot);
			return -1;
		}
		tJeux[i]=(Jeu *) malloc(sizeof(Jeu));
		if (tJeux[i]==NULL)
		{
			printf("Error : problem during allocation !\n");
			fclose(flot);
			return -1;
		}
		*tJeux[i]=j;
		i=i+1;
		j=lireJeu(flot);

	}
	fclose(flot);
	return i;
}


Jeu lireJeu(FILE *flot)
{
	Jeu j;
	int n;
	fscanf(flot,"%s",j.idJeu);
	fscanf(flot,"%s",j.typeJeu);
	fscanf(flot,"%d",&j.nbExJeu);
	fgets(j.nomJeu, 40, flot);
	n = strlen(j.nomJeu);
	if(j.nomJeu[n-1]=='\n')
		j.nomJeu[n-1]='\0';
	//fscanf(flot,"%s",j.nomJeu);
	//j.nomJeu[strlen(j.nomJeu)-1]='\0';
	return j;
}

					//Lire Jeux
void affichageJeux(int size, Jeu *tJeux[])  //Afficher Liste Jeux
{
	int i;
	for (i = 0; i < size; i++)
	{
		//printf("%s\t%s\t%s\t%d\n",tJeux[i]->idJeu, tJeux[i]->nomJeu, tJeux[i]->typeJeu, tJeux[i]->nbExJeu);
		printf("%s/%s/%s/\t\t\t%d\n",tJeux[i]->idJeu, tJeux[i]->nomJeu, tJeux[i]->typeJeu, tJeux[i]->nbExJeu);
	}
}
				//Recherche Jeux


//---------------------- ADHERENTS ------------------------------------------------


int chargerAdherents(char* fileName, Adherent* tAdherent[], int maxsize) // Loading the adherent's file

{
	FILE *flot;
	Adherent a;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	//a=lireAdherent(flot); // LIRE Adherents + AFFICHER Adherents A FAIRE !!
	while(!feof(flot))
	{
		if (i==maxsize)
		{
			printf("Table is full !\n");
			fclose(flot);
			return -1;
		}
		tAdherent[i]=(Adherent *) malloc(sizeof(Adherent));
		if (tAdherent[i]==NULL)
		{
			printf("Error : problem during allocation !\n");
			fclose(flot);
			return -1;
		}
		*tAdherent[i]=a;
		i=i+1;
		//a=lireAdherent(flot);

	}
	fclose(flot);
	return i;			// retourne le nombre de jeux
}

					//Lire adherent
					//Afficher adherent



//---------------------- EMPRUNT ------------------------------------------------

int chargerEmprunt(char* fileName, Emprunt* tEmprunt[], int maxsize) // Loading the loan's file

{
	FILE *flot;
	Emprunt e;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	e=lireEmprunt(flot); // LIRE Emprunt + AFFICHER Emprunt A FAIRE !!
	while(!feof(flot))
	{
		if (i==maxsize)
		{
			printf("Table is full !\n");
			fclose(flot);
			return -1;
		}
		tEmprunt[i]=(Emprunt *) malloc(sizeof(Emprunt));
		if (tEmprunt[i]==NULL)
		{
			printf("Error : problem during allocation !\n");
			fclose(flot);
			return -1;
		}
		*tEmprunt[i]=e;
		i=i+1;
		e=lireEmprunt(flot);

	}
	fclose(flot);
	return i;
}

Emprunt lireEmprunt(FILE *flot)
{
    Emprunt e;
    fscanf(flot,"%s%s%s", e.idEmprunt,e.idAdherent, e.idJeux);
    e.dateEmprunt=lireDate(flot);
    return e;
}

					//Lire Emprunt
					//Afficher Emprunt



//---------------------- Reservation ------------------------------------------------

int chargerReservation(char* fileName, Reservation* tReservation[], int maxsize) // Loading the reservation's file

{
	FILE *flot;
	Reservation r;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	r=lireReservation(flot); // LIRE Reservation + AFFICHER Reservation A FAIRE !!
	while(!feof(flot))
	{
		if (i==maxsize)
		{
			printf("Table is full !\n");
			fclose(flot);
			return -1;
		}
		tReservation[i]=(Reservation *) malloc(sizeof(Reservation));
		if (tReservation[i]==NULL)
		{
			printf("Error : problem during allocation !\n");
			fclose(flot);
			return -1;
		}
		*tReservation[i]=r;
		i=i+1;
		r=lireReservation(flot);

	}
	fclose(flot);
	return i;
}

Reservation lireReservation(FILE *flot)
{
	Reservation r;
	fscanf(flot,"%s%s%s", r.idReservation, r.idAdherent, r.idJeu);
	r.dateReservation=lireDate(flot);
	return r;
}


void affichageReservation(Reservation r)
{	
	printf("ID Réservation\tID Adhérent\tID du jeu\tDate Réservation\n");
	printf("%s\t%s\t%s\t",r.idReservation,r.idAdherent,r.idJeu);
	affichageDate(r.dateReservation);
	printf("\n");
}

					//Lire Reservation
					//chercher Réservation
					
//---------------------- Sauvegrade en binaire------------------------------------------			

void sauvegardeTjeux(Jeu *tJeux[], int nbJeux)
{
	FILE *flot;
	flot=fopen("jeux.bin", "wb");
	if(flot == NULL)
	{
		printf("pb d'ouveture de fichier de sauvegarde\n");
		return;
	}
	fprintf(flot, "%d\n", nbJeux);
	fwrite(tJeux, sizeof(Jeu), nbJeux, flot);
	fclose(flot);
}

//--------------------- Restauration/Chargement des fichiers binaires-------------------

void restaureTJeux(Jeu *tJeux[], int *nbJeux)
{
	FILE *flot;
	flot = fopen("jeux.bin","rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return;
	}
	fscanf(flot, "%d%*c", nbJeux);
	*tJeux=(Jeu*) malloc (*nbJeux*sizeof(Jeu));
	if (tJeux == NULL)
	{
		printf("pb sur malloc de tresult\n");
		*nbJeux = -1;
		fclose(flot);
		return;
	}
	fread(*tJeux, sizeof(Jeu), *nbJeux, flot);
	fclose(flot);
}




























