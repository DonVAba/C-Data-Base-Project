#include <stdio.h>
#include <string.h>
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
       char nomJeu[40];
       char typeJeu[25];
       int nbExJeu;
}Jeu;


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

int chargerJeux(char* fileName, Jeu* tJeux[], int maxsize);
void affichageListeJeux(Jeu* tJeux[]);
Jeu lireJeu(FILE *flot);
void affichageJeux(int size, Jeu *tJeux[]);

int chargerAdherents(char* fileName, Adherent* tAdherent[], int maxsize);

int chargerEmprunt(char* fileName, Emprunt* tEmprunt[], int maxsize);
Emprunt lireEmprunt(FILE *flot);

int chargerReservation(char* fileName, Reservation* tReservation[], int maxsize);
Reservation lireReservation(FILE *flot);
void affichageReservation(Reservation r);

void sauvegardeTjeux(Jeu *tJeux[], int nbJeux);
void restaureTJeux(Jeu *tJeux[], int *nbJeux);











