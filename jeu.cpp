#include "jeu.h"

/** INITIALISATIONS */

void initJeu(Jeu *jeu){
    Joueur *j1 = new Joueur;
    Joueur *j2 = new Joueur;

    cout << "Pseudo du joueur 1 : ";
    cin >> j1->nom;
    j1->couleur = NOIR;
    j1->nbJetons = 0;
    j1->liste_cases_potentielles = initListe();
    j1->liste_cases_jouables = initListe();

    cout << "Pseudo du joueur 2 : ";
    cin >> j2->nom;
    j2->couleur = BLANC;
    j2->nbJetons = 0;
    j2->liste_cases_potentielles = initListe();
    j2->liste_cases_jouables = initListe();

    jeu->joueur1 = *j1;
    jeu->joueur2 = *j2;

    initPlateau(jeu);
}

void initPlateau(Jeu *jeu){
    for (int i = 0; i<TAILLE_PLATEAU; i++){
        for (int j = 0; j<TAILLE_PLATEAU; j++){
            if ((i==3 || i==4)&&(j==3 || j==4)){
                if (j==i){
                    jeu->plateau[i][j] = initJeton(NOIR,i,j);
                    jeu->joueur1.nbJetons+=1;
                    cout << jeu->joueur1.nbJetons<<"jeton ++"<<endl;
                } else {
                    jeu->plateau[i][j] = initJeton(BLANC,i,j);
                    jeu->joueur2.nbJetons+=1;
                    cout << jeu->joueur2.nbJetons<<"jeton ++"<<endl;
                }
            } else {
                jeu->plateau[i][j] = initJeton(VIDE,i,j);
            }
        }
    }
}

/** AFFICHAGES */ 


void affichePlateau(Jeu *jeu){
    for (int i = -1; i<TAILLE_PLATEAU; i++){
        cout << i + 1;
        for (int j = 0; j<TAILLE_PLATEAU; j++){
            cout <<" | ";
            if (i < 0)
                cout << j+1;
            else   
                afficheJeton(jeu->plateau[i][j]);
            
        }
        cout <<endl << "-----------------------------------"<<endl;
    }
}

void afficheScore(Jeu *jeu) {
    cout << "SCORE : ";
    int nbNoirs = jeu->joueur1.nbJetons;
    int nbBlancs = jeu->joueur2.nbJetons;
    cout << nbNoirs <<" Noirs VS "<< nbBlancs <<" Blancs"<<endl;
}

void afficheResultats(Jeu *j){
    afficheScore(j);
    if (j->joueur1.nbJetons > j->joueur2.nbJetons){
        cout << "Le gagnant est "<<j->joueur1.nom << " ! Bravo !"<<endl;
    } else if (j->joueur1.nbJetons < j->joueur2.nbJetons){
        cout << "Le gagnant est "<<j->joueur2.nom << " ! Bravo !"<<endl;
    } else {
        cout << "Egalité ! Incroyable !"<<endl;
    }
}

/** TESTS */

bool testCaseExiste(int ligne, int colonne){
    return (ligne >= 0 && ligne < TAILLE_PLATEAU && colonne >= 0 && colonne < TAILLE_PLATEAU);
}

/** Fonction que teste la présence d'un pion de couleur adverse autour de la position (l,c) */
bool testPionAdverseAutour (Jeu* jeu, int l, int c, int couleur){
    for (int i=-1; i<=1; i++){
        for (int j=-1; j<=1; j++){
            if (testCaseExiste(l+i, c+j))
                return (jeu->plateau[l+i][c+j]->couleur == donneCouleurAdverse(couleur));
        }
    }
    return false;
}

bool testFinPartie(){
    //la parti est finie si joueur1 ou joueur2 ne peut plus faire de gain 
    return false;
}

/** DEROULEMENT DU JEU */ 

int donneCouleurAdverse (int couleur){
    if (couleur == NOIR)
        return BLANC;
    else 
        return NOIR; 
}

void tour (Jeu *jeu, Joueur *j){
    //calcul liste potentielles
    //calcul liste jouables 
    cout << "Tour du joueur "<<j->nom<<endl;
    int ligne, colonne;
    cout << "Choisi une case (ligne, colonne) : ";
    cin >> ligne >> colonne; 
    ligne --;
    colonne --;

    //test si jeton dans la liste 
    jeu->plateau[ligne][colonne]->couleur = j->couleur;
    j->nbJetons += 1;
    cout << j->nbJetons << "jeton ++"<<endl;
    cout << "jeton ++"<<endl;
    affichePlateau(jeu);
    afficheScore(jeu);
}

void partie (){
    Jeu j;
    initJeu(&j);
    affichePlateau(&j);
    afficheScore(&j);

    while (!testFinPartie()){
        tour (&j, &(j.joueur1));
        tour (&j, &(j.joueur2));
    }

    afficheResultats(&j);
}