#include <stdio.h>
#include <stdlib.h>

// Définition des structures // Setting up structure

typedef struct 
{
	int jour;
	int mois;
	int annee;
}Date;


typedef struct 
{
       char idJeu[10];
       char nomJeu[25];
       char typeJeu[25];
       int nbExJeu;
}Jeux;


typedef struct 
{
	char idAdherent[20];
	char civilite[20];
	char nomAdherent[20];
	char prenomAdherent[20];
	Date dateInscription;  
}Adherent;


typedef struct
{
	char idEmprunt[20];
	char idAdherent[20];
	char idJeux[20];
	Date dateEmprunt;
}Emprunt;


typedef struct 
{
	char idReservation[20];
	char idAdherent[20];
	char idJeu[20];
	Date dateReservation;
}Reservation;


// Définitions des prototypes // Setting up prototypes fonction

Date lireDate(FILE *flot);
void affichageDate(Date d);
Date ecrireDate(void);

int chargerJeux(char* fileName, Jeux* tJeux[], int maxsize);
void affichageListeJeuxDisponibles(Jeux* tJeux[],int GameSize,char type[]);
Jeux lireJeu(FILE *flot);
void triJeux(Jeux *TempJeux[],int size);
int RechercheRMin(Jeux *TempJ[],int i,int n);
void permutation(Jeux *TempJ[],int i,int j)	;
void sauvegardeJEUXNormale(Jeux *tJeux[], int nbJeux);
void testTrijeux(void);

int chargerAdherents(char* fileName, Adherent* tAdherent[], int maxsize);
Adherent lireAdherent(FILE *flot);
Adherent creerAdherent(Adherent *tAdherent[], int nbAd);
int chercherAdherent(char*prenom, char*nom, Adherent*tAdherent[], int nbAd);
void testCreerAdherent(void);
void sauvegardeNormaleAdherent(Adherent *tAdherent[], int nbAdherent);
void creerNomUtil(char prenom[],char nom[],int n,int p,char IdUtil[]);


int chargerEmprunt(char* fileName, Emprunt* tEmprunt[], int maxsize);
Emprunt lireEmprunt(FILE *flot);

int chargerReservation(char* fileName, Reservation* tReservation[], int maxsize);
void affichageReservation(Reservation r);
Reservation lireReservation(FILE *flot);

void afficherMenuType(void);
int choixMenuType(void);
void MenuType(void);
void afficherSousMenuEmprunt(void);
int choixSousMenuEmprunt(void);
void sousMenuEmprunt(void);

int blanc(char c);
void partieGauche(char source[],char dest[],int p);
void supprimeBlanc(char source[],char dest[]);
void minuscule(char chaine[]);
