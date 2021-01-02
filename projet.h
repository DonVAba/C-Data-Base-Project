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
	char idAdherent[30];
	char civilite[20];
	char nomAdherent[20];
	char prenomAdherent[20];
	Date dateInscription;  
}Adherent;


typedef struct
{
	char idEmprunt[30];
	char idAdherent[20];
	char idJeu[20];
	Date dateEmprunt;
}Emprunt;

typedef struct listeE
{
	Emprunt e;
	struct listeE * suivant;
}MaillonE;

typedef MaillonE * ListeEmprunt;


typedef struct 
{
	char idReservation[20];
	char idAdherent[20];
	char idJeu[20];
	Date dateReservation;
}Reservation;

typedef struct listeR
{
	Reservation res;
	struct listeR * suivant;
}MaillonR;

typedef MaillonR * ListeReservation;

// Définitions des prototypes // Setting up prototypes fonction

Date lireDate(FILE *flot);
void affichageDate(Date d);
Date ecrireDate(void);
Date plusRecenteDate(Date d1,Date d2);

Jeux** chargerJeux(char* fileName, Jeux* tJeux[], int *nbJeux);
Jeux** chargementBinaireTJeux(Jeux **tJeux, int *nbJeux);
void affichageTousJeux(Jeux* tJeux[],int GameSize);
void affichageListeJeuxDisponibles(Jeux* tJeux[],int GameSize,char type[]);
Jeux lireJeu(FILE *flot);
int ajouterJeux(Jeux *tJeux[], int nbJeux);
int supprimerJeux(Jeux* tJeux[], int nbJeux);
int chercherJeux(char idJeu[], Jeux *tJeux[], int nbJeux);
void triJeux(Jeux *TempJeux[],int size);
int RechercheRMin(Jeux *TempJ[],int i,int n);
void permutation(Jeux *TempJ[],int i,int j)	;
void retourJeux(Jeux *tJeux[],ListeEmprunt le,ListeReservation lr,int nbJeux);
Jeux creerJeux(Jeux *tJeux[], int nbJeux,int *rang);
void sauvegardeJEUXNormale(Jeux *tJeux[], int nbJeux);
void sauvegardeTjeux(Jeux *tJeux[], int nbJeux);
void restaureTJeux(Jeux *tJeux[], int *nbJeux);
void testTrijeux(void);

Adherent** chargerAdherents(char* fileName, Adherent* tAdherent[], int *nbAdherent);
Adherent lireAdherent(FILE *flot);
void triAdherent(Adherent *TempAdherent[],int size);
int RechercheRMinA(Adherent *TempA[],int i,int n);
void permutationA(Adherent *TempA[],int i,int j);
Adherent creerAdherent(Adherent *tAdherent[],int nbAdherent);
int chercherAdherent(char idAdherent[],Adherent *tAdherent[],int nbAdherent);
void testCreerAdherent(void);
int supprimerAdherent(Adherent *tAdherent[], int nbAdherent);
void sauvegardeNormaleAdherent(Adherent *tAdherent[], int nbAdherent);
void creerNomUtil(char prenom[],char nom[],int n,int p,char IdUtil[]);
void sauvegardeTAdherentBinaire(Adherent *tAdherents[], int nbAdherents);
Adherent** chargementBinaireTAdherents(Adherent **tAdherent, int*nbAdherent);
void testChercherAdherent(void);


//int chargerEmprunt(char* fileName, Emprunt* tEmprunt[], int maxsize);
Emprunt lireEmprunt(FILE *flot);
ListeEmprunt empruntvide(void);
ListeEmprunt chargerListeEmprunt(char* fileName,ListeEmprunt le);
ListeEmprunt mettreEnListe(FILE *flot,ListeEmprunt le);
ListeEmprunt ajouterEmprunt(ListeEmprunt le,Emprunt e);
Emprunt creationEmprunt(char idJeu[],char idAdherent[],Date d);
void creationidEmprunt(char idJeu[],char idAdherent[],Date d,char idEmprunt[]);
ListeEmprunt InsertionEnTete(ListeEmprunt le,Emprunt emp);
void AfficherListeEmprunt(ListeEmprunt le,Adherent *tAdherent[],int nbAdherent, Jeux* tJeux[],int nbJeux);
ListeEmprunt chercherEmprunt(ListeEmprunt le,char idEmprunt[]);
ListeEmprunt supprimerEmprunt(ListeEmprunt le,char idEmprunt[]);
ListeEmprunt supprimerEnTeteEmprunt(ListeEmprunt le);
int CompteEmprunt(ListeEmprunt le, Emprunt emp, int i);
void sauvegardeBinaireEmprunts(ListeEmprunt le);
ListeEmprunt chargementBinairetEmrunts(void);
void freeListeEmprunt(ListeEmprunt le);

void faireUnEmpruntouUneReservation(ListeEmprunt le, ListeReservation lr, Jeux* tJeux[], Adherent* tAdherent[], int nbJeux, int nbAdherent);

//void testEmprunt(void);
//void testFaireEmprunt(void);

ListeReservation reservationVide(void);
ListeReservation ajouterEnTete(ListeReservation lr, Reservation r);
ListeReservation CreationDeLaListe(ListeReservation lr);
Reservation lireReservation(FILE *flot);
Reservation creationReservation(char idJeu[20], char idAdherent[20],Date dateReservation);
ListeReservation ajouterReservation(ListeReservation lr, Reservation r);
void AfficherListeReservation(ListeReservation lr, Adherent *tAdherent[], int nbAdherent, Jeux* tJeux[], int nbJeux);
void sauvegardeBinaireReservation(ListeReservation lr);
ListeReservation chargementBinairetReservations(void);
ListeReservation supprimerEnTeteUneReservation(ListeReservation lr);
ListeReservation supprimerUneReservation(ListeReservation lr, Reservation r);
void freeListeReservation(ListeReservation lr);
ListeReservation rechercheReservation(ListeReservation lr,char idJeu[]);

void afficherMenuType(void);
void MenuType(Jeux* tJeux[], int GameSize);
void afficherSousMenuJeux(void);
int choixSousMenuJeux(void);

void afficheMenuGlobal(void);
int choixMenuGlobal(void);
void menuGlobal(void);

int choixSousMenuAdmin(void);
void afficherSousMenuAdmin(void);
//MENU A MODIF

int blanc(char c);
void partieGauche(char source[],char dest[],int p);
void supprimeBlanc(char source[],char dest[]);
void minuscule(char chaine[]);
