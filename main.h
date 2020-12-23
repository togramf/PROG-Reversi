//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

#define TAILLE_PLATEAU 8

struct Jeton {
    int couleur;
    int ligne;
    int colonne; 
};

struct Joueur {
    char nom[15];
    int couleur;
    Jeton *liste;
    Jeton *liste_possibilites; 
    int nbJetons;
};

struct Jeu {
    Joueur joueur1;
    Joueur joueur2;
    Jeton *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
};

int main();
void afficheJeton(Jeton j);
void initJeu(Jeu *jeu);
void initPlateau(Jeu *jeu);
void affichePlateau(Jeu *jeu);
void afficheScore(Jeu *jeu);
void tour (Jeu *jeu, Joueur j);