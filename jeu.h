#include "liste.h"
#include <string.h>

#define TAILLE_PLATEAU 8
int const directions [8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

struct Joueur {
    char nom[15];
    int couleur;
    Liste *liste_cases_potentielles;
    Liste *liste_cases_jouables; 
    int nbJetons;
};

struct Jeu {
    Joueur joueur1;
    Joueur joueur2;
    Jeton *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
};

/** INITIALISATIONS */

void initJeu(Jeu *jeu);
void initPlateau(Jeu *jeu);

/** AFFICHAGES */ 

void afficheCouleur (int couleur);
void affichePlateau(Jeu *jeu);
void afficheScore(Jeu *jeu);
void afficheResultats(Jeu *j);
void afficheCasesJouables(Joueur *joueur);

/** TESTS */

bool testCaseExiste(int ligne, int colonne);
bool testPionAdverseDirection(Jeu *jeu, int couleur, int l, int c, int i);
bool testPionAdverseAutour (Jeu* jeu, int l, int c, int couleur);
bool testFinPartie(Jeu *jeu);
bool testGainPossible (Jeu *jeu, int couleur);
int testGainCase(Jeu *jeu, int couleur, int l, int c);
int testGainDirection (Jeu *jeu, int couleur, int l, int c, int i, int g);

/** DEROULEMENT DU JEU */

int donneCouleurAdverse (int couleur);
void chercheCasesPotentielles (Jeu *jeu, Joueur *joueur);
void chercheCasesJouables(Jeu *jeu, Joueur *joueur);
void joue(Jeu *jeu, Joueur *j, int ligne, int colonne);
void tour (Jeu *jeu, Joueur j);
void partie ();