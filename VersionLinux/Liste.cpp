//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

#include "Liste.h"

Liste * initListe (){
    Liste *l = new Liste;
    l->taille = 0;
    return l;
}

void videListe(Liste* l){
    l->taille = 0;
}

bool testPresenceJeton(Liste *l, int ligne, int colonne){
    for (int i=0; i<l->taille; i++){
        if (l->cases[i][0]==ligne && l->cases[i][1]==colonne)
            return true;
    }
    return false;
}

void afficheListe(Liste *l){
    for (int i=0; i<l->taille; i++){
        cout<<"("<<l->cases[i][0]+1<<","<<l->cases[i][1]+1<<")";
        cout<<" ; ";
    }
    cout<<endl;
}

void ajouteJeton (Liste *l, int ligne, int colonne){
    if (!testPresenceJeton(l, ligne, colonne)){
        l->cases[l->taille][0]=ligne;
        l->cases[l->taille][1]=colonne;
        l->taille ++;
    }
}

