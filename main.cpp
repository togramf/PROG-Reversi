//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

#include <iostream>
using namespace std; 


#include "main.h"



int main(){
    
    partie();
    
    return 0;
}

void testUnitaire1 (){
    Jeu j;
    initJeu(&j);

    //VIDE PLATEAU
    j.plateau[3][3]->couleur=VIDE;
    j.plateau[3][4]->couleur=VIDE;
    j.plateau[4][3]->couleur=VIDE;
    j.plateau[4][4]->couleur=VIDE;

    //TEST PION AUTOUR > OK 
    /*j.plateau[4][4]->couleur=NOIR;
    affichePlateau(&j);
    cout<<testPionAdverseAutour(&j,3,3,BLANC);
    cout<<testPionAdverseAutour(&j,3,4,BLANC);
    cout<<testPionAdverseAutour(&j,3,5,BLANC);
    cout<<testPionAdverseAutour(&j,4,3,BLANC);
    cout<<testPionAdverseAutour(&j,4,5,BLANC);
    cout<<testPionAdverseAutour(&j,5,3,BLANC);
    cout<<testPionAdverseAutour(&j,5,4,BLANC);
    cout<<testPionAdverseAutour(&j,5,5,BLANC);*/

    //TEST PION AUTOUR > OK 
    /*j.plateau[0][0]->couleur=NOIR; // test direction1
    cout<<testPionAdverseAutour(&j,1,1,BLANC);
    j.plateau[0][3]->couleur=NOIR; // test direction2
    cout<<testPionAdverseAutour(&j,1,3,BLANC);
    j.plateau[0][6]->couleur=NOIR; // test direction3
    cout<<testPionAdverseAutour(&j,1,5,BLANC);
    j.plateau[3][0]->couleur=NOIR; 
    cout<<testPionAdverseAutour(&j,3,1,BLANC);
    j.plateau[3][3]->couleur=NOIR;
    cout<<testPionAdverseAutour(&j,3,2,BLANC);
    j.plateau[6][0]->couleur=NOIR;
    cout<<testPionAdverseAutour(&j,5,1,BLANC);
    j.plateau[6][3]->couleur=NOIR;
    cout<<testPionAdverseAutour(&j,5,3,BLANC);
    j.plateau[6][6]->couleur=NOIR;
    cout<<testPionAdverseAutour(&j,5,5,BLANC);
    affichePlateau(&j);*/

    //TEST TestGainPossible OK 
    /*j.plateau[4][4]->couleur = NOIR;
    j.plateau[6][6]->couleur = NOIR;
    affichePlateau(&j);
    for (int i = 3; i<=5; i++){
        for (int h =3; h<=5; h++){
            cout << i <<" "<<h<<" : ";
            if (j.plateau[i][h]->couleur == VIDE){
                j.plateau[i][h]->couleur = BLANC;
                testGainPossible(&j, BLANC);
                j.plateau[i][h]->couleur = VIDE;
            }
        }
    }*/

    /*j.plateau[4][4]->couleur = NOIR;
    j.plateau[5][3]->couleur = BLANC;
    affichePlateau(&j);
    testGainPossible(&j,BLANC);
    testGainPossible(&j,NOIR);*/




    
}


