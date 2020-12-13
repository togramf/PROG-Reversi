//Reversi - Projet 1 de programmation - IMAC 1 (2020-2021)
//par Théo Clément & Margot Fauchon 

struct Jeton {
    int couleur;
    int ligne;
    int colonne; 
};

struct Joueur {
    char nom[15];
    Jeton *liste;
    int nbJetons;
};

struct Jeu {
    Joueur joueur1;
    Joueur joueur2;
    Jeton *plateau[8][8];
};

int main();
void afficheJeton(Jeton j);
void initPlateau(Jeu *jeu);
void affichePlateau(Jeu *jeu);