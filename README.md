# PROG-Reversi

# PROG-Reversi

Objectif : 
pouvoir jouer à deux au reversi dans le terminal (pas d'interface graphique)

Deadline : 
janvier 2021 

Livrables : 
- les fichiers cpp et un makefile (compilable sur machine de l'université)
- rapport pdf (3p)
- video de présentation de la compilation et exécution, avec test des principales fonctionnalités 

Contraintes : 
- utiliser structures : jeton, joueur, jeu 
- cin et cout 
- boucles if for while 
- plusieurs modules 
- pointeurs 
- liste chainee 

Contenu du jeu : 
- accueil
  - demander mode de jeu (multi ou solo contre IA)
      - noms des/du joueur(s)
  - lance partie 
- état initial 
  - un plateau 64*64 
  - pions au centres
- pendant le jeu 
  - affiche nom du joueur dont c'est le tour, et nombre de pions de sa couleur sur le plateau 
  - demander la case que le joueur veut 
  - vérifier si la case est valide (si capture au moins un jeton adverse)
    - si nom, demander une autre case ou lui sugérer les cases valides 
    - si oui, affiche le plateau modifié et passer au tour de l'autre joueur 
- fin de partie (si le plateau est rempli ou que le dernier joueur ne peut pas placer de pions)
  - afficher nom du vainqueur 
