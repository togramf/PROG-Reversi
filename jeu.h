#include "liste.h"
#include <string.h>

#define TAILLE_PLATEAU 8

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

void affichePlateau(Jeu *jeu);
void afficheScore(Jeu *jeu);
void afficheResultats(Jeu *j);

/** TESTS */

bool testCaseExiste(int ligne, int colonne);
bool testPionAdverseAutour (Jeu* jeu, int l, int c, int couleur);
bool testFinPartie();

/** DEROULEMENT DU JEU */

int donneCouleurAdverse (int couleur);
void tour (Jeu *jeu, Joueur j);
void partie ();