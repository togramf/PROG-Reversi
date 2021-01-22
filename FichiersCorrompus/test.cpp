/* JETONS */

#include <iostream>
using namespace std;

#define VIDE 0
#define NOIR 1
#define BLANC 2

bool assistance = false;
bool test = false; 

struct Jeton {
    int couleur;
    int ligne;
    int colonne;
};

Jeton* initJeton(int couleur, int l, int c){
    Jeton *j = new Jeton;
    j->couleur = couleur;
    j->ligne = l;
    j->colonne = c;
    return j;
}

void afficheJeton (Jeton *j){
    if (j->couleur == VIDE)
        cout <<" ";
    else if (j->couleur == NOIR)
        cout <<"N";
    else 
        cout<<"B";
}

/* LISTE */

struct Liste {
    int cases[40][2];
    int taille;
};

Liste* initListe(){
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

void ajouteJeton(Liste *l, int ligne,int colonne){
    if (!testPresenceJeton(l, ligne, colonne)){
        l->cases[l->taille][0]=ligne;
        l->cases[l->taille][1]=colonne;
        l->taille ++;
    }
}

/* JEU */

#define TAILLE_PLATEAU 8
int const directions [8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
/** sur le plateau : 
 *  direction 0 | direction 1 | direction 2
 *  direction 3 | cible       | direction 4
 *  direction 5 | direction 6 | direction 7
*/

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

void afficheCouleur (int couleur){
    if (couleur == NOIR)
        cout <<"NOIR";
    else if (couleur == BLANC)
        cout <<"BLANC";
    else 
        cout <<"VIDE";
}

void affichePlateau(Jeu *jeu){
    for (int i = -1; i<TAILLE_PLATEAU; i++){
        cout << i+1;
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


void calculScores (Jeu *jeu){
    jeu->joueur1.nbJetons = 0;
    jeu->joueur2.nbJetons = 0;

    for (int i = 0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if (jeu->plateau[i][j]->couleur == jeu->joueur1.couleur)
                jeu->joueur1.nbJetons ++;
            else if (jeu->plateau[i][j]->couleur == jeu->joueur2.couleur)
                jeu->joueur2.nbJetons ++;
        }
    }
}

void afficheScore(Jeu *jeu){
    calculScores(jeu);
    cout <<"SCORES : ";
    int nb1 = jeu->joueur1.nbJetons;
    int nb2 = jeu->joueur2.nbJetons;
    cout << nb1 <<" ";
    afficheCouleur(jeu->joueur1.couleur);
    cout <<"S VS "<< nb2<<" ";
    afficheCouleur(jeu->joueur2.couleur);
    cout<<"S "<<endl;
}

void afficheResultats(Jeu *jeu){
    afficheScore(jeu);
    if (jeu->joueur1.nbJetons > jeu->joueur2.nbJetons)
        cout <<"Le gagnant est "<<jeu->joueur1.nom<<" ! Bravo !"<<endl;
    else if (jeu->joueur1.nbJetons < jeu->joueur2.nbJetons)
        cout <<"Le gagnant est "<<jeu->joueur2.nom<<" ! Bravo !"<<endl;
    else 
        cout <<"Egalite ! Incroyable !"<<endl;
}

bool testCaseExiste(int l, int c){
    return (l >= 0 && l < TAILLE_PLATEAU && c >= 0 && c < TAILLE_PLATEAU);
}

int donneCouleurAdverse(int couleur){
    if (couleur == NOIR)
        return BLANC;
    else 
        return NOIR;
}

bool testPionAdverseDirection(Jeu *jeu, int couleur, int l, int c, int i){
    //coordonnees de la case suivante en regardant dans la direction i 
    int ligne = l + directions[i][0];
    int colonne = c + directions[i][1];

    if (testCaseExiste(ligne, colonne)){
        if (jeu->plateau[ligne][colonne]->couleur == donneCouleurAdverse(couleur)){
            if (test)
                cout <<"couleur adverse en "<<ligne<<" "<<colonne<<endl;
            return true;
        }
    }
    return false;
}

/*Retourne true si au moins un pion adverse autour de la position (l,c)*/
bool testPionAdverseAutour (Jeu *jeu, int couleur, int l, int c){
    for (int i=0; i<8; i++){
        if (testPionAdverseDirection(jeu, couleur, l,c,i)){
            if (test)
                cout<<"Pion adverse present autour de "<<l<<" "<<c<<endl;
            return true;
        }
    }
    return false;
}

int testGainDirection(Jeu *jeu, int couleur, int l, int c, int i, int g){
    if (test)
        cout <<"Test gain direction "<<i<<endl;
    
    int ligne = l + directions[i][0];
    int colonne = c + directions[i][1];

    if (g>=0 && testCaseExiste(ligne, colonne)){
        if (jeu->plateau[ligne][colonne]->couleur == donneCouleurAdverse(couleur)){
            g += testGainDirection(jeu, couleur, ligne, colonne, i, 0);
            if (g>=0) //donc si la case suivante dans la direction i n'est pas vide ou hors du plateau 
                return g +1; 
        } else if (jeu->plateau[ligne][colonne]->colonne == couleur)
            return 1;
    }

    return -1; 
}

int testGainCase(Jeu *jeu, int couleur, int l, int c){
    int gain = 0;
    for (int i=0; i<8; i++){
        if (testPionAdverseDirection(jeu, couleur, l, c, i)){
            if (test)
                cout << "Test gain en "<<l<<" "<<c<<endl;
            if (testGainDirection(jeu, couleur, l, c, i, 0)>=0)
                gain += testGainDirection(jeu, couleur, l, c, i, 0);
        }
    }
    return gain;
}

bool testGainPossible(Jeu *jeu, int couleur){
    for (int i =0; i<TAILLE_PLATEAU; i++){
        for (int j = 0; j<TAILLE_PLATEAU; j++){
            if (testGainCase(jeu, couleur, i, j)>0){
                if (test)
                    cout <<"gain de "<<testGainCase(jeu, couleur, i,j)<<" possible en"<<i<<" "<<j<<endl;
                return true;
            }
        }
    }
    return false;
}

bool testFinPartie(Jeu *jeu){
    if (!testGainPossible(jeu, NOIR) && !testGainPossible(jeu, BLANC))
        return true;
    else 
        return false;
}

void chercheCasesPotentielles (Jeu *jeu, Joueur *joueur){
    Liste *l = joueur->liste_cases_potentielles;
    videListe(l);

    for (int i=0; i<TAILLE_PLATEAU; i++){
        for (int j=0; j<TAILLE_PLATEAU; j++){
            if (jeu->plateau[i][j]->couleur==VIDE && testPionAdverseAutour(jeu,joueur->couleur,i,j))
                ajouteJeton(l,i,j);
        }
    }

    if (assistance){
        cout <<"Cases potentielles pour les ";
        afficheCouleur(joueur->couleur);
        cout<<endl; 

        for (int i = 0; i<joueur->liste_cases_potentielles->taille; i++){
            int l = joueur->liste_cases_potentielles->cases[i][0];
            int c = joueur->liste_cases_potentielles->cases[i][1];
            cout <<"("<<l+1<<","<<c+1<<") ";
            cout << testGainCase(jeu, joueur->couleur, l, c)<<" ; ";
        }
        cout <<endl;
    }
}

void chercheCasesJouables (Jeu *jeu, Joueur *joueur){
    Liste *l = joueur->liste_cases_jouables;
    videListe(l);
    for (int i=0; i<joueur->liste_cases_potentielles->taille; i++){
        int ligne = joueur->liste_cases_potentielles->cases[i][0];
        int colonne = joueur->liste_cases_potentielles->cases[i][1];
        if (testGainCase(jeu, joueur->couleur, ligne, colonne) > 0)
            ajouteJeton(l, ligne, colonne);
    }

    if (assistance){
        cout << "Cases jouables pour les ";
        afficheCouleur(joueur->couleur);
        cout<<endl;
        afficheListe(l);
    }
}

void retournePionsDirection (Jeu *jeu, int couleur, int l, int c, int i){
    if (jeu->plateau[l][c]->couleur == donneCouleurAdverse(couleur)){
        jeu->plateau[l][c]->couleur = couleur;
        retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);
    }
}

void retournePions (Jeu *jeu, int couleur, int l, int c){
    for(int i=0; i<8; i++){
        if (testGainDirection(jeu,couleur,l,c,i,0)>0)
            retournePionsDirection(jeu, couleur, l+directions[i][0], c+directions[i][1], i);
    }
}

void joue(Jeu *jeu, Joueur *j, int l, int c){
    jeu->plateau[l][c]->couleur = j->couleur;
    retournePions(jeu, j->couleur, l, c);
}

void tour (Jeu *jeu, Joueur *j){
    cout<<"Tour du joueur "<<j->nom<<" (";
    afficheCouleur(j->couleur);
    cout<<") "<<endl;

    chercheCasesPotentielles(jeu, j);
    chercheCasesJouables(jeu, j);

    if (j->liste_cases_jouables->taille>0){
        int ligne = 0, colonne = 0;
        do {
            cout << "Choisi une case (ligne, colonne) : ";
            cin >> ligne >> colonne;
            ligne --, colonne --; 
        } while (!testPresenceJeton(j->liste_cases_jouables, ligne, colonne));

        joue(jeu,j,ligne,colonne);
        affichePlateau(jeu);
        afficheScore(jeu);
    } else {
        cout <<"Aucun coup possible"<<endl;
    }
}

void partie (){
    cout <<"LANCEMENT DE LA PARTIE"<< endl;
    test = false;

    char temp;
    cout<<"Jouer avec une aide ? (y/n)";
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

int main(){
    partie();
    return 0;
}