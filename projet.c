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


Date plusRecenteDate(Date d1,Date d2)
{
	if (d1.annee>d2.annee)
	{
		return d1;
	}
	if (d2.annee>d1.annee)
	{
		return d2;
	}
	else
	{
		if (d1.mois>d2.mois)		
		{
			return d2;
		}
		if (d2.mois>d1.mois)
		{
			return d1;
		}
		else
			{
				if (d1.jour>d2.jour)		
				{
					return d2;
				}
				if (d2.jour>d1.jour)
					{
						return d1;
					}
				else
					return d1;	
			}
	}
}	




//---------------------- JEUX ------------------------------------------------






int chargerJeux(char* fileName, Jeux* tJeux[]) // Loading the game's file

{
	FILE *flot;
	Jeux j;
	int i,nbJeux;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	fscanf(flot,"%d%*c",&nbJeux);
	tJeux=malloc(nbJeux*sizeof(Jeux));
	j=lireJeu(flot);
	for (i = 0; i < nbJeux; i++)
	{
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
	return nbJeux;
}

int chargementBinaireTJeux(Jeux **tJeux)
{
	int i, nbJeux;
	Jeux j;
	FILE *flot;
	flot = fopen("jeux.bin","rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return -1;
	}
	fscanf(flot, "%d%*c", &nbJeux);
	printf("%d\n", nbJeux);
	tJeux=malloc (nbJeux*sizeof(Jeux));
	if(tJeux == NULL)
	{
		printf("Problème sur malloc\n");
		return -1;
	}	
	fread(&j, sizeof(Jeux), 1, flot);
	for (i=0; i<nbJeux; i++)
	{
		tJeux[i]=(Jeux *) malloc(sizeof(Jeux));
		if (tJeux[i]==NULL)
		{
			printf("Problème durant l'allocation !\n");
			fclose(flot);
			return -1;
		}
		*tJeux[i]=j;
		fread(&j, sizeof(Jeux), 1, flot);
	}
	fclose (flot);
	return nbJeux;
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
			
			if(strcmp(idJeu, tJeux[i]->idJeu)<0)
				return i;
		}
		
	return -1;
}

void affichageTousJeux(Jeux* tJeux[],int GameSize)
{
	int i;
	for (i = 0; i < GameSize ; i++)
	{
		printf("%s\t\t%s\t%d\t\t\t%s\n",tJeux[i]->idJeu,tJeux[i]->typeJeu,tJeux[i]->nbExJeu,tJeux[i]->nomJeu);
	}
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
				printf("%s\t\t%d\t\t\t%s\n",temp[i]->idJeu,temp[i]->nbExJeu,temp[i]->nomJeu);
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

void retourJeux(Jeux *tJeux[],ListeEmprunt le,ListeReservation lr,int nbJeux) 
{	
	int r,i;
	Emprunt e;
	Date d;
	char idEmprunt[20],tempIdJeu[20];

	printf("Saisir l'ID de votre emprunt : ");
	scanf("%s",idEmprunt);
	le=chercherEmprunt(le,idEmprunt);
	if (le==NULL)
	{
		printf("\nErreur : L'emprunt %s n'existe pas !",idEmprunt);
		return;
	}
	strcpy(tempIdJeu,le->e.idJeu);
	le=supprimerEmprunt(le,idEmprunt);
	lr=rechercheReservation(lr,tempIdJeu);
	if (lr!=NULL)
	{
		d=ecrireDate();
		e=creationEmprunt(lr->res.idJeu,lr->res.idAdherent,d);
		le=ajouterEmprunt(le,e);
		lr=supprimerUneReservation(lr,lr->res);
	}
	else
	{	
		i=chercherJeux(le->e.idJeu,tJeux,nbJeux);
		tJeux[i]->nbExJeu=tJeux[i]->nbExJeu+1;
		return;
	}	
	


}


int ajouterJeux(Jeux *tJeux[], int nbJeux)
{
	Jeux j;
	int i,rang;
	j=creerJeux(tJeux,nbJeux,&rang);
	for (i = nbJeux-1; i > rang; i--)
	{
		tJeux[i+1]=tJeux[i];
	}
	return nbJeux+1;
}

Jeux creerJeux(Jeux *tJeux[], int nbJeux,int *rang)
{

	Jeux j;
	
	char idJeu[10], nomJeu[25], typeJeu[25];
	printf("Saisir l'ID du jeu\n");
	scanf("%s*c",j.idJeu);
	minuscule(j.idJeu);
	*rang=chercherJeux(j.idJeu,tJeux,nbJeux);
	if(*rang!=-1)
	{
		printf("Le jeux existe déjà\n");
		
	}
	printf("Saisir le nom du jeu\n");
	fgets(j.nomJeu,25,stdin);
	j.nomJeu[strlen(j.nomJeu)-1]='\0';
	minuscule(j.nomJeu);

	printf("Saisir le type du jeu (construction, plateau, tuile, carte, logique)\n");
	scanf("%s*c",j.typeJeu);
	minuscule(j.typeJeu);
	while((strcmp(j.typeJeu,"construction")!=0)&&(strcmp(j.typeJeu,"plateau")!=0)&&(strcmp(j.typeJeu,"tuile")!=0)&&(strcmp(j.typeJeu,"carte")!=0)&&(strcmp(j.typeJeu,"logique")!=0))
	{
		printf("Erreur, veuillez saisir correctement le type (construction, plateau, tuile, carte, logique)\n");
		scanf("%s%*c",j.typeJeu);
	}
	printf("Saisir le nombre d'exemplaire\n");
	scanf("%d%*c", j.nbExJeu);
	return j;
}

/*
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
*/

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

	for (i = 0; i < nbJeux; i++)
	{
		free(tJeux[i]);
	}
	free(tJeux);
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
	fscanf(flot,"%d%*c",nbJeux);
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
					

					


//---------------------- ADHERENTS ------------------------------------------------







int chargerAdherents(char* fileName, Adherent* tAdherent[]) // Loading the adherent's file

{
	FILE *flot;
	Adherent a;
	int i,nbAdherent;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("Error : File %s can't be opened !\n",fileName);
		return -1;
	}
	fscanf(flot,"%d%*c",&nbAdherent);
	tAdherent=malloc (nbAdherent*sizeof(Adherent));
	a=lireAdherent(flot);
	for(i=0; i <  nbAdherent ; i++)
	{
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
	return nbAdherent;
}

void triAdherent(Adherent *TempAdherent[],int size)
{
	int k,rmin;

	for (k = 0; k < size-1; k++)
	{
		rmin=RechercheRMinA(TempAdherent,k,size);
		permutationA(TempAdherent,k,rmin);
	}
}

int RechercheRMinA(Adherent *TempA[],int i,int n)			// Récursivité possible si jamais
{
	int rmin=i,j;
	for (j=i+1; j < n; j++)
	{
		if (strcmp(TempA[j]->idAdherent,TempA[rmin]->idAdherent)<0)
		{

			rmin=j;
		}
	}

	return rmin;
}		


void permutationA(Adherent *TempA[],int i,int j)	
{
	Adherent permutation;

	permutation=*TempA[i];
	*TempA[i]=*TempA[j];
	*TempA[j]=permutation;
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


int chercherAdherent(char idAdherent[],Adherent *tAdherent[],int nbAdherent)
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


void sauvegardeTAdherentBinaire(Adherent *tAdherents[], int nbAdherents)
{
	FILE *flot;
	int i;
	flot=fopen("adherents.bin", "wb");
	if(flot == NULL)
	{
		printf("pb d'ouveture de fichier de sauvegarde\n");
		return;
	}
	fprintf(flot, "%d\n", nbAdherents);
	for(i=0; i<nbAdherents; i++)
	{
		fwrite(tAdherents[i], sizeof(Adherent), 1, flot);
	}
	fclose(flot);
	for(i=0; i<nbAdherents; i++)
	{
		free(tAdherents[i]);
	}
	free (tAdherents);
}

int chargementBinaireTAdherents(Adherent **tAdherent)
{
	int i, nbAdherent;
	Adherent a;
	FILE *flot;
	flot = fopen("adherents.bin","rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return -1;
	}
	fscanf(flot, "%d%*c", &nbAdherent);
	tAdherent=malloc (nbAdherent*sizeof(Adherent));
	if(tAdherent == NULL)
	{
		printf("Problème sur malloc\n");
		return -1;
	}
	fread(&a, sizeof(Adherent), 1, flot);
	for (i=0; i<nbAdherent; i++)
	{
		tAdherent[i]=(Adherent *) malloc(sizeof(Adherent));
		if (tAdherent[i]==NULL)
		{
			printf("Error : problem during allocation !\n");
			fclose(flot);
			return -1;
		}
		*tAdherent[i]=a;
		fread(&a, sizeof(Adherent), 1, flot);
	}
	fclose (flot);
	return nbAdherent;
}






//---------------------- EMPRUNT ------------------------------------------------






/*

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
*/

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
	le=empruntvide();
	le=mettreEnListe(flot,le);
	fclose(flot);
	return le;
}


ListeEmprunt mettreEnListe(FILE *flot,ListeEmprunt le)
{
	Emprunt e;
	le=empruntvide();
	e=lireEmprunt(flot);
	while (!feof(flot))
	{
		le=InsertionEnTete(le,e);
		e=lireEmprunt(flot);
	}
	return le;
}


Emprunt lireEmprunt(FILE *flot)
{
    Emprunt e;
    fscanf(flot,"%s%s%s", e.idEmprunt,e.idAdherent, e.idJeu);
    e.dateEmprunt=lireDate(flot);
    return e;
}

void creationidEmprunt(char idJeu[],char idAdherent[],Date d,char idEmprunt[])
{	
	char temp[2];

	strcpy(idEmprunt, "R");
	strcat(idEmprunt, idJeu);
	sprintf(temp, "%d", d.annee);
	strcat(idEmprunt, temp);
	sprintf(temp, "%d", d.mois);
	strcat(idEmprunt, temp);
	sprintf(temp, "%d", d.jour);
	strcat(idEmprunt, temp);
	strcat(idEmprunt, idAdherent);
}


Emprunt creationEmprunt(char idJeu[],char idAdherent[],Date d)
{
	Emprunt e;
	char idEmprunt[20];
	creationidEmprunt(idJeu,idAdherent,d,idEmprunt);
	strcpy(e.idEmprunt,idEmprunt);
	strcpy(e.idJeu,idJeu);
	strcpy(e.idAdherent,idAdherent);
	e.dateEmprunt=d;
	return e;
}

					
					

ListeEmprunt empruntvide(void)
{
	return NULL;
}

ListeEmprunt ajouterEmprunt(ListeEmprunt le,Emprunt em)
{
	Date d;
	if (le==NULL)
	{
		return InsertionEnTete(le,em);
	}
	d=plusRecenteDate(le->e.dateEmprunt,em.dateEmprunt);
	if (d.mois==em.dateEmprunt.mois && d.jour==em.dateEmprunt.jour && d.annee==em.dateEmprunt.annee)
	{
		return InsertionEnTete(le,em);
	}
	le->suivant=ajouterEmprunt(le->suivant,em);
	return le;
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
	printf("IDENTITÉ : %s",tAdherent[i]->nomAdherent);
	printf("%s\n",tAdherent[i]->prenomAdherent);
	printf("NOM DU JEU : %s\n",tJeux[j]->nomJeu);
	printf("DATE EMPRUNT : ");
	affichageDate(le->e.dateEmprunt);
	printf("\n\n");
	AfficherListeEmprunt(le->suivant,tAdherent,nbAdherent,tJeux,nbJeux);
}

ListeEmprunt chercherEmprunt(ListeEmprunt le,char idEmprunt[])
{
	int i=0;
	if (le==NULL)
	{
		return le;
	}
	if (strcmp(le->e.idEmprunt,idEmprunt)==0)
			return le;
	else
		{
			le->suivant=chercherEmprunt(le->suivant,idEmprunt);
			return le;
		}
}

ListeEmprunt supprimerEmprunt(ListeEmprunt le,char idEmprunt[])
{
	if (strcpy(le->e.idEmprunt,idEmprunt)==0)
	{
		return supprimerEnTeteEmprunt(le);
	}
	le->suivant=supprimerEmprunt(le->suivant,idEmprunt);
}

ListeEmprunt supprimerEnTeteEmprunt(ListeEmprunt le)
{
	ListeEmprunt svt;
	svt=le->suivant;
	free(le);
	return svt;
}


void faireUnEmpruntouUneReservation(ListeEmprunt le, ListeReservation lr, Jeux* tJeux[], Adherent* tAdherent[], int nbJeux, int nbAdherent)
{
	int rangJ, rangA, nbEmp=0;
	Emprunt e;
	Reservation r;
	Date date;
	char idJeu[20], choix, idAdherent[20],idReservation[20];

	printf("Saisir votre ID d'adherent\n");
	scanf("%s", idAdherent);
	rangA=chercherAdherent(idAdherent, tAdherent, nbAdherent);
	printf("%d\n", rangA);
	while(rangA==-1)
	{
		printf("L'adherent n'existe pas, retaper un ID valide, tapez 'exit' pour sortir\n");
		scanf("%s", idAdherent);
		if (strcmp(idAdherent,"exit")==0)
			return;
		rangA=chercherAdherent(idAdherent, tAdherent, nbAdherent);
	}
	
	printf("L'emprunt va etre réalisé pour l'adherent %s\n", idAdherent );
	printf("Saisir l'ID du jeu que vous voulez emprunter : (32c/kp/...)\n");
	scanf("%s", idJeu);
	rangJ=chercherJeux(idJeu, tJeux, nbJeux);
	while(rangJ==-1)
	{
		printf("Le jeu n'existe pas, retaper un ID valide, tapez 'exit' pour sortir\n");
		scanf("%s", idJeu);
		if (strcmp(idJeu,"exit")==0)
			return;
		rangJ=chercherJeux(idJeu,tJeux,nbJeux);
	}
	printf("L'emprunt ou la réservation va etre réalisé pour le jeux %s\n", idJeu);
	printf("Saisir la date :\n");
	date=ecrireDate();
	if (tJeux[rangJ]->nbExJeu==0)
	{
		printf("Le jeux n'est pas disponible voulez vous le réserver ? (y/n)\n");
		scanf("%c%*c", &choix);
		if (choix == 'n')
			return;
		r=creationReservation(idJeu, idAdherent,date);
		lr=ajouterReservation(lr, r);
	}
	else
	{
		nbEmp=CompteEmprunt(le, e, nbEmp);
		if (nbEmp > 3)
		{
			printf("Cet Adherent a déjà 3 emprunts en cours\n");
		}
		printf("à faire\n");
		e=creationEmprunt(idJeu,idAdherent,date);
		le=ajouterEmprunt(le,e);
		tJeux[rangJ]->nbExJeu=tJeux[rangJ]->nbExJeu-1;
	}
}

int CompteEmprunt(ListeEmprunt le, Emprunt emp, int i)
{
	if(le==NULL)
	{
		return i;
	}
	if(strcmp(le->e.idAdherent, emp.idAdherent)== 0)
	{
		i++;
	}
	i=CompteEmprunt(le->suivant, emp, i);

}

void sauvegardeBinaireEmprunts(ListeEmprunt le)
{
	FILE *flot;
	flot=fopen("emprunts.bin", "wb");
	if(flot == NULL)
	{
		printf("pb d'ouveture de fichier de sauvegarde\n");
		return;
	}
	while(!(le == NULL))
	{
		fwrite(le, sizeof(Emprunt), 1, flot);
		le=le->suivant;
	}
	fclose(flot);
	freeListeEmprunt(le);
}

ListeEmprunt chargementBinairetEmrunts(void)
{
	ListeEmprunt le;
	Emprunt e;
	FILE *flot;
	flot = fopen("emprunts.bin","rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return NULL;
	}
	le=empruntvide();
	fread(&e, sizeof(Emprunt), 1, flot);
	while(!feof(flot))
	{
		le=InsertionEnTete(le, e);
		fread(&e, sizeof(Emprunt), 1, flot);
	}
	fclose (flot);
	return le;
}

void freeListeEmprunt(ListeEmprunt le)
{
	if(le == NULL)
	{
		return;
	}
	free(le);
	freeListeEmprunt(le->suivant);
}



//---------------------- Reservation ------------------------------------------------











ListeReservation reservationVide(void)
{
	return NULL;
}

ListeReservation ajouterEnTete(ListeReservation lr, Reservation r)
{
	MaillonR *a;
	a=(MaillonR*)malloc(sizeof(MaillonR));
	a->res = r;
	a->suivant=lr;
	return a;
}

ListeReservation CreationDeLaListe(ListeReservation lr)
{
	Reservation r;
	FILE *flot;
	flot=fopen("reservations.don", "r");
	lr=reservationVide();
	r=lireReservation(flot);
	while(!feof(flot))
	{
		lr=ajouterReservation(lr, r);
		r=lireReservation(flot);
	}
	return lr;
}


Reservation lireReservation(FILE *flot)
{
	Reservation r;
	fscanf(flot, "%s%s%s", r.idReservation, r.idAdherent, r.idJeu);
	r.dateReservation=lireDate(flot);
	return r;
}

void freeListeReservation(ListeReservation lr)
{
	if(lr == NULL)
	{
		return;
	}
	free(lr);
	freeListeReservation(lr->suivant);
}

Reservation creationReservation(char idJeu[20], char idAdherent[20],Date dateReservation)
{
	Reservation r;
	char temp[2];
	r.dateReservation=dateReservation;
	strcpy(r.idJeu, idJeu);
	strcpy(r.idAdherent, idAdherent);
	strcpy(r.idReservation, "R");
	strcat(r.idReservation, idJeu);
	sprintf(temp, "%d", r.dateReservation.annee);
	strcat(r.idReservation, temp);
	sprintf(temp, "%d", r.dateReservation.mois);
	strcat(r.idReservation, temp);
	sprintf(temp, "%d", r.dateReservation.jour);
	strcat(r.idReservation, temp);
	strcat(r.idReservation, r.idAdherent);
	return r;
}

ListeReservation ajouterReservation(ListeReservation lr, Reservation r)
{
	if(lr == NULL)
	{
		return ajouterEnTete(lr, r);
	}
	if(strcmp(lr->res.idReservation, r.idReservation) == 0)
	{
		printf("entier déjà existant\n");
		return lr;
	}
	if(strcmp(lr->res.idReservation, r.idReservation) > 0)
	{
		return ajouterEnTete(lr, r);
	}
	lr->suivant=ajouterReservation(lr->suivant, r);
	return lr;
}

void AfficherListeReservation(ListeReservation lr, Adherent *tAdherent[], int nbAdherent, Jeux* tJeux[], int nbJeux)	// A COMPLETER
{
	int i,j;
	if (lr==NULL)
	{
		return;
	}

	i=chercherAdherent(lr->res.idAdherent,tAdherent,nbAdherent);
	if (i == -1)
	{
		return;
	}
	j=chercherJeux(lr->res.idJeu,tJeux,nbJeux);
	if (j == -1)
	{
		return;
	}
	printf("ID RESERVATION : %s\n",lr->res.idReservation);
	printf("IDENTITÉ : %s\n",tAdherent[i]->nomAdherent);
	printf("NOM DU JEU : %s\n",tJeux[j]->nomJeu);
	printf("DATE RESERVATION : ");
	affichageDate(lr->res.dateReservation);
	printf("\n\n\n");
	AfficherListeReservation(lr->suivant,tAdherent,nbAdherent,tJeux,nbJeux);
}

void sauvegardeBinaireReservation(ListeReservation lr)
{
	FILE *flot;
	flot=fopen("reservations.bin", "wb");
	if(flot == NULL)
	{
		printf("pb d'ouveture de fichier de sauvegarde\n");
		return;
	}
	while(!(lr == NULL))
	{
		fwrite(lr, sizeof(Reservation), 1, flot);
		lr=lr->suivant;
	}
	fclose(flot);
}

ListeReservation chargementBinairetReservations(void)
{
	ListeReservation lr;
	Reservation r;
	FILE *flot;
	flot = fopen("reservations.bin","rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return NULL;
	}
	lr=reservationVide();
	fread(&r, sizeof(Reservation), 1, flot);
	while(!feof(flot))
	{
		lr=ajouterReservation(lr, r);
		fread(&r, sizeof(Reservation), 1, flot);
	}
	fclose (flot);
	return lr;
}

ListeReservation supprimerEnTeteUneReservation(ListeReservation lr)
{
	ListeReservation svt;
	svt= lr->suivant;
	free(lr);
	return svt;
}

ListeReservation supprimerUneReservation(ListeReservation lr, Reservation r)
{
	if(lr==NULL)
	{
		return lr;
	}
	if(strcmp(lr->res.idReservation, r.idReservation) == 0)
	{
		return supprimerEnTeteUneReservation(lr);
	}
	if(strcmp(lr->res.idReservation, r.idReservation) > 0)
	{
		return lr;
	}
	lr->suivant=supprimerUneReservation(lr->suivant, r);
	return lr;
}

ListeReservation rechercheReservation(ListeReservation lr,char idJeu[])
{
	if (lr==NULL)
	{
		return lr;
	}
	if (strcmp(lr->res.idJeu,idJeu)==0)
		{
			return lr;
		}
	lr->suivant=rechercheReservation(lr->suivant,idJeu);
	return lr;
			
}

					//chercher Réservation
			



//----------------------------- MENU -------------------------------------------	

/*







void afficherMenuType(void)
{
	printf("------------------------------------------------------------------\n\n");
	printf("| \t1\t Construction\n");
	printf("| \t2\t Plateau\n");
	printf("| \t3\t Tuile\n");
	printf("| \t4\t Carte\n");
	printf("| \t5\t Logique\n\n");
	printf("| \t6\t Retour\n\n");
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
			printf("choix 1\n");
			//return;
		if(choix==2)
			printf("choix 2\n");
			//return;
		if (choix==3)
			printf("choix 3\n");
			//return;
		if(choix==4)
			printf("choix 4\n");
			//return;
		if (choix==5)
			printf("choix 5\n");
			//return;
		
	}
	return;
}

void afficherSousMenuJeux(void)
{
	printf("------------------------------------------------------------------\n\n");
	printf("| \t1\t Trié par type\n");
	printf("| \t2\t Tout voir\n");
	printf("| \t3\t Retour\n");
	printf("------------------------------------------------------------------\n");
}

int choixSousMenuJeux(void)
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

*/

void menuGlobal(void) // MODIF
{
	int choix;
	Jeux **tJeux;
	Adherent **tAdherent;
	int taillemax,nbJeux,nbAdherent;
	
	nbJeux=chargerJeux("jeux.don",tJeux);
	if (tailleJeu==-1)
	{
		return;
	}
	//restaureJeux
	nbAdherent=chargerAdherents("adherents.don",tAdherent);
	if (nbmat==-1)
	{
		return;
	}
	//restaureAhderent

	choix=choixMenuGlobal();
	
	
	while (choix != 7)
	{
		if (choix==1)
		{
			afficherTmat(tmat,nbmat);
		}
		else 
			if (choix == 2)
			{
				printf("Code de la matière à saisir : ");
				scanf("%s",code);
		
				i=rechmat(code,tmat,nbmat);
				if(i==-1)
					printf("La matière recherchée n'est pas enregistrée\n");
				else
					printf("La matière recherchée se situe en postion %d\n",i);
		
			}
			else 
				if (choix == 3)
				{
					nbmat=supMat(tmat,nbmat);
						if (nbmat == -1)
						{
							return;
						}
				}

				else 
					if (choix == 4)
					{

						nbmat=ajoutMat(tmat,nbmat,TMAX);
						if (nbmat == -2)
						{
							printf("Tableau plein !\n");
							return;

						}

						
					}

					else
						if (choix == 5)	
						{
							modifMat(tmat,nbmat);

						}
		printf("\n\nTapez sur la touche entrée pour revenir au menu ..\n");				
		c=getchar();			
		choix=choixMenu();
	}

}


void afficheMenuGlobal(void)
{
	system("clear");

	printf("\t\t\t\t____________________________________________________________________\n");
	printf("\t\n");
	printf("\t\t\t\t\t\t 1\tAfficher les jeux\n");
	printf("\t\t\t\t\t\t 2\tEmprunter un jeux\n");
	printf("\t\t\t\t\t\t 3\tAnnulation d'une réservation\n");
	printf("\t\t\t\t\t\t 4\tAfficher les emprunts\n");
	printf("\t\t\t\t\t\t 5\tAfficher les réservations\n");
	printf("\t\t\t\t\t\t 6\tFonction Administrateur\n");
	printf("\t\t\t\n");
	printf("\t\t\t\t\t\t 7\tQuitter\n");
	printf("\t\t\t\t____________________________________________________________________\n");

}

int choixMenuGlobal(void)
{
	int choix;
	char c;
	afficheMenuGlobal();
	printf("\n\t\t\t\t\t\t\tVotre choix : ");
	scanf("%d%*c",&choix);
	while(choix<1 || choix>6)
	{
		printf("\n\nChoix incorrect");
		printf("\n\n\n\nTapez sur la touche entrée pour revenir au menu ..\n");
		c=getchar();
		afficheMenuGlobal();
		printf("\n\t\t\t\t\t\tVotre choix : ");
		scanf("%d%*c",&choix);
	}
	return choix;
}


