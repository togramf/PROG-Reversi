/* JETON */

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

Jeton* initJeton(int couleur, int l, int c){
    Jeton* j = new Jeton;
    j->couleur = couleur;
    j->colonne = c;
    j->ligne = l;
    return j;
}

void afficheJeton(Jeton *j){
    if (j->couleur == VIDE)
        cout << " ";
    else if (j->couleur == NOIR)
        cout << "X";
    else
        cout << "O";
}

/* LISTE */

struct Liste{
    int cases[40][2];  
    int taille;
};


Liste * initListe (){
    Liste *l = new Liste;
    l->taille = 0;
    return l;
}

void videListe(Liste* l){
    l->taille = 0;
}

bool testPresenceJeton(Liste *l, int ligne, int colonne){
    for (int i=0; i<l->taille; i++){
        if (l->cases[i][0]==ligne && l->cases[i][1]==colonne)
            return true;
    }
    return false;
}

void afficheListe(Liste *l){
    for (int i=0; i<l->taille; i++){
        cout<<"("<<l->cases[i][0]+1<<","<<l->cases[i][1]+1<<")";
        cout<<" ; ";
    }
    cout<<endl;
}

void ajouteJeton (Liste *l, int ligne, int colonne){
    if (!testPresenceJeton(l, ligne, colonne)){
        l->cases[l->taille][0]=ligne;
        l->cases[l->taille][1]=colonne;
        l->taille ++;
    }
}

/* JEU */

#include <string.h>

#define TAILLE_PLATEAU 8

/** 8 directions autour d'une case, sur le plateau : 
 *  direction 0 | direction 1 | direction 2
 *  direction 3 | cible       | direction 4
 *  direction 5 | direction 6 | direction 7
*/
int const directions [8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

struct Joueur {
    char nom[15];
    int couleur;
    Liste *liste_cases_potentielles;
    Liste *liste_cases_jouables; 
    int nbJetons;
};

struct Jeu {
    Joueur joueur1;
    Joueur joueur2;
    Jeton *plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
};

/** INITIALISATIONS */

void initJeu(Jeu *jeu);
void initPlateau(Jeu *jeu);

/** AFFICHAGES */ 

void afficheCouleur (int couleur);
void affichePlateau(Jeu *jeu);
void afficheScore(Jeu *jeu);
void afficheResultats(Jeu *j);

/** TESTS */

bool testCaseExiste(int ligne, int colonne);
bool testPionAdverseDirection(Jeu *jeu, int couleur, int l, int c, int i);
bool testPionAdverseAutour (Jeu* jeu, int couleur, int l, int c);
bool testFinPartie(Jeu *jeu);
bool testGainPossible (Jeu *jeu, Joueur *joueur);
int testGainCase(Jeu *jeu, int couleur, int l, int c);
int testGainDirection (Jeu *jeu, int couleur, int l, int c, int i, int g);

/** DEROULEMENT DU JEU */

int donneCouleurAdverse (int couleur);
void calculScores(Jeu *jeu);
void chercheCasesPotentielles (Jeu *jeu, Joueur *joueur, bool aide);
void chercheCasesJouables(Jeu *jeu, Joueur *joueur, bool aide);
void retournePionsDirection(Jeu *jeu, int couleur, int l, int c, int i);
void retournePions(Jeu *jeu, int couleur, int l, int c);
void joue(Jeu *jeu, Joueur *j, int ligne, int colonne);
void tour (Jeu *jeu, Joueur j, bool aide);
void partie ();


/** INITIALISATIONS */

void initJeu(Jeu *jeu){
    Joueur *j1 = new Joueur;
    Joueur *j2 = new Joueur;

    cout << "Pseudo du joueur 1 : ";
    cin >> j1->nom;
    j1->couleur = BLANC;
    j1->nbJetons = 0;
    j1->liste_cases_potentielles = initListe();
    j1->liste_cases_jouables = initListe();

    cout << "Pseudo du joueur 2 : ";
    cin >> j2->nom;
    j2->couleur = NOIR;
    j2->nbJetons = 0;
    j2->liste_cases_potentielles = initListe();
    j2->liste_cases_jouables = initListe();

    jeu->joueur1 = *j1;
    jeu->joueur2 = *j2;

    initPlateau(jeu);
}

void initPlateau(Jeu *jeu){
    int MILIEU_PLATEAU_1 = TAILLE_PLATEAU/2-1;
    int MILIEU_PLATEAU_2 = TAILLE_PLATEAU/2;

    for (int i=0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if ((i==MILIEU_PLATEAU_1 || i==MILIEU_PLATEAU_2)&&(j==MILIEU_PLATEAU_1 || j==MILIEU_PLATEAU_2)){
                if (j==i)
                    jeu->plateau[i][j] = initJeton(NOIR, i,j);
                else 
                    jeu->plateau[i][j] = initJeton (BLANC, i,j);
            } else {
                jeu->plateau[i][j] = initJeton (VIDE, i,j);
            }
        }
    }
}

/** AFFICHAGES */ 

void afficheCouleur (int couleur){
    if (couleur == NOIR)
        cout <<"(X) NOIR";
    else if (couleur == BLANC)
        cout << "(O) BLANC";
    else 
        cout << "VIDE";
}

void affichePlateau(Jeu *jeu){
    //system("cls");
    system("clear"); //Pour linux 
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
    calculScores(jeu);
    cout << "SCORE : ";
    int nb1 = jeu->joueur1.nbJetons;
    int nb2 = jeu->joueur2.nbJetons;
    cout << nb1 << " ";
    afficheCouleur(jeu->joueur1.couleur);
    cout<<"S VS "<< nb2 << " ";
    afficheCouleur(jeu->joueur2.couleur);
    cout <<"S "<<endl;
}

void afficheResultats(Jeu *j){
    cout <<"-----------------------------------"<<endl;
    afficheScore(j);
    if (j->joueur1.nbJetons > j->joueur2.nbJetons)
        cout << "Le gagnant est "<<j->joueur1.nom << " ! Bravo !"<<endl;
    else if (j->joueur1.nbJetons < j->joueur2.nbJetons)
        cout << "Le gagnant est "<<j->joueur2.nom << " ! Bravo !"<<endl;
    else 
        cout << "Egalite ! Incroyable !"<<endl;
    cout <<"-----------------------------------"<<endl;
}

/** TESTS */

bool testCaseExiste(int ligne, int colonne){
    return (ligne >= 0 && ligne < TAILLE_PLATEAU && colonne >= 0 && colonne < TAILLE_PLATEAU);
}

bool testPionAdverseDirection(Jeu *jeu, int couleur, int l, int c, int i){
    int ligne, colonne;
    
    ligne = l + directions[i][0];
    colonne = c + directions[i][1];

    if (testCaseExiste(ligne,colonne)){
        if (jeu->plateau[ligne][colonne]->couleur == donneCouleurAdverse(couleur)){
            //if (test)
                //cout <<"couleur adverse en "<<ligne<<" "<<colonne<<endl;
            return true;
        }
    }      
    return false;
}

/** Fonction qui teste la présence d'un pion de couleur adverse autour de la position (l,c) */
bool testPionAdverseAutour (Jeu* jeu, int couleur, int l, int c){
    for (int i=0; i<8; i++){
        if (testPionAdverseDirection(jeu,couleur,l,c,i)){
            //if (test)
                //cout<<"Pion adverse present autour de "<<l<<" "<<c<<endl;
            return true;
        }  
    }
    return false;
}

bool testFinPartie(Jeu *jeu){
    if (!testGainPossible(jeu, &(jeu->joueur1)) && !testGainPossible(jeu, &(jeu->joueur2)))
        return true; 
    else 
        return false;
}

bool testGainPossible (Jeu *jeu, Joueur *joueur){
    chercheCasesJouables(jeu, joueur, false);

    if (joueur->liste_cases_jouables->taille>0)
        return true;

    return false;
}

int testGainCase(Jeu *jeu, int couleur, int l, int c){
    int gain = 0;
    for (int i=0; i<8; i++){
        if (testPionAdverseDirection(jeu,couleur,l,c,i)){
            if (testGainDirection(jeu, couleur, l, c, i, 0)>0)
                gain += testGainDirection(jeu, couleur, l, c, i, 0);
        }
    }
    return gain;
}

int testGainDirection (Jeu *jeu, int couleur, int l, int c, int i, int g){

    int ligne = l + directions[i][0];
    int colonne = c + directions[i][1];
  
    if (g>=0){
        if (testCaseExiste(ligne, colonne)){
            if (jeu->plateau[ligne][colonne]->couleur == donneCouleurAdverse(couleur)){
            g += testGainDirection(jeu, couleur, ligne, colonne, i, 0);
            if (g>=0)
                g++;
            return g;
            } else if (jeu->plateau[ligne][colonne]->couleur == couleur){
                return 0;
            } 
        }else {
            return -1;
        }
    } 
    return -1;
    
}

/** DEROULEMENT DU JEU */ 

int donneCouleurAdverse (int couleur){
    if (couleur == NOIR)
        return BLANC;
    else 
        return NOIR; 
}

void calculScores(Jeu *jeu){
    jeu->joueur1.nbJetons =0;
    jeu->joueur2.nbJetons =0;

    for (int i =0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if (jeu->plateau[i][j]->couleur == jeu->joueur1.couleur){
                jeu->joueur1.nbJetons ++;
            } else if (jeu->plateau[i][j]->couleur == jeu->joueur2.couleur){
                jeu->joueur2.nbJetons ++;
            }
        }
    }
}

void chercheCasesPotentielles (Jeu *jeu, Joueur *joueur){
    Liste* l = joueur->liste_cases_potentielles;
    videListe(l);
    
    for (int i =0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if (jeu->plateau[i][j]->couleur==VIDE && testPionAdverseAutour(jeu,joueur->couleur,i,j))
                ajouteJeton(l, i, j);
        }
    }
}

void chercheCasesJouables(Jeu *jeu, Joueur *joueur, bool aide){
    chercheCasesPotentielles(jeu, joueur);

    Liste* l = joueur->liste_cases_jouables;
    videListe(l);

    for (int i=0; i<joueur->liste_cases_potentielles->taille; i++){
        int ligne = joueur->liste_cases_potentielles->cases[i][0];
        int colonne = joueur->liste_cases_potentielles->cases[i][1];
        if (testGainCase(jeu, joueur->couleur,ligne, colonne) > 0){
            ajouteJeton(l, ligne, colonne);
        }
    }

    if (aide){ //assistance
        cout << "Cases jouables pour les ";
        afficheCouleur(joueur->couleur);
        cout<<endl;
        afficheListe(l);
    }
}

void retournePions(Jeu *jeu, int couleur, int l, int c){
    for (int i=0; i<8; i++){
        if (testGainDirection(jeu, couleur, l, c, i, 0)>0)
            retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);
    }
}

void retournePionsDirection(Jeu *jeu, int couleur, int l, int c, int i){
    if (jeu->plateau[l][c]->couleur==donneCouleurAdverse(couleur)){
        jeu->plateau[l][c]->couleur = couleur;
        retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);
    }    
}

void joue(Jeu *jeu, Joueur *j, int ligne, int colonne){
    jeu->plateau[ligne][colonne]->couleur = j->couleur;
    retournePions(jeu, j->couleur,ligne,colonne);
}

void tour (Jeu *jeu, Joueur *j, bool aide){
    cout << "Tour du joueur "<<j->nom<<" (";
    afficheCouleur(j->couleur);
    cout<<")"<<endl;
    
    chercheCasesJouables(jeu, j, aide);

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
        cout << "Aucun coup possible"<<endl;   
}

void partie (){
    cout <<"LANCEMENT DE LA PARTIE"<< endl;

    bool assistance = false; 

    char temp;
    cout<<"Jouer avec une assistance ? (y/n)";
    cin >> temp;
    if (temp == 'y')
        assistance = true;
    

    Jeu j;
    initJeu(&j);
    affichePlateau(&j);
    afficheScore(&j);

    while (!testFinPartie(&j)){
        tour (&j, &(j.joueur1), assistance);
        tour (&j, &(j.joueur2), assistance);
    }

    afficheResultats(&j);
}

/* MAIN */

int main(){
    partie();
    
    return 0;
}