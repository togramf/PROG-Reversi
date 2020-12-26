//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

#include <iostream>
using namespace std; 


#include "main.h"



int main(){
    
    partie();
    
    return 0;
}

/**
void casesPotentielles (Jeu *jeu, Joueur *joueur){
    joueur->liste_cases_potentielles=NULL;
    for (int i=0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if (jeu->plateau[i][j]->couleur == VIDE){
                if (TestPionAdverseAutour(jeu, i, j, joueur->couleur)){
                    ajouteJeton(joueur->liste_cases_potentielles, jeu->plateau[i][j]);
                }
            }
        }
    }
}
*/

