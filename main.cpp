//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

#include <iostream>
using namespace std; 

#include "main.h"

#define VIDE 0
#define NOIR 1
#define BLANC 2

int main(){
    Jeu j;
    initJeu(&j);
    affichePlateau(&j);
    return 0;
}

void afficheJeton(Jeton j){
    if (j.couleur == VIDE){
        cout << " ";
    } else if (j.couleur == NOIR){
        cout << "N";
    } else {
        cout << "B";
    }
}

void affichePlateau(Jeu *jeu){
    for (int i = -1; i<TAILLE_PLATEAU; i++){
        cout << i + 1;
        for (int j = 0; j<TAILLE_PLATEAU; j++){
            cout <<" | ";
            if (i < 0)
                cout << j+1;
            else   
                //cout << "X" <<" | ";
                afficheJeton(*(jeu->plateau[i][j]));
            
        }
        cout <<endl << "-----------------------------------"<<endl;
    }
}

void afficheScore(Jeu *jeu) {
    cout << "SCORE"<<endl;
    cout << jeu->joueur1.nbJetons <<" Noirs VS "<<jeu->joueur2.nbJetons <<" Blancs"<<endl;
}

void initJeu(Jeu *jeu){
    Joueur *j1 = new Joueur;
    Joueur *j2 = new Joueur;
    cout << "Pseudo du joueur 1 : ";
    cin >> j1->nom;
    cout << "Pseudo du joueur 2 : ";
    cin >> j2->nom;
    jeu->joueur1 = *j1;
    jeu->joueur2 = *j2;
    initPlateau(jeu);
}

void initPlateau(Jeu *jeu){
    for (int i = 0; i<TAILLE_PLATEAU; i++){
        for (int j = 0; j<TAILLE_PLATEAU; j++){
            Jeton *p;
            p = (Jeton *)malloc(sizeof(Jeton));
            p->ligne = i;
            p->colonne = j;
            if ((i==3 || i==4)&&(j==3 || j==4)){
                if (j==i){
                    p->couleur = NOIR;
                } else {
                    p->couleur = BLANC;
                }
            } else {
                p->couleur = VIDE;
            }
            jeu->plateau[i][j] = p;
        }
    }
}

