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
                    //cout << jeu->joueur1.nbJetons<<"jeton ++"<<endl;
                } else {
                    jeu->plateau[i][j] = initJeton(BLANC,i,j);
                    jeu->joueur2.nbJetons+=1;
                    //cout << jeu->joueur2.nbJetons<<"jeton ++"<<endl;
                }
            } else {
                jeu->plateau[i][j] = initJeton(VIDE,i,j);
            }
        }
    }
}

/** AFFICHAGES */ 

void afficheCouleur (int couleur){
    if (couleur == NOIR)
        cout <<"NOIR";
    else if (couleur == BLANC)
        cout << "BLANC";
    else 
        cout << "VIDE";
}
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

void afficheCasesJouables(Joueur *joueur){
    cout << "Cases jouables : ";
    afficheListe(joueur->liste_cases_jouables);
}

/** TESTS */

bool testCaseExiste(int ligne, int colonne){
    return (ligne >= 0 && ligne < TAILLE_PLATEAU && colonne >= 0 && colonne < TAILLE_PLATEAU);
}

bool testPionAdverseDirection(Jeu *jeu, int couleur, int l, int c, int i){
    int ligne, colonne;
    if (i>=0){
        ligne = l + directions[i][0];
        colonne = c + directions[i][1];
    } else {
        ligne = l - directions[-i][0];
        colonne = c - directions[-i][1];
    }

    if (testCaseExiste(ligne,colonne)){
        if (jeu->plateau[ligne][colonne]->couleur == donneCouleurAdverse(couleur)){
            //cout<<"couleur adverse en "<<ligne<<" "<<colonne;
            return true;
        }
    }      
    return false;
}

/** Fonction que teste la présence d'un pion de couleur adverse autour de la position (l,c) */
bool testPionAdverseAutour (Jeu* jeu, int l, int c, int couleur){
    for (int i=0; i<8; i++){
        if (testPionAdverseDirection(jeu,couleur,l,c,i))
            return true;
    }
    return false;
}

bool testFinPartie(Jeu *jeu){
    if (!testGainPossible(jeu, NOIR) && !testGainPossible(jeu, BLANC))
        return true; 
    else 
        return false;
}

bool testGainPossible (Jeu *jeu, int couleur){
    for (int i =0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if (testGainCase(jeu, couleur, i, j)>0){
                return true;
            }
        }
    }
    return false;
}

int testGainCase(Jeu *jeu, int couleur, int l, int c){
    int gain = 0;
    for (int i=0; i<8; i++){
        if (testPionAdverseDirection(jeu,couleur,l,c,i)){
            gain += testGainDirection(jeu, couleur, l, c, i, 0);
        }
    }
    return gain;
}

int testGainDirection (Jeu *jeu, int couleur, int l, int c, int i, int g){
    int ligne = l + directions[i][0];
    int colonne = c + directions[i][1];
  
    if (g>=0){
        if (jeu->plateau[ligne][colonne]->couleur == donneCouleurAdverse(couleur)){
            g += testGainDirection(jeu, couleur, ligne, colonne, i, 0);
            if (g>=0)
                g++;
            return g;
        } else if (jeu->plateau[ligne][colonne]->couleur == couleur){
            return 0;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

/** DEROULEMENT DU JEU */ 

int donneCouleurAdverse (int couleur){
    if (couleur == NOIR)
        return BLANC;
    else 
        return NOIR; 
}

void chercheCasesPotentielles (Jeu *jeu, Joueur *joueur){
    videListe(joueur->liste_cases_potentielles);
    for (int i =0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            //cout << "test pour "<<i+1<<";"<<j+1 <<" "<<jeu->plateau[i][j]->couleur<<" ";
            if (jeu->plateau[i][j]->couleur==VIDE && testPionAdverseAutour(jeu,i,j,joueur->couleur)){
                //cout << " - ok"<<endl;
                ajouteJeton(joueur->liste_cases_potentielles,*(jeu->plateau[i][j]));
            } else {
                //cout << " - no"<<endl;
            }
        }
    }
}

void chercheCasesJouables(Jeu *jeu, Joueur *joueur){
    videListe(joueur->liste_cases_jouables);
    for (int i=0; i<joueur->liste_cases_potentielles->taille; i++){
        int ligne = joueur->liste_cases_potentielles->jeton[i].ligne;
        int colonne = joueur->liste_cases_potentielles->jeton[i].colonne;
        if (testGainCase(jeu, joueur->couleur,ligne, colonne) > 0){
            ajouteJeton(joueur->liste_cases_jouables, joueur->liste_cases_potentielles->jeton[i]);
        }
    }
}

void retournePions(Jeu *jeu, int couleur, int l, int c){
    for (int i=0; i<8; i++){
        if (testGainDirection(jeu, couleur, l, c, i, 0)>0){
            retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);
        }
    }
}

void retournePionsDirection(Jeu *jeu, int couleur, int l, int c, int i){
    if (jeu->plateau[l][c]->couleur==donneCouleurAdverse(couleur)){
        jeu->plateau[l][c]->couleur = couleur;
        if (jeu->joueur1.couleur == couleur){
            jeu->joueur1.nbJetons++;
        } else {
            jeu->joueur2.nbJetons++;
        }
        retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);

    }    
}

void joue(Jeu *jeu, Joueur *j, int ligne, int colonne){
    jeu->plateau[ligne][colonne]->couleur = j->couleur;
    j->nbJetons += 1;
    retournePions(jeu, j->couleur,ligne,colonne);
}

void tour (Jeu *jeu, Joueur *j){
    cout << "Tour du joueur "<<j->nom<<" (";
    afficheCouleur(j->couleur);
    cout<<")"<<endl;
    //calcul liste potentielles
    chercheCasesPotentielles(jeu, j);
    afficheListe(j->liste_cases_potentielles);
    //calcul liste jouables 
    chercheCasesJouables(jeu, j);
    afficheListe(j->liste_cases_jouables);

    if (j->liste_cases_jouables->taille>0){
        int ligne, colonne;
        do {
            cout << "Choisi une case (ligne, colonne) : ";
            cin >> ligne >> colonne; 
            ligne --;
            colonne --;
        } while (!testPresenceJeton(j->liste_cases_jouables,ligne,colonne));

        joue(jeu, j, ligne, colonne);
        affichePlateau(jeu);
        afficheScore(jeu);

    }else 
        cout << "Aucune case jouable"<<endl;   
}

void partie (){
    Jeu j;
    initJeu(&j);
    affichePlateau(&j);
    afficheScore(&j);

    while (!testFinPartie(&j)){
        tour (&j, &(j.joueur1));
        tour (&j, &(j.joueur2));
    }

    afficheResultats(&j);
}