#include "liste.h"

Liste * initListe (){
    int cap = 60;
    Liste *l = (Liste *)malloc(2*sizeof(int)+sizeof(Jeton)*cap);
    if (l == 0){
        cout << "Erreur alloc memoire"<<endl;
    } else {
        l->taille = 0;
        l->capacite = cap;
    }
    return l;
}

bool testPresenceJeton(Liste *l, int ligne, int colonne){
    for (int i=0; i<l->taille; i++){
        if (l->jeton[i].ligne == ligne && l->jeton[i].colonne == colonne){
            //cout<<"Jeton "<< ligne << " " <<colonne <<" present dans la liste"<<endl;
            return true;
        }
    }
    //cout <<"Jeton absent"<<endl;
    return false;
}

void afficheListe(Liste *l){
    for (int i=0; i<l->taille; i++){
        cout <<" ["<<l->jeton[i].ligne+1<<";"<<l->jeton[i].colonne+1<<"] ";
        cout << " ; ";
    }
    cout <<endl;
}

void ajouteJeton (Liste *l, Jeton j){
    if (testPresenceJeton(l,j.ligne, j.colonne)){
        //cout<<"Jeton deja dans la liste"<<endl;
    } else if (l->taille < l->capacite) {
        l->jeton[l->taille]=j;
        l->taille ++;
        //cout << "Jeton ajoute"<<endl;
    }
}

void videListe (Liste *l){
    free(l->jeton);
    l->jeton = (Jeton *) malloc(sizeof(Jeton)*l->capacite);
    l->taille = 0;
}