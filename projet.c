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

int supprimerJeux(Jeux* tJeux[], int nbJeux)
{
	int rang, i;
	char idJeu[10];
	printf("Please type the game ID you want to delete\n");
	scanf("%s%*c", idJeu);
	rang=chercherJeux(idJeu,tJeux,nbJeux);
	
	if (rang==-1)
		return nbJeux;
	free(tJeux[rang]);
	for (i = rang; i < nbJeux-1; i++)
	{
		tJeux[i]=tJeux[i+1];
	}
	return nbJeux-1;
}

int chercherJeux(char idJeu[], Jeux *tJeux[], int nbJeux)
{
	int i;
	for(i=0 ; i < nbJeux ; i++)
		{	
			if(strcmp(idJeu, tJeux[i]->idJeu)==0)
				return i;
			
			//if(strcmp(idJeu, tJeux[i]->idJeu)<0)
			//	return -1;
		}
		
	return -1;
}

void affichageListeJeuxDisponibles(Jeux* tJeux[],int size,char type[]) 		// LISTES possible si jamais
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
			printf("ID du Jeu\tNbe exemplaires\t\tNom du Jeu\n\n");
			for (i = 0; i < j; i++)
			{
				printf("%s\t\t%d\t%s\n",temp[i]->idJeu,temp[i]->nbExJeu,temp[i]->nomJeu);
			}
		}
	for (i = 0; i < j; i++)
	{
		free(temp[i]);
	}

}

void triJeux(Jeux *TempJeux[],int size)
{
	int k,rmin;

	for (k = 0; k < size-1; k++)
	{
		rmin=RechercheRMin(TempJeux,k,size);
		permutation(TempJeux,k,rmin);
	}
}

int RechercheRMin(Jeux *TempJ[],int i,int n)			// Récursivité possible si jamais
{
	int rmin=i,j;
	for (j=i+1; j < n; j++)
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
	Jeux permutation;

	permutation=*TempJ[i];
	*TempJ[i]=*TempJ[j];
	*TempJ[j]=permutation;
}


void sauvegardeJEUXNormale(Jeux *tJeux[], int nbJeux)
{
    FILE *flot;
    int i;
    flot = fopen("jeuxsav.don", "w");
    if (flot == NULL)
    {
        printf("probléme d'ouveture\n");
    }
    fprintf(flot, "%d\n", nbJeux);
    for (i=0; i<nbJeux; i=i+1)
    {

        fprintf(flot, "%s\t%s\t%d\t%s\n", tJeux[i]->idJeu, tJeux[i]->typeJeu, tJeux[i]->nbExJeu, tJeux[i]->nomJeu);
    }
    fclose(flot);
}

void sauvegardeTjeux(Jeux *tJeux[], int nbJeux)
{
	FILE *flot;
	int i;
	flot=fopen("jeux.bin", "wb");
	if(flot == NULL)
	{
		printf("pb d'ouveture de fichier de sauvegarde\n");
		return;
	}
	fprintf(flot, "%d\n", nbJeux);
	for(i=0; i<nbJeux; i++)
	{
		fwrite(tJeux[i], sizeof(Jeux), 1, flot);
	}
	fclose(flot);
}

void restaureTJeux(Jeux *tJeux[], int *nbJeux)
{
	FILE *flot;
	flot = fopen("jeux.bin", "rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return;
	}
	fscanf(flot, "%d%*c", nbJeux);
	*tJeux=(Jeux*) malloc (*nbJeux*sizeof(Jeux));
	if (tJeux == NULL)
	{
		printf("pb sur malloc de tresult\n");
		*nbJeux = -1;
		fclose(flot);
		return;
	}
	fread(*tJeux, sizeof(Jeux), *nbJeux, flot);
	fclose(flot);
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
	fscanf(flot,"%s",a.idAdherent);
	a.dateInscription=lireDate(flot);
	fscanf(flot,"%s",a.civilite);
	fscanf(flot,"%s",a.nomAdherent);
	fgets(a.prenomAdherent,25,flot);
	a.prenomAdherent[strlen(a.prenomAdherent)-1]='\0';
	return a;
}
					//Lire adherent

Adherent creerAdherent(Adherent *tAdherent[],int nbAdherent)
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
	minuscule(nom);
	printf("Saisir votre prénom\n");
	fgets(a.prenomAdherent,20,stdin);
	a.prenomAdherent[strlen(a.prenomAdherent)-1]='\0';
	strcpy(prenom,a.prenomAdherent);
	minuscule(prenom);
	
	cherche=chercherAdherent(a.idAdherent,tAdherent,nbAdherent);
	if(cherche!=-1)
	{
		printf("L'adherent existe déjà\n");
		//return NULL;
	}

	printf("Saisir votre genre (Mme/Mr)\n");
	scanf("%s",a.civilite);
	while((strcmp(a.civilite,monsieur)!=0) && strcmp(a.civilite,madame)!=0)
	{	
		printf("Erreur, veuillez saisir correctement votre genre (Mme/Mr)\n");
		scanf("%s", a.civilite);
		printf("%s\n",a.civilite);
	}
	a.dateInscription=ecrireDate();

	creerNomUtil(prenom,nom,6,2,a.idAdherent);

	return a;
}


int chercherAdherent(char *idAdherent,Adherent *tAdherent[],int nbAdherent)
{
	int i;
	for(i=0 ; i < nbAdherent ; i++)
		{
			if(strcmp(idAdherent, tAdherent[i]->idAdherent)==0)
				return i;
			
			//if(strcmp(idAdherent, tAdherent[i]->prenomAdherent)<0)
				//return -1;
		}
		
	return -1;
}

int supprimerAdherent(Adherent *tAdherent[], int nbAdherent)
{
	int rang, i;
	char idAdherent[20];
	printf("Please type the user ID you want to delete\n");
	scanf("%s%*c", idAdherent);
	rang=chercherAdherent(idAdherent,tAdherent,nbAdherent);
	
	if (rang==-1)
		return nbAdherent;
	free(tAdherent[rang]);
	for (i = rang; i < nbAdherent-1; i++)
	{
		tAdherent[i]=tAdherent[i+1];
	}
	return nbAdherent-1;
}



void sauvegardeNormaleAdherent(Adherent *tAdherent[], int nbAdherent)
{
    FILE *flot;
    int i;
    flot = fopen("adherentsav.don", "w");
    if (flot == NULL)
    {
        printf("probléme d'ouveture\n");
    }
    fprintf(flot, "%d\n", nbAdherent);
    for (i=0; i<nbAdherent; i=i+1)
    {

        fprintf(flot, "%s\t%d/%d/%d\t%s\t%s\t%s\n", tAdherent[i]->idAdherent, tAdherent[i]->dateInscription.jour, tAdherent[i]->dateInscription.mois, tAdherent[i]->dateInscription.annee, tAdherent[i]->civilite, tAdherent[i]->nomAdherent, tAdherent[i]->prenomAdherent);
    }
    fclose(flot);
}


void creerNomUtil(char prenom[],char nom[],int n,int p,char IdUtil[])
{
	supprimeBlanc(prenom,prenom);
	supprimeBlanc(nom,nom);
	partieGauche(prenom,prenom,p);
	partieGauche(nom,nom,n);
	strcpy(IdUtil,strcat(prenom,nom));
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

void minuscule(char chaine[])
{
	int i;
	
	for (i=0; chaine[i]!='\0'; i++)
	{
		
		if(chaine[i]>='A' && chaine[i]<='Z')
			chaine[i] -='A' - 'a';

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

ListeEmprunt chargerListeEmprunt(char* fileName,ListeEmprunt le)
{
	FILE *flot;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		exit(1);
	}
	le=mettreEnListe(flot,le);
	fclose(flot);
	return le;
	

}

ListeEmprunt mettreEnListe(FILE *flot,ListeEmprunt le)
{
	Emprunt e;

	if (feof(flot))
	{
		return NULL;
	}
	
	e=lireEmprunt(flot);
	le=InsertionEnTete(le,e);
	le->suivant=mettreEnListe(flot,le->suivant);
	return le;
	
}

Emprunt lireEmprunt(FILE *flot)
{
    Emprunt e;
    fscanf(flot,"%s%s%s", e.idEmprunt,e.idAdherent, e.idJeu);
    e.dateEmprunt=lireDate(flot);
    return e;
}


					
					

ListeEmprunt empruntvide(void)
{
	return NULL;
}

ListeEmprunt InsertionEnTete(ListeEmprunt le,Emprunt emp)
{
	ListeEmprunt le1;

	le1=(ListeEmprunt)malloc(sizeof(MaillonE));
	if (le1==NULL)
		return NULL;
	le1->e=emp;
	le1->suivant=le;
	return le1;
}

void AfficherListeEmprunt(ListeEmprunt le,Adherent *tAdherent[],int nbAdherent, Jeux* tJeux[],int nbJeux)	// A COMPLETER
{
	int i,j;
	if (le==NULL)
	{
		return;
	}

	i=chercherAdherent(le->e.idAdherent,tAdherent,nbAdherent);
	if (i == -1)
	{
		return;
	}
	j=chercherJeux(le->e.idJeu,tJeux,nbJeux);
	if (j == -1)
	{
		return;
	}
	printf("ID EMPRUNT : %s\n",le->e.idEmprunt);
	printf("IDENTITÉ : %s ",tAdherent[i]->nomAdherent);
	printf("%s\n",tAdherent[i]->prenomAdherent);
	printf("NOM DU JEU : %s\n",tJeux[j]->nomJeu);
//	printf("%s \t %s \t %s \t %s \t",le->e.idEmprunt,tAdherent[i]->nomAdherent,tAdherent[i]->prenomAdherent,tJeux[j]->nomJeu);
	printf("DATE EMPRUNT : ");
	affichageDate(le->e.dateEmprunt);
	printf("\n\n\n");
	AfficherListeEmprunt(le->suivant,tAdherent,nbAdherent,tJeux,nbJeux);
}




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
			

//----------------------------- MENU -------------------------------------------	









void afficherMenuType(void)
{
	printf("------------------------------------------------------------------\n\n");
	printf("\t1)\t Construction\n");
	printf("\t2)\t Plateau\n");
	printf("\t3)\t Tuile\n");
	printf("\t4)\t Carte\n");
	printf("\t5)\t Logique\n\n");
	printf("\t6)\t Retour\n\n");
	printf("------------------------------------------------------------------\n");

}

int choixMenuType(void)
{
	int choix;
	system("clear");
	afficherMenuType();
	printf("Please select an option :\n");
	scanf("%d", &choix);
	
	while(choix<1 || choix>6)
	{
		system("clear");
		printf("Error : try to select a right option :\n");
		afficherMenuType();
		scanf("%d", &choix);
		
	}
	return choix;

}



void MenuType(void)
{
	int choix=choixMenuType();
	while(choix!=6)
	{
		if (choix==1)
			printf("choix 1\n");return;
		if(choix==2)
			printf("choix 2\n");return;
		if (choix==3)
			printf("choix 3\n");return;
		if(choix==4)
			printf("choix 4\n");return;
		if (choix==5)
			printf("choix 5\n");return;
		
	}
	return;
}

void afficherSousMenuEmprunt(void)
{
	printf("------------------------------------------------------------------\n\n");
	printf("\t1)\t Trie par type\n");
	printf("\t2)\t Tout voir\n");
	printf("\t3)\t Retour\n");
	printf("------------------------------------------------------------------\n");
}

int choixSousMenuEmprunt(void)
{
	int choix;
	system("clear");
	afficherSousMenuEmprunt();
	printf("Please select an option :\n");
	scanf("%d", &choix);
	
	while(choix<1 || choix>3)
	{
		system("clear");
		printf("Error : try to select a right option :\n");
		afficherSousMenuEmprunt();
		printf("Error : try to select a right option :\n");
		scanf("%d", &choix);
		
	}
	return choix;

}

void sousMenuEmprunt(void)
{
	int choix=choixSousMenuEmprunt();
	while(choix!=3)
	{
		if (choix==1)
			MenuType();
		if(choix==2)
			printf("choix 2\n");
		choix=choixSousMenuEmprunt();
	}
	return;
}