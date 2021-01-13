#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"projet.h"





//---------------------- DATE ------------------------------------------------


/*Reçoit un fichier déjà ouvert
	Lit une le jour,le mois et l’année d’une Date sur le fichier FLOT
	Retourne cette Date*/


Date lireDate(FILE *flot)
{
    Date d;
    fscanf(flot,"%d/%d/%d%*c",&d.jour,&d.mois,&d.annee);
 
	return d;
}

/*Reçoit une date
	Écrit cette date au format JJ/MM/AAAA*/

void affichageDate(Date d)
{
	printf("%d/%d/%d",d.jour,d.mois,d.annee);
}

/*Demande à l’utilisateur d’écrire le jour,le mois et l’année d’une date (souvent la date du jour)
	Retourne cette Date
	// Peut-être remplacée par la fonction current_date à certains moments*/

Date ecrireDate(void)
{
    Date d;
    printf("\n\tÉcrire le jour(1-31)\n\t");
    scanf("%d%*c",&d.jour);
    while (d.jour<1 || d.jour>31)
    {
    	printf("\n\tErreur, ecrire correctement le jour(1-31)\n");
    	scanf("%d%*c", &d.jour);
    }


    printf("\n\tÉcrire le mois(1-12)\n\t");
    scanf("%d%*c", &d.mois);
    while (d.mois<1 || d.mois>12)
    {
    	printf("\n\tErreur, écrire correctement le mois(1-12)\n\t");
    	scanf("%d%*c", &d.mois);
    }

    printf("\n\tEcrire l'annee(2020-20XX)\n\t");
    scanf("%d%*c", &d.annee);
    while (d.annee<2020)
    {
    	printf("\n\tErreur, écrire correctement l'année(2020-20XX)\n\t");
    	scanf("%d%*c", &d.annee);
    }
 
	return d;
}

/*Reçois 2 dates
	Compare l’année de ces 2 dates
	Si elles sont égales compare leur mois
	S’ils sont égaux compare leur jour
	Retourne l'indice de la date la plus récente*/


int plusRecenteDate(Date d1,Date d2)
{
	if (d1.annee>d2.annee)
	{
		return 2;
	}
	if (d2.annee>d1.annee)
	{
		return 1;
	}
	if (d1.mois>d2.mois)		
	{
		return 2;
	}
	if (d2.mois>d1.mois)
	{
		return 1;
	}
	if (d1.jour>d2.jour)		
	{
		return 2;
	}
	if (d2.jour>d1.jour)
	{
		return 1;
	}
		return 1;	

}	




//---------------------- JEUX ------------------------------------------------



/*Reçois un nom de fichier et le tableau de pointeur déclaré mais vide
	Ouvre un fichier flot
	Lit le nombre de jeux écrit dans la première ligne du fichier
	Lit un jeu à partir d’un fichier
	Alloue ce même nombre lu ci-dessus,d’espace pour les pointeurs
	Rempli la valeur des pointeurs avec les jeux lus*/


void chargerJeux(char* fileName, Jeux *tJeux[]) // Loading the game's file

{
	FILE *flot;
	Jeux j;
	int i, nbJeux;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("\n\tErreur : le fichier %s ne peut pas etre ouvert !\n",fileName);
		return;
	}
	fscanf(flot,"%d%*c", &nbJeux);
	//tJeux=malloc(*nbJeux*sizeof(Jeux));
	j=lireJeu(flot);
	for (i = 0; !feof(flot); i++)
	{
		
		tJeux[i]=(Jeux*) malloc(sizeof(Jeux));
		if (tJeux[i]==NULL)
		{
			printf("\n\tErreur : Problème durant l'allocation mémoire !\n");
			fclose(flot);
			return;
		}
		*tJeux[i]=j;
		j=lireJeu(flot);
	}
	fclose(flot);
}

/*Reçoit un nomFichier
	Lit le nombre de jeux
	Retourne le nombre de jeux*/

int tailleTableau(char nomFichier[20])
{
	int tailleTableau;
	FILE *flot;
	flot = fopen(nomFichier,"r");
	if (flot == NULL)
	{
		printf("\n\tErreur : le fichier %s ne peut pas etre ouvert\n", nomFichier);
		return -1;
	}
	fscanf(flot, "%d%*c", &tailleTableau);
	fclose (flot);
	return tailleTableau;
}

/*Reçois le tableau de pointeur
	Ouvre le fichier binaire dans lequel le tableau de pointeur a été sauvegardé
	Rempli le tableau
	Ferme le fichier*/

void chargementBinaireTJeux(Jeux **tJeux)
{
	int i, nbJeux;
	Jeux j;
	FILE *flot;
	flot = fopen("jeux.bin","rb");
	if (flot == NULL)
	{
		printf("\n\tErreur : le fichier binaire ne peut pas etre ouvert\n");
		return;
	}
	fscanf(flot, "%d%*c", &nbJeux);
	fread(&j, sizeof(Jeux), 1, flot);
	for (i=0; i<nbJeux; i++)
	{
		tJeux[i]=(Jeux *) malloc(sizeof(Jeux));
		if (tJeux[i]==NULL)
		{
			printf("\n\tErreur : Problème durant l'allocation mémoire !\n");
			fclose(flot);
			return;
		}
		*tJeux[i]=j;
		fread(&j, sizeof(Jeux), 1, flot);
	}
	fclose (flot);
}

/*Reçois un fichier déjà ouvert
	Lit un ID de jeu,un type de jeu, un nombre d’exemplaire disponibles et un nom
	Retourne un jeu*/

Jeux lireJeu(FILE *flot)
{
	Jeux j;
	fscanf(flot,"%s%*c",j.idJeu);
	fscanf(flot,"%s%*c",j.typeJeu);
	fscanf(flot,"%d%*c",&j.nbExJeu);
	fgets(j.nomJeu,40,flot);
	j.nomJeu[strlen(j.nomJeu)-1]='\0';
	return j;
}

/*Reçois le tableau de pointeur et le nombre de jeux
	Demande l’ID du jeu
	Cherche cet ID dans le tableau
	Retourne -1 s’il n’existe pas
	Sinon supprime le pointeur sur le jeu
	Retourne le nouveau nombre de jeux*/


int supprimerJeux(Jeux* tJeux[], int nbJeux)
{
	int rang, i;
	char idJeu[10];
	printf("\n\tSaisir l'ID du jeu à supprimer : ");
	scanf("%s%*c", idJeu);
	rang=chercherJeux(idJeu,tJeux,nbJeux);
	
	if (rang==-1)
	{
		printf("\n\tLe jeu n'existe pas !\n");
		return nbJeux;
	}
	free(tJeux[rang]);
	for (i = rang; i < nbJeux-1; i++)
	{
		tJeux[i]=tJeux[i+1];
	}
	return nbJeux-1;
}

/*Reçois un ID Jeu, le tableau de pointeur et le nombre de jeu
	Tant que on a pas examiné le dernier ID Jeu
		Si l’ID correspond on retourne le rang
	Si on ne trouve pas l’ID on retourne -1*/

int chercherJeux(char idJeu[], Jeux *tJeux[], int nbJeux)
{
	int i;
	for(i=0 ; i < nbJeux ; i++)
		{	
			if(strcmp(idJeu, tJeux[i]->idJeu)==0)
				return i;
		}
		
	return -1;
}

/*Reçois le tableau de pointeur et le nombre de jeux
	Écrit chaque jeu un par un*/

void affichageTousJeux(Jeux* tJeux[],int GameSize)
{
	int i;
	printf("\t\tID\t\tCatég.\t\tExemplaires\t\tTitre\n\n");
	for (i = 0; i < GameSize ; i++)
	{
		printf("\t\t%s\t\t%s\t\t%d\t\t\t%s\n",tJeux[i]->idJeu,tJeux[i]->typeJeu,tJeux[i]->nbExJeu,tJeux[i]->nomJeu);
	}
}

/*Reçois le tableau de pointeur, le nombre de jeux et un type déclaré avant l’appel de cette 	fonction
	Déclare un tableau de pointeur temporaire
	Rempli ce tableau de tous les jeux ayant le type de l’appel et un nombre d’exemplaire supérieur 	à 0
	Appelle la fonction triJeux
	Affiche le tableau temporaire trié
	Libère les espaces alloués pour ce tableau temporaires
*/


void affichageListeJeuxDisponibles(Jeux* tJeux[],int size,char type[]) 		// LISTES possible si jamais
{
	int i,j=0;
	Jeux *temp[40];
	printf("\n\t\tJeux disponibles pour la catégorie : %s\n\n", type);
	for (i = 0; i < size ; i++)
	{

		if (strcmp(tJeux[i]->typeJeu,type)==0)
		{
			if (tJeux[i]->nbExJeu > 0)
			{
				temp[j]=(Jeux *) malloc(sizeof(Jeux));
				if (temp[j]==NULL)
				{
					printf("\n\tErreur pendant l'allocation mémoire !\n");
					return ;
				}
				*temp[j]=*tJeux[i];
				j=j+1;
			}
		}
	}
	if (j==0)
	{
		printf("\n\t\tPas de jeux disponibles!\n");
		return;

	}

	triJeux(temp,j); 
	printf("\t\tID\tExemplaires\t\tTitre\n\n");
	for (i = 0; i < j; i++)
	{
		printf("\t\t%s\t%d\t\t\t%s\n",temp[i]->idJeu,temp[i]->nbExJeu,temp[i]->nomJeu);
	}
		
	for (i = 0; i < j; i++)
		free(temp[i]);
	

}

/*Reçois un tableau de pointeur temporaire et la taille de ce tableau
	Tant qu’on est pas au dernier, appel la fonction rechercheRMin et la fonction permutation*/

void triJeux(Jeux *TempJeux[],int size)
{
	int k,rmin;

	for (k = 0; k < size-1; k++)
	{
		rmin=RechercheRMin(TempJeux,k,size);
		permutation(TempJeux,k,rmin);
	}
}

/*Reçois un tableau de pointeur et de variable qui n’ont pas encore de valeur
	Compare chaque élément du tableau
	Retourne le rang de l’élément le plus petit*/

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

/*Reçois le tableau de pointeur temporaire et deux rangs
	Permutent les deux éléments du tableaux appartenant aux rangs*/	


void permutation(Jeux *TempJ[],int i,int j)
{
	Jeux permutation;

	permutation=*TempJ[i];
	*TempJ[i]=*TempJ[j];
	*TempJ[j]=permutation;
}

/*Reçois le tableau de pointeur Jeux, la liste des emprunts, la liste des réservations et le nombre 	de jeux
	Demande l’ID de l’emprunt afin d’effectuer le retour
	Cherche l’emprunt pour voir s’il existe
	Supprime cet emprunt
	Recherche s’il y a une réservation pour le jeu emprunté
	Si oui crée un emprunt à partir de cette réservation sinon ajoute 1 aux nombres d’exemplaires du jeu*/

void retourJeux(Jeux *tJeux[],ListeEmprunt *le, ListeReservation *lr,int nbJeux, Adherent *tAdherent[], int nbAdherent) 
{	
	int i, retourRechEmp, retourRechRes, compteur=0;
	Reservation r;
	Emprunt e;
	Date d;
	char idEmprunt[30],tempIdJeu[20], temp[2];

	printf("\nVoici la liste des Emprunts : ");
	AfficherListeEmprunt(*le, tAdherent, nbAdherent, tJeux, nbJeux);
	printf("Saisir l'ID de votre emprunt : ");
	scanf("%s%*c",idEmprunt);
	retourRechEmp=chercherEmprunt(*le, idEmprunt, &e);
	if (retourRechEmp==-1)
	{
		printf("\nErreur : L'emprunt %s n'existe pas !\n",idEmprunt);
		return;
	}
	strcpy(tempIdJeu, e.idJeu);
	*le=supprimerEmprunt(*le, e);
	retourRechRes=rechercheReservation(*lr, tempIdJeu, &r);
	if (retourRechRes==-1)
	{
		i=chercherJeux((*le)->e.idJeu,tJeux,nbJeux);
		tJeux[i]->nbExJeu=tJeux[i]->nbExJeu+1;
		return;
	}
	else
	{	
		d=ecrireDate();
		e=creationEmprunt(r.idJeu, r.idAdherent, d);
		compteur=compteLesEmpruntsAvecLesMemesInfos(*le, e, compteur);
		if (compteur>0)
		{
			sprintf(temp, "%d", compteur);
			strcat(e.idEmprunt, temp);
		}
		*le=ajouterEmprunt(*le, e);
		*lr=supprimerUneReservation(*lr, r);
	}	
}

/*Reçois le tableau de pointeur et le nombre de jeux
	Créer un jeu
	Ajoute ce jeu dans le tableaux
	Retourne le nouveau nombre de jeux*/

int ajouterJeux(Jeux *tJeux[], int nbJeux)
{
	Jeux j;
	int i,rang;
	j=creerJeux(tJeux,nbJeux,&rang);
	if(rang==-1)
	{	
		/*
		for (i = nbJeux-1; i > rang; i--)
		{
			tJeux[i+1]=tJeux[i];
		}*/
		*tJeux[nbJeux]=j;
		return nbJeux+1;
	}
	return nbJeux;	
}

/*
int ajouterJeuxBis(Jeux **tJeux[], int nbJeux)
{
	Jeux j , **temptJeux;
	int i,rang;
	j=creerJeux(*tJeux,nbJeux,&rang);
	if(rang==-1)
	{	
		nbJeux=nbJeux+1;
		temptJeux= realloc  (*tJeux, nbJeux*sizeof(Jeux));
		if (temptJeux==NULL)
		{
			printf("Probléme sur realloc.\n");
			return -1;
		}

		*tJeux=temptJeux;
		testreal(*tJeux, rang, nbJeux, j);
		return nbJeux;
	}
	return nbJeux;	
}*/
/*
void insertionJeu(Jeux **tJeux, int rang, int nbJeux, Jeux j)
{
	int i;
	tJeux[nbJeux-1]=(Jeux *) malloc(sizeof(Jeux));
	if (tJeux[nbJeux-1]==NULL)
	{
		printf("Erreur durant l'allocation!\n");
		return;
	}
	*tJeux[nbJeux-1]=j;
}*/


/*Reçois le tableau de pointeur, le nombre de jeux et un pointeur sur une variable
	Demande de rentrer un ID, un type ,un nombre d’exemplaire et un nom de jeu
	Lit les réponses
	Recherche le jeu
	Défini la valeur du pointeur par le rang d’insertion du jeu s’il n’existe déjà pas
	Retourne ce jeu*/

Jeux creerJeux(Jeux *tJeux[], int nbJeux,int *rang)
{

	Jeux j;
	
	char idJeu[10], nomJeu[25], typeJeu[25];
	printf("\n\tSaisir l'ID du jeu : ");
	scanf("%s%*c",j.idJeu);
	minuscule(j.idJeu);
	*rang=chercherJeux(j.idJeu,tJeux,nbJeux);
	if(*rang!=-1)
	{
		printf("\n\tLe jeu existe déjà\n");
		
	}
	else
	{	
		printf("\n\tSaisir le nom du jeu : ");
		fgets(j.nomJeu,25,stdin);
		j.nomJeu[strlen(j.nomJeu)-1]='\0';
		minuscule(j.nomJeu);

		printf("\n\tSaisir le type du jeu (construction, plateau, tuile, carte, logique) : ");
		scanf("%s%*c",j.typeJeu);
		minuscule(j.typeJeu);
		while((strcmp(j.typeJeu,"construction")!=0)&&(strcmp(j.typeJeu,"plateau")!=0)&&(strcmp(j.typeJeu,"tuile")!=0)&&(strcmp(j.typeJeu,"carte")!=0)&&(strcmp(j.typeJeu,"logique")!=0))
		{
			printf("\n\tErreur, veuillez saisir correctement le type (construction, plateau, tuile, carte, logique) : ");
			scanf("%s%*c",j.typeJeu);
		}
		printf("\n\tSaisir le nombre d'exemplaire :");
		scanf("%d%*c", &j.nbExJeu);
	}
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

/*Reçois le tableau de pointeur et le nombre de jeux
	Ouvre un fichier binaire
	Écrit les valeurs du tableau de pointeur sur le fichier
	Ferme le fichier*/

void sauvegardeTjeuxBinaire(Jeux *tJeux[], int nbJeux)
{
	FILE *flot;
	int i;
	flot=fopen("jeux.bin", "wb");
	if(flot == NULL)
	{
		printf("\n\tProbleme d'ouverture du fichier binaire\n");
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

/*Reçois le tableau de pointeur, et un pointeur sur le nombre de jeux
	Remet les valeurs sauvegardées sur le fichier dans le tableau
	Ferme le fichier*/

/*
Jeux** restaureTJeux(Jeux *tJeux[], int *nbJeux)
{
	FILE *flot;
	flot = fopen("jeux.bin", "rb");
	if (flot == NULL)
	{
		printf("pb d'ouverture du fichier binaire\n");
		return NULL;
	}
	fscanf(flot,"%d%*c",nbJeux);
	*tJeux=(Jeux*) malloc (*nbJeux*sizeof(Jeux));
	if (tJeux == NULL)
	{
		printf("pb sur malloc de tresult\n");
		*nbJeux = -1;
		fclose(flot);
		return NULL;
	}
	fread(*tJeux, sizeof(Jeux), *nbJeux, flot);
	fclose(flot);
	return tJeux;
}
*/

					

					


//---------------------- ADHERENTS ------------------------------------------------



/*Reçoit un nom de fichier, un tableau de pointeur sur des Adherents et un nombre d’adherent
	Ouvre un fichier portant le nom donné à l’appel de la fonction de chargement
	Lit les adhérents et alloue un espace pour chacun au fur et à mesure
	Ferme le fichier*/



void chargerAdherents(char* fileName, Adherent* tAdherent[]) // Loading the adherent's file

{
	FILE *flot;
	int nbAdherent;
	Adherent a;
	int i;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("\n\tErreur : le fichier %s ne peut pas etre ouvert !\n",fileName);
		return;
	}
	fscanf(flot,"%d%*c", &nbAdherent);
	a=lireAdherent(flot);
	for(i=0; i <  nbAdherent ; i++)
	{
		tAdherent[i]=(Adherent *) malloc(sizeof(Adherent));
		if (tAdherent[i]==NULL)
		{
			printf("\n\tErreur : probleme durant l'allocation mémoire !\n");
			fclose(flot);
			return;
		}
		*tAdherent[i]=a;
		a=lireAdherent(flot);

	}
	fclose(flot);
}

/*Reçois un tableau de pointeur temporaire et la taille de ce tableau
	Tant qu’on est pas au dernier, appel la fonction rechercheRMinA et la fonction permutationA*/

void triAdherent(Adherent *TempAdherent[],int size)
{
	int k,rmin;

	for (k = 0; k < size-1; k++)
	{
		rmin=RechercheRMinA(TempAdherent,k,size);
		permutationA(TempAdherent,k,rmin);
	}
}

/*Reçois un tableau de pointeur et de variable qui n’ont pas encore de valeur
	Compare chaque élément du tableau
	Retourne le rang de l’élément le plus petit*/

int RechercheRMinA(Adherent *TempA[],int i,int n)			
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

/*Reçois le tableau de pointeur temporaire et deux rangs
	Permutent les deux éléments du tableaux appartenant aux rangs*/

void permutationA(Adherent *TempA[],int i,int j)	
{
	Adherent permutation;

	permutation=*TempA[i];
	*TempA[i]=*TempA[j];
	*TempA[j]=permutation;
}

/*Reçois un fichier déjà ouvert
	Lit les données appartenant à la structure d’un adherent
	Retourne cet adhérent*/

Adherent lireAdherent(FILE *flot)
{
	Adherent a;
	fscanf(flot,"%s%*c",a.idAdherent);
	a.dateInscription=lireDate(flot);
	fscanf(flot,"%s%*c",a.civilite);
	fscanf(flot,"%s%*c",a.nomAdherent);
	fgets(a.prenomAdherent,25,flot);
	a.prenomAdherent[strlen(a.prenomAdherent)-1]='\0';
	return a;
}
					//Lire adherent

/*Reçois le tableau de pointeur adhérent et le nombre de jeux
	Demande les valeurs appartenant à la structure Adherent
	Lit ces valeurs
	Recherche si cet Adhérent existe déjà
	Si oui quitte la la fonction
	Sinon crée un ID Adhérent
	Retourne cet adhérent*/

Adherent creerAdherent(Adherent *tAdherent[],int nbAdherent, int *chercherAdh)
{

	Adherent a;
	char monsieur[3]="mr";
	char madame[4]="mme";
	char nom[15],prenom[15];
	printf("\n\tSaisir votre nom : ");
	scanf("%s%*c", a.nomAdherent);
	strcpy(nom,a.nomAdherent);
	minuscule(nom);
	printf("\n\tSaisir votre prénom : ");
	fgets(a.prenomAdherent,20,stdin);
	a.prenomAdherent[strlen(a.prenomAdherent)-1]='\0';
	strcpy(prenom,a.prenomAdherent);
	minuscule(prenom);
	creerNomUtil(prenom,nom,6,2,a.idAdherent);
	*chercherAdh=chercherAdherent(a.idAdherent,tAdherent,nbAdherent);
	if(*chercherAdh!=-1)
	{
		printf("\n\tL'adherent existe déjà\n");
		return a;
	}
	else
	{	
		printf("\n\tVoici votre ID : %s\n", a.idAdherent);
		printf("\n\tSaisir votre genre (Mme/Mr) : ");
		scanf("%s%*c",a.civilite);
		minuscule(a.civilite);
		while((strcmp(a.civilite,monsieur)!=0) && strcmp(a.civilite,madame)!=0)
		{	
			printf("\n\tErreur, veuillez saisir correctement votre genre (Mme/Mr) : 5");
			scanf("%s%*c", a.civilite);
			printf("%s\n",a.civilite);
		}
		a.dateInscription=ecrireDate();
		creerNomUtil(prenom,nom,6,2,a.idAdherent);
		return a;
	}	
}

/*Reçoit un ID adherent, le tableau de pointeur et le nombre d’adherent
	Cherche si l’adhérent avec l’ID reçu existe
	Si oui retourne -1
	Sinon retourne son rang d’insertion*/

int chercherAdherent(char idAdherent[],Adherent *tAdherent[],int nbAdherent)
{
	int i;
	for(i=0 ; i < nbAdherent ; i++)
		{
			if(strcmp(idAdherent, tAdherent[i]->idAdherent)==0)
			{	
				return i;
			}	
			
			if(strcmp(idAdherent, tAdherent[i]->prenomAdherent)<0)
				return -1;
		}
		
	return -1;
}

/*Reçois le tableau de pointeur Adhérent et le nombre d’adhérent
	Demande l’ID de l’adhérent qu’on veut supprimer
	Cherche si l’adhérent existe
	Si oui supprime cet adhérent et renvoie le nouveau nombre d’adhérent
	Sinon renvoie -1*/

int supprimerAdherent(Adherent *tAdherent[], int nbAdherent)
{
	int rang, i;
	char idAdherent[20];
	printf("\n\tSaisir l'ID de l'adherent à supprimer : ");
	scanf("%s%*c", idAdherent);
	rang=chercherAdherent(idAdherent,tAdherent,nbAdherent);
	
	if (rang==-1)
	{
		printf("\n\tL'adherent n'existe pas !\n");
		return nbAdherent;
	}
	free(tAdherent[rang]);
	for (i = rang; i < nbAdherent-1; i++)
	{
		tAdherent[i]=tAdherent[i+1];
	}
	return nbAdherent-1;
}

/*Reçois le tableau de pointeur adhérent et le nombre d’adhérent
	Ouvre un fichier où on va écrire
	Écrit les données des adhérents sur le fichier
	Ferme le fichier*/

void sauvegardeNormaleAdherent(Adherent *tAdherent[], int nbAdherent)
{
    FILE *flot;
    int i;
    flot = fopen("adherentsav.don", "w");
    if (flot == NULL)
    {
        printf("\n\tErreur : probleme d'ouverture du fichier !\n");
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
	char prenomBis[30]={};
	char nomBis[30]={};
	supprimeBlanc(prenom,prenom);
	supprimeBlanc(nom,nom);
	partieGauche(prenom,prenomBis,p);
	partieGauche(nom,nomBis,n);
	strcpy(IdUtil,strcat(prenomBis,nomBis));
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

/*Reçois le tableau de pointeur adhérent et le nombre d’adhérent
	Ouvre un fichier binaire où on va écrire
	Écrit les données des adhérents sur le fichier
	Ferme le fichier
	Libère l’espace alloué pour le tableau*/

void sauvegardeTAdherentBinaire(Adherent *tAdherents[], int nbAdherents)
{
	FILE *flot;
	int i;
	flot=fopen("adherents.bin", "wb");
	if(flot == NULL)
	{
		printf("\n\tErreur : Problème d'ouverture du fichier binaire\n");
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

/*Reçois le tableau de pointeur, et un pointeur sur le nombre d’adherent
	Remet les valeurs sauvegardées sur le fichier dans le tableau
	Ferme le fichier
	Retourne le tableau de pointeur*/

void chargementBinaireTAdherents(Adherent **tAdherent)
{
	int i, nbAdherent;
	Adherent a;
	FILE *flot;
	flot = fopen("adherents.bin","rb");
	if (flot == NULL)
	{
		printf("\n\tErreur : Problème d'ouverture du fichier binaire\n");
		return;
	}
	fscanf(flot, "%d%*c", &nbAdherent);
	fread(&a, sizeof(Adherent), 1, flot);
	for (i=0; i<nbAdherent; i++)
	{
		tAdherent[i]=(Adherent *) malloc(sizeof(Adherent));
		if (tAdherent[i]==NULL)
		{
			printf("\n\tErreur : Problème durant l'allocation mémoire !\n");
			fclose(flot);
			return;
		}
		*tAdherent[i]=a;
		fread(&a, sizeof(Adherent), 1, flot);
	}
	fclose (flot);
}






//---------------------- EMPRUNT ------------------------------------------------

/*Reçois un nom de fichier et la liste emprunt
	Ouvre le fichier
	Défini comme NULL le premier maillon de la liste
	Appelle la fonction mettreEnListe
	Ferme le fichier
	Retourne la liste*/

ListeEmprunt chargerListeEmprunt(char* fileName,ListeEmprunt le)
{
	FILE *flot;
	int i=0;

	flot=fopen(fileName,"r");
	if (flot==NULL)
	{
		printf("\n\tErreur: le fichier %s ne peut pas etre ouvert !\n",fileName);
		exit(1);
	}
	le=empruntvide();
	le=mettreEnListe(flot,le);
	fclose(flot);
	return le;
}

/*Reçois un fichier ouvert et la liste des emprunts
	Tant que le fichier n’est pas à sa fin on lit un emprunt
		et appelle de la fonction InsertTeteEmprunt
	Retourne la liste*/

ListeEmprunt mettreEnListe(FILE *flot,ListeEmprunt le)
{
	Emprunt e;
	le=empruntvide();
	e=lireEmprunt(flot);
	while (!feof(flot))
	{
		le=ajouterEmprunt(le,e);
		e=lireEmprunt(flot);
	}
	return le;
}

/*Reçois un fichier ouvert
	Lit les données d’un emprunt
	Retourne un emprunt*/

Emprunt lireEmprunt(FILE *flot)
{
    Emprunt e;
    fscanf(flot,"%s%s%s", e.idEmprunt,e.idAdherent, e.idJeu);
    e.dateEmprunt=lireDate(flot);
    return e;
}

/*Reçois un ID Jeu, un ID adherent et une date
	Crée un ID Emprunt
	Retourne l’emprunt*/	

Emprunt creationEmprunt(char idJeu[],char idAdherent[],Date d)
{
	Emprunt e;
	printf("%s\n", idJeu);
	printf("%s\n", idAdherent);
	
	char temp[3];
	char temp2[5];
	strcpy(e.idJeu,idJeu);
	strcpy(e.idAdherent,idAdherent);
	e.dateEmprunt=d;
	strcpy(e.idEmprunt, "E");
	strcat(e.idEmprunt, idJeu);
	sprintf(temp2, "%d", d.annee);
	strcat(e.idEmprunt, temp2);
	sprintf(temp, "%d", d.mois);
	strcat(e.idEmprunt, temp);
	sprintf(temp, "%d", d.jour);
	strcat(e.idEmprunt, temp);
	strcat(e.idEmprunt, idAdherent);
	printf("%s\n", e.idEmprunt);
	return e;
}

		
//Retourne NULL			

ListeEmprunt empruntvide(void)
{
	return NULL;
}

/*Reçois la liste d’emprunt et un emprunt
	Ajoute l’emprunt en fonction de sa date d’emprunt
	Retourne la liste*/

ListeEmprunt ajouterEmprunt(ListeEmprunt le,Emprunt em)
{

	int d;
	if (le==NULL)
	{
		return InsertionEnTete(le,em);
	}
	d=plusRecenteDate(le->e.dateEmprunt,em.dateEmprunt);
	if (d==2)
	{
		return InsertionEnTete(le,em);
	}
	le->suivant=ajouterEmprunt(le->suivant,em);
	return le;
}

/*Reçois la liste d’emprunt et un emprunt
	Insère l’emprunt
	Retourne la liste*/

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

/*Reçois la liste d’emprunt,le tableau de pointeur adherent, le nombre d’adherent,le tableau de 	pointeur de jeux et le nombre de jeux
	Cherche le rang de l’adhérent de l’emprunt
	Cherche le rang de l’adhérent du jeu
	Affiche l’emprunt
	Appelle la fonction AfficherListeEmprunt avec le maillon suivant*/

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
	printf("\n__________________________________________________\n\n");
	printf("ID EMPRUNT : %s\n",le->e.idEmprunt);
	printf("IDENTITÉ : %s ",tAdherent[i]->nomAdherent);
	printf("%s\n",tAdherent[i]->prenomAdherent);
	printf("NOM DU JEU : %s\n",tJeux[j]->nomJeu);
	printf("DATE EMPRUNT : ");
	affichageDate(le->e.dateEmprunt);
	printf("\n__________________________________________________");
	printf("\n\n");
	AfficherListeEmprunt(le->suivant,tAdherent,nbAdherent,tJeux,nbJeux);

}
/*
ListeEmprunt chercherEmprunt(ListeEmprunt le,char idEmprunt[])
{
	if (le==NULL)
	{
		return NULL;
	}
	if (strcmp(le->e.idEmprunt, idEmprunt)==0)
			return le;
	else
	{
			le->suivant=chercherEmprunt(le->suivant,idEmprunt);
	}
}
*/

/*Reçois la liste d’emprunt et un ID Emprunt
	Cherche en fonction de l’ID et retourne 0 si trouvée
	Sinon retourne -1*/

int chercherEmprunt(ListeEmprunt le,char idEmprunt[], Emprunt *e)
{
	while(le!=NULL)
	{
		if (strcmp(le->e.idEmprunt, idEmprunt)==0)
		{
			*e=le->e;
			return 0;
		}
		else
			le=le->suivant;		
	}
	return -1;	
}

/*Reçois la liste d’emprunt et un ID emprunt
	Si l’ID est le même appel de la fonction supprimerEnTeteEmprunt
	Sinon appelle la fonction supprimerEmprunt avec le maillon suivant
	Retourne la liste*/

ListeEmprunt supprimerEmprunt(ListeEmprunt le, Emprunt e)
{
	if(le==NULL)
	{
		return le;
	}
	if(strcmp(le->e.idEmprunt, e.idEmprunt) == 0)
	{
		return supprimerEnTeteEmprunt(le);
	}
	le->suivant=supprimerEmprunt(le->suivant, e);
	return le;
}

/*Reçoit la liste d’emprunt
	Lie le maillon précédent avec le maillon suivant
	Libère l’espace de l’emprunt
	Retourne le maillon suivant*/

ListeEmprunt supprimerEnTeteEmprunt(ListeEmprunt le)
{
	ListeEmprunt svt;
	svt=le->suivant;
	free(le);
	return svt;
}

/*Reçoit les listes emprunt et réservations, les tableaux de pointeurs Jeux et Adherents, le nombre de jeux et le nomrbe d'adherent en pointeur
	Demande de saisir un ID adhérent
	Cherche le rang de l'adherent et redemande un ID si non trouvé et quitte la fonction si "exit" tapé
	Demande ensuite un ID de jeu
	Cherche le rang de ce jeu et redemande un ID si non trouvé et quitte la fonction si "exit" est tapé
	Appelle la fonction écrire Date
	Si le jeu n'est pas disponible, crée une réservation sinon crée un emprunt et annule l'emprunt si l'adhérent a 3 emprunts
	*/ 


void faireUnEmpruntouUneReservation(ListeEmprunt le, ListeReservation lr, Jeux* tJeux[], Adherent* tAdherent[], int nbJeux, int *nbAdherent)
{
	int rangJ, rangA, nbEmp=0, compteur=0, chercherAdh;
	Emprunt e;
	Reservation r;
	Date date;
	Adherent a;
	char idJeu[20], choix, idAdherent[20],idReservation[20], temp[2];

	printf("\n\tSaisir votre ID d'adherent (les deux premieres lettres de votre prenom suivi des six premieres lettres de votre nom : ");
	scanf("%s%*c", idAdherent);
	rangA=chercherAdherent(idAdherent, tAdherent, *nbAdherent);
	while(rangA==-1)
	{
		printf("L'adherent n'existe pas, retaper un ID valide, tapez 'exit' pour sortir, tapez 'nouveau' pour savoir comment créer un nouvel adherent\n");
		scanf("%s%*c", idAdherent);
		if (strcmp(idAdherent,"exit")==0)
			return;
		if (strcmp(idAdherent,"nouveau")==0)
		{
			printf("Rendez-vous dans le sous-menu Administrateur à partir du menu principal pour créer un nouvel adherent\n");
			printf("Tapez 'exit' pour retourner au menu principal.\n");
			scanf("%s%*c", idAdherent);
			if (strcmp(idAdherent,"exit")==0)
				return;
		}
		rangA=chercherAdherent(idAdherent, tAdherent, *nbAdherent);
	}
	
	printf("L'emprunt va etre réalisé pour l'adherent %s\n", idAdherent );
	printf("\n\tSaisir l'ID du jeu que vous voulez emprunter : ");
	scanf("%s%*c", idJeu);
	rangJ=chercherJeux(idJeu, tJeux, nbJeux);
	while(rangJ==-1)
	{
		printf("\n\tLe jeu n'existe pas, retaper un ID valide, tapez 'exit' pour sortir : ");
		scanf("%s%*c", idJeu);
		if (strcmp(idJeu,"exit")==0)
			return;
		rangJ=chercherJeux(idJeu,tJeux,nbJeux);
	}
	printf("\n\tL'emprunt ou la réservation va etre réalisé pour le jeu %s\n", idJeu);
	printf("\n\tSaisir la date d'aujourd'hui : \n");
	date=ecrireDate();
	if (tJeux[rangJ]->nbExJeu==0)
	{
		printf("\n\tLe jeu n'est pas disponible voulez vous le réserver ? (y/n)");
		scanf("%s%*c", &choix);
		if (choix == 'n')
			return;

		r=creationReservation(idJeu, idAdherent, date);
		compteur=compteLesReservationsAvecLesMemesInfos(lr, r, compteur);
		if (compteur>0)
		{
			printf("test\n");
			sprintf(temp, "%d", compteur);
			strcat(r.idReservation, temp);
		}
		lr=ajouterReservation(lr, r);
	}
	else
	{
		e=creationEmprunt(idJeu,idAdherent,date);
		nbEmp=compteEmprunt(le, e, nbEmp);
		if (nbEmp == 3)
		{
			printf("\n\tCet Adherent a déjà 3 emprunts en cours\n");
			return;
		}
		compteur=compteLesEmpruntsAvecLesMemesInfos(le, e, compteur);
		if (compteur>0)
		{
			sprintf(temp, "%d", compteur);
			strcat(e.idEmprunt, temp);
		}
		affichageDate(e.dateEmprunt);
		printf("\n\n");
		le=ajouterEmprunt(le,e);
		tJeux[rangJ]->nbExJeu=tJeux[rangJ]->nbExJeu-1;
	}
	return;
}

/*Reçois la liste d’emprunt, un emprunt et un entier
	Si l’ID emprunt du maillon est le même que celui de l’emprunt incrémente i de 
	Appelle la fonction compteEmprunt avec le maillon suivant
	Retourne i à la fin de la liste*/

int compteLesEmpruntsAvecLesMemesInfos(ListeEmprunt le, Emprunt emp, int i)
{
	if(le==NULL)
	{
		return i;
	}
	if(strcmp(le->e.idAdherent, emp.idAdherent)== 0 && strcmp(le->e.idJeu, emp.idJeu)==0 
		&& le->e.dateEmprunt.jour==emp.dateEmprunt.jour && le->e.dateEmprunt.mois==emp.dateEmprunt.mois 
		&& le->e.dateEmprunt.annee==emp.dateEmprunt.annee)
	{
		i++;
	}
	i=compteLesEmpruntsAvecLesMemesInfos(le->suivant, emp, i);
	return i;
}

int compteEmprunt(ListeEmprunt le, Emprunt emp, int i)
{
	if(le==NULL)
	{
		return i;
	}
	if(strcmp(le->e.idAdherent, emp.idAdherent)== 0)
	{
		i++;
	}
	i=compteEmprunt(le->suivant, emp, i);
	return i;

}

/*Reçois la liste d’emprunt
	Ouvre le fichier binaire
	Écrit la liste sur un fichier binaire
	Libère l’espace pour la liste
	Ferme le fichier*/

void sauvegardeBinaireEmprunts(ListeEmprunt le)
{
	FILE *flot;
	flot=fopen("emprunts.bin", "wb");
	if(flot == NULL)
	{
		printf("\n\tErreur : probleme d'ouverture du fichier binaire !\n");
		return;
	}
	while(!(le == NULL))
	{
		fwrite(le, sizeof(Emprunt), 1, flot);
		le=le->suivant;
	}
	fclose(flot);
}

/*Ouvre un fichier binaire
	Remet dans la liste d’emprunt les données
	Ferme le fichier
	Retourne la liste*/

ListeEmprunt chargementBinairetEmrunts(void)
{
	ListeEmprunt le;
	Emprunt e;
	FILE *flot;
	flot = fopen("emprunts.bin","rb");
	if (flot == NULL)
	{
		printf("\n\tErreur : probleme d'ouverture du fichier binaire !\n");
		return NULL;
	}
	le=empruntvide();
	fread(&e, sizeof(Emprunt), 1, flot);
	while(!feof(flot))
	{
		le=ajouterEmprunt(le, e);
		fread(&e, sizeof(Emprunt), 1, flot);
	}
	fclose (flot);
	return le;
}




//---------------------- Reservation ------------------------------------------------







//Retourne NULL



ListeReservation reservationVide(void)
{
	return NULL;
}

/*Reçois une liste de réservation et une réservation
	Insère la réservation
	Retourne la liste */

ListeReservation ajouterEnTete(ListeReservation lr, Reservation r)
{
	MaillonR *a;
	a=(MaillonR*)malloc(sizeof(MaillonR));
	a->res = r;
	a->suivant=lr;
	return a;
}

/*Reçois une liste de réservations
	Ouvre un fichier
	Tant que la fin du fichier n’est pas atteinte :
		Ajoute une réservation
		Lit une réservation
	Retourne la liste*/

ListeReservation CreationDeLaListe(ListeReservation lr)
{
	Reservation r;
	FILE *flot;
	flot=fopen("reservations2.don", "r");
	lr=reservationVide();
	r=lireReservation(flot);
	while(!feof(flot))
	{
		lr=ajouterReservation(lr, r);
		r=lireReservation(flot);
	}
	return lr;
}

/*Reçoit un fichier déjà ouvert
	Lit les données d’une réservation
	Retourne la réservation*/

Reservation lireReservation(FILE *flot)
{
	Reservation r;
	fscanf(flot, "%s%s%s", r.idReservation, r.idAdherent, r.idJeu);
	r.dateReservation=lireDate(flot);
	return r;
}

/*Reçoit un ID Jeu, un ID adhérent et une date de réservation
	Met une réservation les valeurs
	Crée un ID réservation
	Retourne la réservation*/

Reservation creationReservation(char idJeu[20], char idAdherent[20],Date dateReservation)
{
	Reservation r;
	char temp[3];
	char temp2[5];
	r.dateReservation.jour=dateReservation.jour;
	r.dateReservation.mois=dateReservation.mois;
	r.dateReservation.annee=dateReservation.annee;
	strcpy(r.idJeu, idJeu);
	strcpy(r.idAdherent, idAdherent);
	strcpy(r.idReservation, "R");
	strcat(r.idReservation, idJeu);
	sprintf(temp2, "%d", r.dateReservation.annee);
	strcat(r.idReservation, temp2);
	sprintf(temp, "%d", r.dateReservation.mois);
	strcat(r.idReservation, temp);
	sprintf(temp, "%d", r.dateReservation.jour);
	strcat(r.idReservation, temp);
	strcat(r.idReservation, r.idAdherent);
	return r;
}

/*Reçois la liste de réservation et une réservation
	Insère la réservation en fonction de sa date (1ère = plus récente)
	Retourne la liste*/

ListeReservation ajouterReservation(ListeReservation lr, Reservation r)
{
	int d;
	if (lr==NULL)
	{
		return ajouterEnTete(lr, r);
	}
	d=plusRecenteDate(lr->res.dateReservation,r.dateReservation);
	if (d==2)
	{
		return ajouterEnTete(lr,r);
	}
	lr->suivant=ajouterReservation(lr->suivant,r);
	return lr;
}

/*Reçois la liste de réservation,le tableau de pointeur adherent, le nombre d’adherent,le tableau de 	pointeur de jeux et le nombre de jeux
	Cherche le rang de l’adhérent de la réservation
	Cherche le rang de l’adhérent du jeu réservé
	Affiche la réservation
	Appelle la fonction AfficherListeRéservation avec le maillon suivant*/

void afficherListeReservation(ListeReservation lr, Adherent *tAdherent[], int nbAdherent, Jeux* tJeux[], int nbJeux)	// A COMPLETER
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
	printf("\n__________________________________________________\n\n");
	printf("ID RESERVATION : %s\n",lr->res.idReservation);
	printf("IDENTITÉ : %s\n",tAdherent[i]->nomAdherent);
	printf("NOM DU JEU : %s\n",tJeux[j]->nomJeu);
	printf("DATE RESERVATION : ");
	affichageDate(lr->res.dateReservation);
	printf("\n__________________________________________________");
	printf("\n\n\n");
	afficherListeReservation(lr->suivant,tAdherent,nbAdherent,tJeux,nbJeux);
}

/*Reçois la liste de réservation,le tableau de pointeur adherent, le nombre d’adherent,le tableau de pointeur de jeux et le nombre de jeux
	Ecrit et li un ID jeu
	Cherche le rang de l’adhérent de la réservation
	Cherche le rang de l’adhérent du jeu réservé
	Affiche la réservation
	Appelle la fonction AfficherListeRéservation avec le maillon suivant*/

void afficherListeReservationPourUnJeuDonne(ListeReservation lr, Adherent *tAdherent[], int nbAdherent, Jeux* tJeux[], int nbJeux)
{
	int i, j, compteur=0;
	char idJeu[20];
	printf("Saisir l'id du jeu dont vous voulez voir les réservations :");
	scanf("%s%*c", idJeu);
	while (lr!=NULL)
	{
		if (strcmp(lr->res.idJeu, idJeu)==0)
		{
			i=chercherAdherent(lr->res.idAdherent,tAdherent,nbAdherent);
			j=chercherJeux(lr->res.idJeu,tJeux,nbJeux);
			printf("\n__________________________________________________\n\n");
			printf("ID RESERVATION : %s\n",lr->res.idReservation);
			printf("IDENTITÉ : %s\n",tAdherent[i]->nomAdherent);
			printf("NOM DU JEU : %s\n",tJeux[j]->nomJeu);
			printf("DATE RESERVATION : ");
			affichageDate(lr->res.dateReservation);
			printf("\n__________________________________________________");
			printf("\n\n\n");
			compteur++;
		}		
		lr=lr->suivant;
	}
	if (compteur==0)
	{
		printf("Pas de reservation pour ce jeu\n");
	}
}	

/*
	Reçoit la liste des réservations , une chaine de caractère et un pointeur sur une réservation
	Retourne 0 si trouvé sinon -1
*/

int rechercheReservation(ListeReservation lr ,char idJeu[], Reservation *r)
{
	while (lr!=NULL)
	{
		if (strcmp(lr->res.idJeu, idJeu)==0)
		{
			*r=lr->res;
			return 0;
		}		
		lr=lr->suivant;
	}
	return -1;
}

int rechercheReservationBis(ListeReservation lr, Reservation r)
{
	while (lr!=NULL)
	{
		if (strcmp(lr->res.idReservation, r.idReservation)==0)
		{
			return 0;
		}		
		lr=lr->suivant;
	}
	return -1;
}

/*Reçois la liste de réservation
	Ouvre le fichier binaire
	Écrit la liste sur un fichier binaire
	Libère l’espace pour la liste
	Ferme le fichier*/

void sauvegardeBinaireReservation(ListeReservation lr)
{
	FILE *flot;
	flot=fopen("reservations.bin", "wb");
	if(flot == NULL)
	{
		printf("\n\tErreur : probleme d'ouverture du fichier binaire !\n");
		return;
	}
	while(!(lr == NULL))
	{
		fwrite(lr, sizeof(Reservation), 1, flot);
		lr=lr->suivant;
	}
	fclose(flot);
}

/*Ouvre un fichier binaire
	Remet dans la liste de réservation les données
	Ferme le fichier
	Retourne la liste*/

ListeReservation chargementBinairetReservations(void)
{
	ListeReservation lr;
	Reservation r;
	FILE *flot;
	flot = fopen("reservations.bin","rb");
	if (flot == NULL)
	{
		printf("\n\tErreur : probleme d'ouverture du fichier binaire !\n");
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

/*Reçoit la liste de réservation
	Lie le maillon précédent avec le maillon suivant
	Libère l’espace de la réservation
	Retourne le maillon suivant*/

ListeReservation supprimerEnTeteUneReservation(ListeReservation lr)
{
	ListeReservation svt;
	svt= lr->suivant;
	free(lr);
	return svt;
}

/*Reçois la liste d’emprunt et une réservation
	Si l’ID est le même appel de la fonction supprimerEnTeteEmprunt
	Sinon appelle la fonction supprimerUneRéservation avec le maillon suivant
	Retourne la liste
*/

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
	lr->suivant=supprimerUneReservation(lr->suivant, r);
	return lr;
}
/*
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
			
}*/

/*Reçoit la liste des emprunts
	Libère les espaces alloués pour cette liste*/
			
void freeListeEmprunt(ListeEmprunt le)
{
	MaillonE *suiv;
	suiv=(MaillonE*)malloc(sizeof(MaillonE));
	while(le!=NULL)
	{
		suiv->suivant=le->suivant;
		free(le);
		le=suiv->suivant;
	}
	free(suiv);
}

/*Reçoit la liste de réservation
	Libère les espaces alloués pour cette liste*/

void freeListeReservation(ListeReservation lr)
{
	MaillonR *suiv;
	suiv=(MaillonR*)malloc(sizeof(MaillonR));
	while(lr!=NULL)
	{
		suiv->suivant=lr->suivant;
		free(lr);
		lr=suiv->suivant;
	}
	free(suiv);
	return;
}

/*Reçoit une liste de réservation,une réservation et un entier
	Si les réservations sont les mêmes incrémente i
	Sinon appelle la fonction avec le maillon suivant
	retourne i
*/

int compteLesReservationsAvecLesMemesInfos(ListeReservation lr, Reservation r, int i)
{
	if(lr==NULL)
	{
		return i;
	}
	if(strcmp(lr->res.idAdherent, r.idAdherent)== 0 && strcmp(lr->res.idJeu, r.idJeu)==0 
		&& lr->res.dateReservation.jour==r.dateReservation.jour && lr->res.dateReservation.mois==r.dateReservation.mois 
		&& lr->res.dateReservation.annee==r.dateReservation.annee)
	{
		i++;
	}
	i=compteLesReservationsAvecLesMemesInfos(lr->suivant, r, i);
	return i;
}

//----------------------------- MENU -------------------------------------------	









void afficherMenuType(void)
{
	printf("\n\t____________________________________________________________________\n");
	printf("\t\n");
	printf("\t\t1\t Construction\n");
	printf("\t\t2\t Plateau\n");
	printf("\t\t3\t Tuile\n");
	printf("\t\t4\t Carte\n");
	printf("\t\t5\t Logique\n\n");
	printf("\t\t6\t Retour\n");
	printf("\t\t\t\n");
	printf("\t____________________________________________________________________\n");

}

int choixMenuType(void)
{
	int choix;
	afficherMenuType();
	printf("\n\tVotre choix : ");
	scanf("%d%*c", &choix);
	
	while(choix<1 || choix>6)
	{
		afficherMenuType();
		printf("\n\tErreur ! Veuillez saisir un choix valide : ");
		scanf("%d%*c", &choix);
		
	}
	return choix;

}



/*void MenuType(Jeux* tJeux[], int GameSize)//jai modifié les parametres
{
	int choix=choixMenuType();
	while(choix!=6)
	{
		if (choix==1)
			affichageListeJeuxDisponibles(tJeux,GameSize, "construction" );
			return;
		if(choix==2)
			affichageListeJeuxDisponibles(tJeux, GameSize, "plateau" );
			return;
		if (choix==3)
			affichageListeJeuxDisponibles(tJeux, GameSize, "tuile");
			return;
		if(choix==4)
			affichageListeJeuxDisponibles(tJeux, GameSize, "carte");
			return;
		if (choix==5)
			affichageListeJeuxDisponibles(tJeux, GameSize, "logique");
			return;
		
	}
	return;
}
*/
void afficherSousMenuJeux(void)
{
	printf("\t____________________________________________________________________\n");
	printf("\t\n");
	printf("\t\t1\t Trié par type\n");
	printf("\t\t2\t Tout voir\n\n");
	printf("\t\t3\t Retour\n");
	printf("\t\t\t\n");
	printf("\t____________________________________________________________________\n");
}

int choixSousMenuReservation(void)
{
	int choix;
	//system("clear");
	afficherSousMenuReservation();
	printf("\n\tVotre choix : ");
	scanf("%d%*c", &choix);
	
	while(choix<1 || choix>3)
	{
		//system("clear");
		afficherSousMenuReservation();
		printf("\n\tErreur ! Veuillez saisir un choix valide : ");
		scanf("%d%*c", &choix);

		
	}
	return choix;
}

void afficherSousMenuReservation(void)
{
	printf("\t____________________________________________________________________\n");
	printf("\t\n");
	printf("\t\t1\t Afficher la liste des reservations pour un jeu donné\n");
	printf("\t\t2\t Afficher la liste des reservations pour tous les jeux\n");
	printf("\t\t3\t Retour\n");
	printf("\t\t\t\n");
	printf("\t____________________________________________________________________\n");
}


void afficherSousMenuAdmin(void)
{
	printf("\t____________________________________________________________________\n");
	printf("\t\n");
	printf("\t\t1\t Créer un jeu\n");
	printf("\t\t2\t supprimer un jeu\n");
	printf("\t\t3\t Créer un Adherent\n");
	printf("\t\t4\t Supprimer un Adherent\n\n");
	printf("\t\t5\t Retour\n");
	printf("\t\t\t\n");
	printf("\t____________________________________________________________________\n");
}

int choixSousMenuAdmin(void)
{
	int choix;
	afficherSousMenuAdmin();
	printf("\n\tVotre choix : ");
	scanf("%d%*c", &choix);
	
	while(choix<1 || choix>5)
	{
		afficherSousMenuAdmin();
		printf("\n\tErreur ! Veuillez saisir un choix valide : ");
		scanf("%d%*c", &choix);

		
	}
	return choix;

}



int choixSousMenuJeux(void)
{
	int choix;
	afficherSousMenuJeux();
	printf("\n\tVotre choix : ");
	scanf("%d%*c", &choix);
	
	while(choix<1 || choix>3)
	{
		afficherSousMenuJeux();
		printf("\n\tErreur ! Veuillez saisir un choix valide : ");
		scanf("%d%*c", &choix);
		
	}
	return choix;

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void menuGlobal(void) // MODIF
{
	int choix, choixSousMenu, choixType, j, i, choixSousMenuA, chercherAdh, choixResa, nb;
	Jeux **tJeux, **temptJeux;
	Adherent **tAdherent, a, **temptAdherent;
	ListeEmprunt le;
	ListeReservation lr;
	Reservation r;
	int nbJeux,nbAdherent, retourRechercheRes;
	char c, idEmprunt[30];
	
	//chargement des fichiers 
	//nbJeux=tailleTableau("jeux.bin");//pour le chargement binaire
	nbJeux=tailleTableau("jeux.don");//pour le chargement classique
	printf("%d\n",nbJeux);
	tJeux=(Jeux**) malloc (nbJeux*sizeof(Jeux*));
	if(tJeux == NULL)
	{
		printf("Problème sur malloc\n");
		return;
	}
	chargementBinaireTJeux(tJeux);

	nbAdherent=tailleTableau("adherents.bin");
	//nbAdherent=tailleTableau("adherents.don");
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
	//chargerAdherents("adherents.don",tAdherent);
	chargementBinaireTAdherents(tAdherent);
	//triAdherent(tAdherent, nbAdherent);

	//le=chargerListeEmprunt("emprunts2.don", le);
	le=chargementBinairetEmrunts();
	//lr=CreationDeLaListe(lr);
	lr=chargementBinairetReservations();

	choix=choixMenuGlobal();
	
	
	while (choix!=8)
	{
		if (choix==1)
		{
			//system("clear");
			choixSousMenu=choixSousMenuJeux();//reaffiche sous menu jeux - choisir/lire - reaffiche/demande de reecrire - return choix 
			while(choixSousMenu!=3)//entrée dans le sous menu
			{
				//system("clear");
				if (choixSousMenu==1)
				{
					
					choixType=choixMenuType();//affiche menu type - choisir/lire - reaffiche demande reecrire - return choix
					while(choixType!=6)
					{
						if (choixType==1)
						{
							//system("clear");
							affichageListeJeuxDisponibles(tJeux,nbJeux, "construction" );
						}
						if(choixType==2)
						{
							//system("clear");
							affichageListeJeuxDisponibles(tJeux, nbJeux, "plateau" );
						}
					
						if (choixType==3)
						{
							//system("clear");
							affichageListeJeuxDisponibles(tJeux, nbJeux, "tuile");
						}
						
						if(choixType==4)
						{
							//system("clear");
							affichageListeJeuxDisponibles(tJeux, nbJeux, "carte");
						}
						
						if (choixType==5)
						{
							//system("clear");
							affichageListeJeuxDisponibles(tJeux, nbJeux, "logique");
						}
						
						choixType=choixMenuType();
					}	
				}
			
				if(choixSousMenu==2)
				{
				//system("clear");
				printf("%d\n", nbJeux);
				affichageTousJeux(tJeux, nbJeux);			
				}
				choixSousMenu=choixSousMenuJeux();
			}	
		}//sortie du sous menu
		if(choix==2)
		{
			//system("clear");
			printf("%d\n", nbAdherent);
			faireUnEmpruntouUneReservation(le, lr, tJeux, tAdherent, nbJeux, &nbAdherent);
			printf("%d\n", nbAdherent);
		}
		if (choix==3)
			{
				//system("clear");
				printf("Saisir l'id de la reservations\n");
				scanf("%s%*c", r.idReservation);
				retourRechercheRes=rechercheReservationBis(lr, r);
				if (retourRechercheRes==-1)
				{
					printf("\n\nLa réservation n'existe pas !\n");
				}
				else
				{
					lr=supprimerUneReservation(lr, r);
					printf("\n\nReservation annulée !\n");
				}
			}	
		if(choix==4)
		{
			//system("clear");
			AfficherListeEmprunt(le, tAdherent, nbAdherent, tJeux, nbJeux);
			printf("\n\nTapez sur la touche entrée pour revenir au menu ..\n");				
			c=getchar();
		}	
		if(choix==5)
		{
			choixResa=choixSousMenuReservation();
			while(choixResa!=3)
			{
				if (choixResa==1)
				{
					afficherListeReservationPourUnJeuDonne(lr, tAdherent, nbAdherent, tJeux, nbJeux);
					printf("\n\nTapez sur la touche entrée pour revenir au menu ..\n");				
					c=getchar();
				}
				if(choixResa==2)
				{
					afficherListeReservation(lr, tAdherent, nbAdherent, tJeux, nbJeux);
					printf("\n\nTapez sur la touche entrée pour revenir au menu ..\n");				
					c=getchar();
				}
				choixResa=choixSousMenuReservation();
			}
			printf("\n");
		}	
		if(choix == 6)
		{
			//system("clear");
			retourJeux(tJeux, &le, &lr, nbJeux, tAdherent, nbAdherent);
		}
		if (choix==7)
		{
			//system("clear");
			choixSousMenuA=choixSousMenuAdmin();//reaffiche sous menu jeux - choisir/lire - reaffiche/demande de reecrire - return choix 
			while(choixSousMenuA!=5)//entrée dans le sous menu
			{
				//system("clear");
				if (choixSousMenuA==1)
				{
					//system("clear");
					temptJeux=(Jeux**) realloc  (tJeux, (nbJeux+1)*sizeof(Jeux*));
					if (temptJeux==NULL)
					{
						printf("Probléme sur realloc.\n");
						return;
					}
					tJeux=temptJeux;
					tJeux[nbJeux]=(Jeux *) malloc(sizeof(Jeux));
					nbJeux=ajouterJeux(tJeux, nbJeux);
					printf("%d\n", nbJeux);
					//nbJeux=ajouterJeuxBis(&tJeux, nbJeux);
					//printf("%d\n", &tJeux);
					
				}
				if(choixSousMenuA==2)
				{
					//system("clear");
					nbJeux=supprimerJeux(tJeux, nbJeux);	
				}
				if(choixSousMenuA==3)
				{
					//system("clear");
					a=creerAdherent(tAdherent, nbAdherent, &chercherAdh);
					if (chercherAdh!=1)
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
						*tAdherent[nbAdherent-1]=a;
						triAdherent(tAdherent, nbAdherent);
					}
				}
				if(choixSousMenuA==4)
				{
					//system("clear");
					nbAdherent=supprimerAdherent(tAdherent, nbAdherent);
				}
				choixSousMenuA=choixSousMenuAdmin();
			}	
		}			
		choix=choixMenuGlobal();

	}
	//sauvegardeTAdherentBinaire(tAdherent, nbAdherent);
	//sauvegardeTjeuxBinaire(tJeux, nbJeux);
	//sauvegardeBinaireReservation(lr);
	//freeListeReservation(lr);
	//sauvegardeBinaireEmprunts(le);
	//freeListeEmprunt(le);

}


void afficheMenuGlobal(void)
{
	//system("clear");

	printf("\t____________________________________________________________________\n");
	printf("\t\n");
	printf("\t\t 1\tAffichage des jeux\n");//fonctionne
	printf("\t\t 2\tEmprunter un jeux (ou le réserver)\n");
	printf("\t\t 3\tAnnulation d'une réservation\n");
	printf("\t\t 4\tAfficher les emprunts\n");
	printf("\t\t 5\tAfficher les réservations\n");
	printf("\t\t 6\tRetour d'un jeu\n");
	printf("\t\t 7\tFonction Administrateur\n");
	printf("\t\t\t\n");
	printf("\t\t 8\tQuitter\n");
	printf("\t____________________________________________________________________\n");

}

int choixMenuGlobal(void)
{
	int choix;
	char c;

	afficheMenuGlobal();
	printf("\n\tVotre choix : ");
	scanf("%d%*c",&choix);
	while(choix<1 || choix>8)
	{
		printf("\n\nChoix incorrect");
		printf("\n\n\n\nTapez sur la touche entrée pour revenir au menu ..\n");
		c=getchar();
		afficheMenuGlobal();
		printf("\n\tVotre choix : ");
		scanf("%d%*c",&choix);
	}
	return choix;
}


