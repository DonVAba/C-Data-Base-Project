#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"

//---------------------- DATE ------------------------------------------------

Date lireDate(FILE *flot)
{
    Date d;
    fscanf(flot,"%d/%d/%d%*c",&d.jour,&d.mois,&d.annee);
 
	return d;
}

void affichageDate(Date d)
{
	printf("%d/%d/%d",d.jour,d.mois,d.annee);
}

Date ecrireDate(void)
{
    Date d;
    printf("Ecrire le jour(1-31)\n");
    scanf("%d",&d.jour);
    while (d.jour<1 || d.jour>31)
    {
    	printf("Erreur, ecrire correctement le jour(1-31)\n");
    	scanf("%d", &d.jour);
    }


    printf("Ecrire le mois(1-12)\n");
    scanf("%d", &d.mois);
    while (d.mois<1 || d.mois>12)
    {
    	printf("Erreur, ecrire correctement le mois(1-12)\n");
    	scanf("%d", &d.mois);
    }

    printf("Ecrire l'annee(2020-20XX)\n");
    scanf("%d", &d.annee);
    while (d.annee<2020)
    {
    	printf("Erreur, ecrire correctement l'annee(2020-20XX)\n");
    	scanf("%d", &d.annee);
    }
 
	return d;
}		

//---------------------- JEUX ------------------------------------------------

int chargerJeux(char* fileName, Jeux* tJeux[], int maxsize) // Loading the game's file

{
	FILE *flot;
	Jeux j;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	j=lireJeu(flot); //  AFFICHER JEU A FAIRE !!
	while(!feof(flot))
	{
		if (i==maxsize)
		{
			printf("Table is full !\n");
			fclose(flot);
			return -1;
		}
		tJeux[i]=(Jeux *) malloc(sizeof(Jeux));
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


Jeux lireJeu(FILE *flot)
{
	Jeux j;
	fscanf(flot,"%s",j.idJeu);
	fscanf(flot,"%s",j.typeJeu);
	fscanf(flot,"%d",&j.nbExJeu);
	fgets(j.nomJeu,40,flot);
	j.nomJeu[strlen(j.nomJeu)-1]='\0';
	return j;
}

void affichageListeJeuxDisponibles(Jeux* tJeux[],int size,char type[])
{
	int i,j=0;
	Jeux *temp[40];

	for (i = 0; i < size ; i++)
	{
		if (strcmp(tJeux[i]->typeJeu,type)==0)
		{
			if (tJeux[i]->nbExJeu > 0)
			{
				temp[j]=(Jeux *) malloc(sizeof(Jeux));
				if (temp[j]==NULL)
				{
					printf("Error : problem during allocation !\n");
					return ;
				}
				*temp[j]=*tJeux[i];
				j=j+1;
			}
		}
	}
	if (j==0)
	{
		printf("No games available !\n");
		return;
	}
	else
		{
			triJeux(temp,j); 
			for (i = 0; i < j; i++)
			{
				printf("%s\t\t%s\t\t%d\t%s\n",temp[i]->idJeu,temp[i]->typeJeu,temp[i]->nbExJeu,temp[i]->nomJeu);
			}
		}
	for (i = 0; i < j; i++)
	{
		free(temp[i]);
	}

}

void triJeux(Jeux *TempJeux[],int size)
{
	int k,rmin,i;
	for (k = 0; k < size-1; k++)
	{
		rmin=RechercheRMin(TempJeux+k,i,size);
		permutation(TempJeux+k,rmin,rmin+1);
	}
}

int RechercheRMin(Jeux *TempJ[],int i,int n)
{
	int rmin=i,j;
	for (j=i+1; i < n; j++)
	{
		if (strcmp(TempJ[j]->nomJeu,TempJ[rmin]->nomJeu)<0)
		{
			rmin=j;
		}
	}
	return rmin;
}		


void permutation(Jeux *TempJ[],int i,int j)	
{
	Jeux *permutation;
	permutation=TempJ[i];
	TempJ[i]=TempJ[j];
	TempJ[j]=permutation;
}

void testTrijeux(void)
{
	char nomFichier[20];
	int size,i;
	Jeux *tJeux[20];

	/*printf("Saisir nom du fichier :");
	scanf("%s",nomFichier);*/
	printf("\n");
	size=chargerJeux("test.txt",tJeux,20);
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
					
					//Lire Jeux
					//Afficher Liste Jeux
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
	a=lireAdherent(flot); // LIRE Adherents + AFFICHER Adherents A FAIRE !!
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
		a=lireAdherent(flot);

	}
	fclose(flot);
	return i;
}

Adherent lireAdherent(FILE *flot)
{
	Adherent a;
	fscanf(flot,"%s%*c",a.idAdherent);
	a.dateInscription=lireDate(flot);
	fscanf(flot,"%s%*c",a.nomAdherent);
	fgets(a.prenomAdherent,25,flot);
	a.prenomAdherent[strlen(a.prenomAdherent)-1]='\0';
	return a;
}
					//Lire adherent

Adherent creerAdherent(Adherent *tAdherent[],int nbAd)
{

	Adherent a;
	int cherche;
	char monsieur[3]="Mr";
	char madame[4]="Mme";
	char nom[15],prenom[15];
	printf("Saisir votre nom\n");
	fgets(a.nomAdherent,20,stdin);
	a.nomAdherent[strlen(a.nomAdherent)-1]='\0';
	strcpy(nom,a.nomAdherent);
	printf("Saisir votre prénom\n");
	fgets(a.prenomAdherent,20,stdin);
	a.prenomAdherent[strlen(a.prenomAdherent)-1]='\0';
	strcpy(prenom,a.prenomAdherent);
	
	cherche=chercherAdherent(a.prenomAdherent, a.nomAdherent , tAdherent, nbAd);
	if(cherche!=-1)
	{
		printf("L'adherent existe déjà\n");
		//return NULL;
	}

	printf("Saisir votre genre (Mme/Mr)\n");
	scanf("%s",a.civilite);
	printf("%s\n",a.civilite);
	while((strcmp(a.civilite,monsieur)!=0) && strcmp(a.civilite,madame)!=0)
	{	
		printf("Erreur, veuillez saisir correctement votre genre (Mme/Mr)\n");
		scanf("%s", a.civilite);
		printf("%s\n",a.civilite);
	}
	a.dateInscription=ecrireDate();

	creerNomUtil(prenom,nom,4,2,a.idAdherent);

	return a;
}


int chercherAdherent(char*prenom, char*nom, Adherent*tAdherent[], int nbAd)
{
	int i;
	for(i=0;i<nbAd;i++)
		{
			if((strcmp(prenom, tAdherent[i]->prenomAdherent)==0)&&(strcmp(nom,tAdherent[i]->nomAdherent)==0))
				return i;
			
			if((strcmp(prenom, tAdherent[i]->prenomAdherent)==0)&&(strcmp(nom,tAdherent[i]->nomAdherent)<0))
				return -1;
		}
		
	return -1;
}

int blanc(char c)
{
	if (c==' ' || c=='\t' || c=='\n')
	{
		return 1;
	}
	return 0;
}

void supprimeBlanc(char source[],char dest[])
{
	int i=0,j=0;
	while(source[i]!='\0')
	{
		if (blanc(source[i])==0)
		{
			dest[j]=source[i];
			j=j+1;
		}
		i=i+1;
	}
	dest[j]='\0';
}

void partieGauche(char source[],char dest[],int p)
{
	strcpy(dest,source);
	if (p<strlen(source))
		dest[p]='\0';
}



void creerNomUtil(char prenom[],char nom[],int n,int p,char IdUtil[])
{
	supprimeBlanc(prenom,prenom);
	supprimeBlanc(nom,nom);
	partieGauche(prenom,prenom,p);
	partieGauche(nom,nom,n);
	strcpy(IdUtil,strcat(prenom,nom));
}


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
		printf("%s\t%s\t%s",tAdherent[i]->civilite,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent);
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
		printf("\t%s\t%s\t%s",tAdherent[i]->civilite,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent);
		printf("\n");
	}
	for (i = 0; i < size; i++)
	{
		free(tAdherent[i]);
	}

}



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

void affichageReservation(Reservation r)
{	
	printf("ID Réservation\tID Adhérent\tID du jeu\tDate Réservation\n");
	printf("%s\t%s\t%s\t",r.idReservation,r.idAdherent,r.idJeu);
	affichageDate(r.dateReservation);
	printf("\n");
}

Reservation lireReservation(FILE *flot)
{}

					//Lire Reservation
					//chercher Réservation
					


