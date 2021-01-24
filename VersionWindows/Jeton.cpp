#include "Jeton.h"

Jeton* initJeton(int couleur, int l, int c){
    Jeton* j = new Jeton;
    j->couleur = couleur;
    j->colonne = c;
    j->ligne = l;
    return j;
}

void afficheJeton(Jeton *j){
    if (j->couleur == VIDE)
        cout << " ";
    else if (j->couleur == NOIR)
        cout << "X";
    else
        cout << "O";
}

