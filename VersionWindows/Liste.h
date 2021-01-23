#include "Jeton.h"

struct Liste{
    int cases[40][2];  
    int taille;
};

Liste * initListe ();
void videListe(Liste* l);
bool testPresenceJeton(Liste *l, int ligne, int colonne);
void afficheListe(Liste *l);
void ajouteJeton (Liste *l, int ligne, int colonne);
