//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

#include <iostream>
using namespace std; 

#define VIDE 0
#define NOIR 1
#define BLANC 2

struct Jeton {
    int couleur;
    int ligne;
    int colonne; 
};


Jeton* initJeton(int couleur, int l, int c);
void afficheJeton(Jeton *j);