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
    initPlateau(&j);
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

void initPlateau(Jeu *jeu){
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
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

void affichePlateau(Jeu *jeu){
    for (int i = -1; i<8; i++){
        cout << i + 1;
        for (int j = 0; j<8; j++){
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