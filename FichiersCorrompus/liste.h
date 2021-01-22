#include "jeton.h"

struct Liste{
    Jeton *jeton; //pointeur sur premier jeton de la liste 
    int taille;
    int capacite;
};

Liste * initListe ();
bool testPresenceJeton(Liste *l, int ligne, int colonne);
void afficheListe(Liste *l);
void ajouteJeton (Liste *l, Jeton j);
void videListe (Liste *l);