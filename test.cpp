/* JETONS */ 

#include <iostream>
using namespace std; 

#define VIDE 0
#define NOIR 1
#define BLANC 2

bool assistance = false;

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
    if (j->couleur == VIDE){
        cout << " ";
    } else if (j->couleur == NOIR){
        cout << "N";
    } else {
        cout << "B";
    }
}

/* LISTE */

struct Liste{
    Jeton *jeton; //pointeur sur premier jeton de la liste 
    int taille;
    int capacite;
};

Liste * initListe ();
bool testPresenceJeton(Liste *l, int ligne, int colonne);
void afficheListe(Liste *l);
void ajouteJeton (Liste *l, Jeton j);
void videListe (Liste *l);

Liste * initListe (){
    int cap = 60;
    Liste *l = (Liste *)malloc(2*sizeof(int)+sizeof(Jeton)*cap);
    if (l == 0){
        cout << "Erreur alloc memoire"<<endl;
    } else {
        l->taille = 0;
        l->capacite = cap;
    }
    return l;
}

bool testPresenceJeton(Liste *l, int ligne, int colonne){
    for (int i=0; i<l->taille; i++){
        if (l->jeton[i].ligne == ligne && l->jeton[i].colonne == colonne){
            //cout<<"Jeton "<< ligne << " " <<colonne <<" present dans la liste"<<endl;
            return true;
        }
    }
    //cout <<"Jeton absent"<<endl;
    return false;
}

void afficheListe(Liste *l){
    for (int i=0; i<l->taille; i++){
        cout <<" ["<<l->jeton[i].ligne+1<<";"<<l->jeton[i].colonne+1<<"] ";
        cout << " ; ";
    }
    cout <<endl;
}

void ajouteJeton (Liste *l, Jeton j){
    if (testPresenceJeton(l,j.ligne, j.colonne)){
        //cout<<"Jeton deja dans la liste"<<endl;
    } else if (l->taille < l->capacite) {
        l->jeton[l->taille]=j;
        l->taille ++;
        //cout << "Jeton ajoute"<<endl;
    }
}

void videListe (Liste *l){
    free(l->jeton);
    l->jeton = (Jeton *) malloc(sizeof(Jeton)*l->capacite);
    l->taille = 0;
}

/* JEU */

#define TAILLE_PLATEAU 8
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
bool testPionAdverseAutour (Jeu* jeu, int l, int c, int couleur);
bool testFinPartie(Jeu *jeu);
bool testGainPossible (Jeu *jeu, int couleur);
int testGainCase(Jeu *jeu, int couleur, int l, int c);
int testGainDirection (Jeu *jeu, int couleur, int l, int c, int i, int g);

/** DEROULEMENT DU JEU */

int donneCouleurAdverse (int couleur);
void calculScores(Jeu *jeu);
void chercheCasesPotentielles (Jeu *jeu, Joueur *joueur);
void chercheCasesJouables(Jeu *jeu, Joueur *joueur);
void retournePionsDirection(Jeu *jeu, int couleur, int l, int c, int i);
void retournePions(Jeu *jeu, int couleur, int l, int c);
void joue(Jeu *jeu, Joueur *j, int ligne, int colonne);
void tour (Jeu *jeu, Joueur j);
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
    for (int i = 0; i<TAILLE_PLATEAU; i++){
        for (int j = 0; j<TAILLE_PLATEAU; j++){
            if ((i==3 || i==4)&&(j==3 || j==4)){
                if (j==i){
                    jeu->plateau[i][j] = initJeton(NOIR,i,j);
                    //cout << jeu->joueur1.nbJetons<<"jeton ++"<<endl;
                } else {
                    jeu->plateau[i][j] = initJeton(BLANC,i,j);
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

/** Fonction qui teste la présence d'un pion de couleur adverse autour de la position (l,c) */
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
                //cout << "gain "<< testGainCase(jeu, couleur, i, j)<< " en "<<i<<" "<<j<<endl;
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
            //cout << "Test gain ";
            gain += testGainDirection(jeu, couleur, l, c, i, 0);
        }
    }
    return gain;
}

int testGainDirection (Jeu *jeu, int couleur, int l, int c, int i, int g){
    //cout << "direction "<<i<<endl;
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
            //cout << "test pour "<<i+1<<";"<<j+1 <<" "<<jeu->plateau[i][j]->couleur<<" ";
            if (jeu->plateau[i][j]->couleur==VIDE && testPionAdverseAutour(jeu,i,j,joueur->couleur)){
                //cout << " - ok"<<endl;
                ajouteJeton(l,*(jeu->plateau[i][j]));
            } else {
                //cout << " - no"<<endl;
            }
        }
    }

    if (assistance){
        //affichage cases potentielles 
        cout << "Cases potentielles pour les ";
        afficheCouleur(joueur->couleur);
        cout<<endl;
        for (int i = 0; i<l->taille; i++){
            cout <<" ["<<l->jeton[i].ligne+1<<";"<<l->jeton[i].colonne+1<<"] ";
            int gain = testGainCase(jeu, joueur->couleur, l->jeton[i].ligne, l->jeton[i].colonne);
            cout << gain;
            cout <<" ; ";
        }
        cout <<endl;
    }
    
    
}

void chercheCasesJouables(Jeu *jeu, Joueur *joueur){
    Liste* l = joueur->liste_cases_jouables;
    videListe(l);
    for (int i=0; i<joueur->liste_cases_potentielles->taille; i++){
        Jeton jeton = joueur->liste_cases_potentielles->jeton[i];
        int ligne = jeton.ligne;
        int colonne = jeton.colonne;
        if (testGainCase(jeu, joueur->couleur,ligne, colonne) >= 0){
            ajouteJeton(l, jeton);
        }
    }

    if (assistance){
        //affichage cases jouables 
        cout << "Cases jouables pour les ";
        afficheCouleur(joueur->couleur);
        cout<<endl;
        for (int i = 0; i<l->taille; i++){
            cout <<" ["<<l->jeton[i].ligne+1<<";"<<l->jeton[i].colonne+1<<"] ";
            cout <<" ; ";
        }
        cout <<endl;
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
        retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);
    }    
}

void joue(Jeu *jeu, Joueur *j, int ligne, int colonne){
    jeu->plateau[ligne][colonne]->couleur = j->couleur;
    retournePions(jeu, j->couleur,ligne,colonne);
}

void tour (Jeu *jeu, Joueur *j){
    cout << "Tour du joueur "<<j->nom<<" (";
    afficheCouleur(j->couleur);
    cout<<")"<<endl;
    //calcul liste potentielles
    chercheCasesPotentielles(jeu, j);
    //calcul liste jouables 
    chercheCasesJouables(jeu, j);

    if (j->liste_cases_jouables->taille>0){
        int ligne = 0, colonne = 0;
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
    cout << "LANCEMENT DE LA PARTIE"<<endl;

    char temp;
    cout << "Jouer en avec assistance ? (y/n)";
    cin >> temp;
    if (temp == 'y')
        assistance = true;

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

/* MAIN */

int main(){
    partie();
    
    return 0;
}