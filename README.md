# algebre_lineaire

Ceci est ma version du projet pour la matière Algebre Lineaire Appliqué du semestre 4 (2è année de licence informatique).

## Prérecquis
```
git clone 'lien_du_clonage'
```

## Pour faire les tests

Vous trouverez un fichier "tp1.c" dans ce git. Il contient le main ainsi que le code source de mes fonctions, et réalise un affichage des réponses conforme au sujet du projet.

Pour le compiler, rien de difficile :
```
gcc -Wall -Wextra -Werror tp1.c -o main
```
(Les flags ne sont pas nécessaires, mais autant compiler avec)

Pour le lancer, et voir le résultat sur la console :
```
./main
```

## Quels tests sont effectués ?

Ceux qui sont demandés dans le projet. En outre, l'addition de deux matrices, vérifier si une matrice est carré, symétrique, calculer un déterminant, utilisation du pivot de Gauss, etc ...


## Mon encodage

Attention ! Si vous voulez changer le code du main pour d'autres affichages, vous pouvez retrouver le code source de toutes les fonctions un peu plus haut dans le fichier tp1.c. Mais pour mes fonctions, j'ai choisi de commencer ma matrice à la case (1,1), soit la case [1,1] du tableau dans la structure. Pour accéder au premier élément de ma matrice, ce sera donc (1,1).

Tout le code source C de mes fonctions et mon main sont dans tp1.c. Le main commence exactement à la ligne 716.


## AUTEUR

* **Joaquim Ventura**
