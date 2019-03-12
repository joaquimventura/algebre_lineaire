#include <stdio.h>
#include <stdlib.h>

typedef float E;
typedef struct matrix
{
	E * mat;
	int nb_rows, nb_colums;
} Matrix;


/*
	Role: Fonction qui créer une nouvelle matrice.
	
	Entrée: Un nombre de ligne (int) et de colonne (int).
	
	Sortie: Une structure Matrix (définie plus haut).
			-> Si le nombre de ligne et de colonne ne sont pas positifs,
			une matrice avec nombre ligne et colonne = 0 est créée.
*/
Matrix newMatrix(int rows, int column)
{
	Matrix res;
	int i,j;

	if((rows > 0) && (column > 0))
	{
		res.nb_rows = rows;
		res.nb_colums = column;
		res.mat = malloc(rows * column * sizeof(E));

		for(i=1; i <= rows; i++)
		{
			for(j=1; j <= column; j++)
			{
				res.mat[(i - 1) * res.nb_colums + j - 1] = 0.;
			}
		}
	}
	else
	{
		res.nb_rows = 0;
		res.nb_colums = 0;
		res.mat = malloc(0 * sizeof(E));
	}
	return res;
}


/*
	Role: Fonction qui récupère un élément dans la matrice. Si accès à une valeur non
		comprise dans la matrice, on quitte le programme avec un message d'erreur.
	
	Entrée: Une matrice (Matrix), un numéro de ligne (int) et de colonne (int).

	Exemple: si on veut accéder à l'élément en position(1,1) de la matrice (premier
			élément de la matrice), on fait getElt(A,1,1);
	
	Sortie: L'élément qu'on cherche à récupérer.
*/
E getElt(Matrix m, int row, int column)
{
	if((row <= m.nb_rows) && (column <= m.nb_colums) && (row > 0) && (column > 0))
		return m.mat[(row - 1) *  m.nb_colums + column - 1];
	else
	{
		fprintf(stderr,"Erreur getElt() -> accès à une valeur en dehors du tableau");
		exit(1);
	}
}


/*
	Role: Fonction qui modifie la valeur dans la case choisie de la matrice.
	
	Entrée: Une matrice (Matrix), un numéro de ligne (int) et de colonne (int), une
			nouvelle valeur (E).
	
	Sortie: Rien, l'élément est directement changé dans la matrice, sans recopie.
*/
void setElt(Matrix m, int row, int column, E val)
{
	if((row <= m.nb_rows) && (column <= m.nb_colums) && (row > 0) && (column > 0))
		m.mat[(row - 1) * m.nb_colums + column - 1] = val;
}


/*
	Role: Fonction qui supprime l'espace mémoire d'une matrice.
	
	Entrée: La matrice (Matrix) à supprimer.
	
	Sortie: Rien.
*/
void deleteMatrix(Matrix m) {
	free(m.mat);
}


/*
	Role: Fonction qui test si une matrice est carré.
	
	Entrée: Une matrice (Matrix).
	
	Sortie: Un int, 1 si la matrice est carré, 0 sinon.
*/
int isSquare(Matrix A)
{
	return (A.nb_rows == A.nb_colums);
}


/*
	Role: Fonction qui test si une matrice est symétrique.
	
	Entrée: Une matrice (Matrix).
	
	Sortie: Un int, 1 si la matrice est symétrique, 0 sinon.
*/
int isSymetric(Matrix A)
{
	int i,j;
	if(isSquare(A) == 1)
	{
		for(i=1; i <= A.nb_rows; i++)
		{
			for(j=i; j <= A.nb_colums; j++)
			{
				if(getElt(A,i,j) != getElt(A,j,i))
					return 0;
			}
		}
		return 1; // aucune erreur de symétrie, la matrice est symétrique
	}
	else
		return 0; // faux, matrice non symétrique
}


/*
	Role: Fonction qui calcul la transpose d'une matrice.
	
	Entrée: Une matrice (Matrix).
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à la transposée de la matrice en
			argument.
*/
Matrix transpose(Matrix A)
{
	int i,j;
	Matrix resultat = newMatrix(A.nb_colums,A.nb_rows);
	for(i=1;i<= resultat.nb_rows; i++)
	{
		for(j=1; j <= resultat.nb_colums; j++)
		{
			setElt(resultat,i,j,getElt(A,j,i));
		}
	}
	return resultat;
}


/*
	Role: Fonction qui calcul l'addition de deux matrices.
	
	Entrée: Deux matrices (Matrix).
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à l'addition des deux matrices en
			argument.
*/
Matrix addition(Matrix A, Matrix B)
{
	Matrix resultat;
	int i,j;
	if((A.nb_rows == B.nb_rows) && (A.nb_colums == B.nb_colums)) // test si addition possible
	{
		resultat = newMatrix(A.nb_rows,A.nb_colums);
		for(i=1; i <= resultat.nb_rows; i++)
		{
			for(j=1; j <= resultat.nb_colums; j++)
			{
				setElt(resultat,i,j,getElt(A,i,j) + getElt(B,i,j));
			}
		}
	}
	
	else // si addition non possible, on renvoie une matrice "nulle", carré de taille 0
	{
		resultat = newMatrix(0,0);
	}

	return resultat;
}


/*
	Role: Fonction qui affiche une matrice (évite de devoir écrire cette boucle pour chaque
			affichage dans le main).
	
	Entrée: Une matrice (Matrix).
	
	Sortie: Rien, affichage sur la sortie standart de la matrice sous forme visuel.
*/
void afficheMatrice(Matrix A)
{
	int i,j;

	if((A.nb_rows == 0) && (A.nb_colums == 0))
		printf("Matrice Vide (ligne et colonne = 0) !\n");
	else
	{
		for(i=1; i <= A.nb_rows; i++)
		{
			for(j=1; j <= A.nb_colums; j++)
			{
				printf("%f ",getElt(A,i,j));
			}
			printf("\n");
		}
	}
	printf("\n");
}


/*
	Role: Fonction qui calcul la multiplication de deux matrices.
	
	Entrée: Deux matrices (Matrix).
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à la multiplication des deux matrices
			en argument.
*/
Matrix multiplication(Matrix A, Matrix B)
{
	Matrix resultat;
	int i,j,k,test;
	if(A.nb_colums == B.nb_rows) // test si la multiplication est possible
	{
		resultat = newMatrix(A.nb_rows,B.nb_colums);
		for(i=1; i<=A.nb_rows; i++)
		{
			for(j=1; j<=B.nb_colums; j++)
			{
				test=0;
				for(k=1; k<=B.nb_colums; k++)
				{
					test += getElt(A,i,k) * getElt(B,k,j);
				}
				setElt(resultat,i,j,test);
			}
		}
	}
	else // si la multiplication est impossible
	{
		resultat = newMatrix(0,0); // création d'une matrice "nulle", carré de taille 0
	}

	return resultat;
}


/*
	Role: Fonction qui multiplie chaque coefficient de la matrice par un scalaire.
	
	Entrée: Un scalaire multiplicatif (E) et une matrice (Matrix).
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à la multiplication de chaque
			coefficient de la matrice en argument par le scalaire en argument.
*/
Matrix mult_scalaire(E scalaire, Matrix A)
{
	Matrix resultat = newMatrix(A.nb_rows,A.nb_colums);
	int i,j;
	E test;
	// pour faciliter les calculs, je suppose que ma matrice est non nulle,
	// ie elle a au moins une ligne et une colonne.
	for (i=1; i<=A.nb_rows; i++)
	{
		for(j=1; j<=A.nb_colums; j++)
		{
			test = scalaire * getElt(A,i,j);
			setElt(resultat,i,j,test);
		}
	}

	return resultat;
}


/*
	Role: Fonction qui remplace un block d'une matrice par une autre matrice.
	
	Entrée: Une première matrice (Matrix), un numéro de ligne (int) et un numéro de colonne
			(int) qui indiquent à partir de où je dois modifier ma première matrice, et une
			autre matrice (Matrix) par laquelle on va remplacer dans la première matrice.
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à la première matrice en argument,
			avec un block changé, qui correspond à la deuxième matrice (Matrix), à partir
			d'une certaine ligne et colonne.
*/
Matrix setMatrixBlock(Matrix A, int ligne, int colonne, Matrix B)
{
	Matrix resultat;
	int i,j,a,b;

	// je test d'abord si j'ai la place de mettre la matrice B dans la matrice A selon
	// les indices donnés en argument
	if(((ligne + B.nb_rows - 1) > A.nb_rows) || ((colonne + B.nb_colums - 1) > A.nb_colums))
	{
		resultat = newMatrix(0,0); // si je ne peux pas, je renvoie une matrice nulle, carré
									// de taille 0
		printf("Impossible de changer ce block de la matrice, manque de place dans la matrice !\n");
	}
	else
	{
		resultat = newMatrix(A.nb_rows,A.nb_colums);
		for (i=1; i<=A.nb_rows; i++)
		{
			for(j=1; j<=A.nb_colums; j++)
			{
				setElt(resultat,i,j,getElt(A,i,j));
			}
		}
		// sinon je recopie d'abord  ma matrice A dans ma matrice résultat

		for (a=1; a<=B.nb_rows; a++)
		{
			for(b=1; b<=B.nb_colums; b++)
			{
				setElt(resultat,a+ligne-1,b+colonne-1,getElt(B,a,b));
			}
		}
		// et je remplace par la matrice B à partir de la ligne et de la colonne indiqué en
		// argument.
	}
	return resultat;
}


/*
	Role: Fonction qui renvoie un certain block d'une matrice.
	
	Entrée: Une matrice (Matrix) dont on souhaite extraire un certain block, un début de ligne
			(int), et une fin de ligne (int), ainsi qu'un début de colonne (int), et une fin
			de colonne (int).
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à un block seulement de la matrice
			en argument. Si ma matrice est A(3,3) et que je souhaite retirer un block carré
			de taille 2 qui commence en A(1,1) et donc qui fini en A(2,2), alors ma matrice
			résultat sera une matrice de taille 2 qui contient A(1,1), A(1,2), A(2,1)
			et A(2,2).
*/
Matrix getMatrixBlock(Matrix A, int ligne_debut, int colonne_debut, int nb_ligne, int nb_colonne)
{
	Matrix resultat;
	int i,j;

	// je test d'abord si je peux extraire le block souhaité dans la matrice en argument
	if((ligne_debut > 0) && (colonne_debut > 0) && (nb_ligne > 0) && (nb_colonne > 0) &&
		((ligne_debut + nb_ligne) <= A.nb_rows) && ((colonne_debut + nb_colonne) <= A.nb_colums))
	{
		// si c'est le cas, je recopie ce block dans une nouvelle matrice
		resultat = newMatrix(nb_ligne,nb_colonne);
		for (i=1; i<=nb_ligne; i++)
		{
			for(j=1; j<=nb_colonne; j++)
			{
				setElt(resultat,i,j,getElt(A,i+ligne_debut-1,j+colonne_debut-1));
			}
		}
	}
	else
	{
		// sinon je créer une matrice nulle, carré de taille 0
		resultat = newMatrix(0,0);
		printf("Erreur getMatrix, un paramètre est eronné !\n");
	}

	return resultat;
}


/*
	Role: Fonction qui extrait une ligne et une colonne d'une matrice.
	
	Entrée: Une matrice (Matrix), un numéro de ligne (int) et de colonne (int) à extraire.
	
	Sortie: Une nouvelle matrice (Matrix), qui correspond à la matrice en argument moins
			la ligne et la colonne qu'on voulait enlever, fonction très utile pour calculer
			un determinant selon une fonction récursive.
*/
Matrix extraction(Matrix A, int i, int j)
{
	int a,b,test_ligne = 0,test_colonne = 0;
	Matrix resultat = newMatrix(A.nb_rows - 1,A.nb_colums - 1);
	
	// pour faciliter les calculs, j'ai supposer que ma ligne et ma colonne était bien comprises
	// dans ma matrice, ie dans une matrice (3,3), je ne vais pas essayer de retirer la 4e ligne
	// et la 4e colonne, même si normalement il faudrait le tester, mais comme je n'utilise cette
	// fonction que dans ma formule de récursivité de calcul du déterminant, je n'essaie jamais
	// de retirer une ligne ou une colonne qui n'existeraient pas dans ma matrice !

	for (a=1; a<=resultat.nb_rows; a++)
	{
		if(a == i)
			test_ligne = 1;
		
		for(b=1; b<=resultat.nb_colums; b++)
		{
			if(b == j)
				test_colonne = 1;

			if(((test_ligne + a) <= A.nb_rows) && ((test_colonne + b) <= A.nb_colums))
				setElt(resultat,a,b,getElt(A,test_ligne + a, test_colonne + b));
		}	
		test_colonne = 0;
	}

	return resultat;

}


/*
	Role: Fonction qui calcul la puissance d'un nombre.
	
	Entrée: Un nombre (int) et sa puissance souhaitée (int).
	
	Sortie: Le nombre à sa puissance.
		-> fonction utile pour le déterminant récursif !
*/
int puissance(int a, int n)
{
	int i, resultat=a;

	for(i=1; i<n; i++)
		resultat *= a;

	return resultat;
}


/*
	Role: Fonction qui calcul le determinant d'une matrice selon la méthode récursive.
	
	Entrée: Une matrice (Matrix) carrée, même si le test est effectuée pour ne pas faire
			de faux calculs !
	
	Sortie: La valeur (E) du déterminant de la matrice, calculéee selon la méthode récursive.
*/
E determinant(Matrix A)
{
	int somme = 0, i;
	
	// je test directement si la matrice est carré ou non
	if(!(isSquare(A)))
		printf("Matrice non carré, calcul determinant impossible !\n");
	
	else
	{
		// Si elle l'est, on calcul alors notre déterminant selon la méthode récursive,

		// Si ma matrice est carré de taille 2, on a directement la formule suivante :
		if(A.nb_rows == 2)
			somme = getElt(A,1,1) * getElt(A,2,2) - getElt(A,2,1) * getElt(A,1,2);
		else
		{
			// sinon on lance une récursion, en prenant garde de changer le signe du
			//coefficient multiplicateur quand c'est nécessaire !
			for(i=1; i<=A.nb_rows; i++)
			{
				Matrix test = extraction(A,1,i);
				somme += puissance(-1,i+1) * (getElt(A,1,i) * determinant(test));
				deleteMatrix(test);
			}
		}
	}

	return somme;
}

/*

Attention, ces fonctions ne sont pas utilisées dans ce programme, mais étaient nécessaire
pour une fonction du projet que j'ai écris d'une autre façon.


void mult_ligne_scalaire(Matrix A, int ligne, int scalaire)
{
	int j;

	if(ligne <= A.nb_rows)
	{
		for(j=1; j <= A.nb_colums; j++)
		{
			setElt(A,ligne,j, getElt(A,ligne,j) * scalaire);
		}
	}
}
Cette fonction multiplie seulement une ligne d'une matrice par un scalaire, ressemble
à la multiplication d'une matrice par un scalaire.


void permuter_ligne(Matrix A, int ligne1, int ligne2)
{
	int j;
	E temp;

	if((ligne1 <= A.nb_rows) && (ligne2 <= A.nb_rows))
	{
		for(j=1; j <= A.nb_colums; j++)
		{
			temp = getElt(A,ligne1,j);
			setElt(A,ligne1,j,getElt(A,ligne2,j));
			setElt(A,ligne2,j,temp);
		}
	}
}
Alors que celle-ci permute deux lignes d'une matrice.

Ces deux fonctions ont été testé et fonctionne correctement si jamais vous voulez les
réutiliser en gardant la même structure de données que moi !
*/


/*
	Role: Fonction qui simule un pivot de gauss (Triangularisation supérieure de la matrice).
	
	Entrée: La matrice (Matrix) qu'on souhaite triangularisée supérieure.
	
	Sortie: Une nouvelle matrice (Matrix) qui correspond à la triangularisation supérieure
			de la matrice. Le sujet du projet stipulait qu'on devait pouvoir choisir entre
			un triangle supérieur ou inférieur, mais ne trouvant pas comment faire, ma fonction
			ne fait que le triangle supérieur !!!
*/
void pivotDeGauss(Matrix A)
{
	int i,j,k;
	E p,q;

	if(isSquare(A)) // Je ne triangularise que si la matrice est carré
	{
		for(k=1; k <= A.nb_rows; k++)
		{
			p = getElt(A,k,k);

			for(i=k+1; i <= A.nb_rows; i++)
			{
				q = getElt(A,i,k);
				setElt(A,i,k,0.);

				for(j=k+1; j <= A.nb_colums; j++)
				{
					setElt(A,i,j,(getElt(A,i,j) - (getElt(A,k,j) * (q / p))));
				}
			}
		}
	}
	else
		printf("Matrice non carré, pivot de gauss ne peut être appliqué !\n");
}


/*
	Role: Fonction qui calcul le rang d'une matrice triangularisée.

	Entrée: Une matrice (Matrix) qu'on aura au préalable triangularisée avec le pivot de gauss.
	
	Sortie: Le rang (int) de la matrice (Nombre minimale de vecteurs lignes ou colonnes linéairement
			indépendants).
*/
int rang_matrice(Matrix A)
{
	int i,resultat = 0;

	// étant triangularisée, si deux lignes venaient à être les mêmes, on aurait une ligne de
	// 0, donc je test si sur la diagonale j'ai un 0 ou non. Si j'en ai 1, c'est une ligne
	// en trop.
	for(i=1; i<= A.nb_rows; i++)
	{
		if(getElt(A,i,i) != 0)
			resultat++;
	}

	return resultat;
}


/*
	Role: Fonction qui calcul le determinant d'une matrice triangularisée.

	Entrée: Une matrice (Matrix) qu'on aura au préalable triangularisée avec le pivot de gauss.
	
	Sortie: La valeur (E) du déterminant de la matrice triangularisée.
*/
E determinant_gauss(Matrix A)
{
	int somme = 0;
	if(!(isSquare(A))) // je test d'abord si la matrice est carré
		printf("Matrice non carré, calcul determinant impossible !\n");
	
	else
	{
		// si elle l'est, comme elle est triangularisée supérieure, je peux développer
		// d'après la première colonne à chaque étape (les 0 n'étant pas développé).

		// si elle est de taille 2, on connaît la formule suivante :
		if(A.nb_rows == 2)
			somme = getElt(A,1,1) * getElt(A,2,2) - getElt(A,2,1) * getElt(A,1,2);
		else
		{
			// sinon on développe selon la première colonne à chaque fois.
			Matrix test = extraction(A,1,1);
			somme += getElt(A,1,1) * determinant(test);
			deleteMatrix(test);
		}
	}

	return somme;
}


/*
	Role: Fonction qui transforme une matrice en matrice identité (utile pour la décomposition
			en L U ci-après).

	Entrée: Une matrice (Matrix).
	
	Sortie: Rien, on modifie directement la matrice en argument.
*/
void matrixIdentite(Matrix A)
{
	int i,j;
	if(!isSquare(A)) // Si la matrice n'est pas carré, je ne peux pas la modifier en matrice identité
		printf("Matrix impossible à modifier en matrix identite !\n");
	else
	{
		// sinon
		for(i=1;i<=A.nb_rows;i++)
		{
			for(j=1;j<=A.nb_colums;j++)
			{
				if(i==j) // je place un 1. sur chaque diagonale
					setElt(A,i,j,1.);
				else // et un 0. partout ailleurs
					setElt(A,i,j,0.);
			}
		}
	}
}


/*
	Role: Fonction qui recopie le contenu d'une matrice dans une autre.

	Entrée: Une matrice (Matrix) dont on souhaite recopier le contenu dans une autre matrice
			en argument (Matrix).
	
	Sortie: Rien, on modifie direment la deuxième matrice (Matrix) en argument en remplacant
			son contenu par le contenu de la première matrice (Matrix) en argument.
*/
void recopie_matrix(Matrix A, Matrix B) // recopie le contenu de la matrix A dans la matrix B
{
	int i,j;

	// je test d'abord si je peux faire une telle recopie
	if((A.nb_rows == B.nb_rows) && (A.nb_colums == B.nb_colums))
	{
		for(i=1;i<=A.nb_rows;i++)
		{
			for(j=1;j<=A.nb_colums;j++)
			{
				setElt(B,i,j,getElt(A,i,j));
			}
		}
	}
	else
		printf("Recopie matrix impossible !\n");
}


/*
	Role: Fonction qui décompose en L et U une matrice.

	Entrée: Une matrice (Matrix) qu'on souhaite décomposée en L et U. Egalement une matrice (Matrix)
			qui recevra le contenu de la matrice L et une autre matrice (Matrix) qui recevra le contenu
			de la matrice U.
	
	Sortie: Rien, on modifie directement la matrice L et U en argument.
*/
void decomposition_L_U(Matrix A, Matrix L, Matrix U)
{
	int i,j,k;
	E p,q;

	matrixIdentite(L);
	recopie_matrix(A,U);

	for(k=1;k<=A.nb_rows;k++)
	{
		p = getElt(U,k,k);
		for(i=k+1;i<=A.nb_rows;i++)
		{
			q = getElt(U,i,k);
			setElt(U,i,k,0.);
			setElt(L,i,k, q / p);
			for(j=k+1;j<=A.nb_rows;j++)
			{
				setElt(U,i,j, getElt(U,i,j) - (getElt(U,k,j) * (q / p)));
			}
		}
	}
}


int main() {

	// QUESTION 1
	printf("QUESTION 1 :\n");
	printf("\n");

	// Pour les besoins du projet, je créer la matrice A
	Matrix A = newMatrix(3,3);

	setElt(A,1,1,1.);
	setElt(A,1,2,3.);
	setElt(A,1,3,5.);
	setElt(A,2,1,2.);
	setElt(A,2,2,5.);
	setElt(A,2,3,1.);
	setElt(A,3,1,-1.);
	setElt(A,3,2,-4.);
	setElt(A,3,3,-3.);

	// Et la matrice B.
	Matrix B = newMatrix(2,3);

	setElt(B,1,1,1.);
	setElt(B,1,2,4.);
	setElt(B,1,3,2.);
	setElt(B,2,1,2.);
	setElt(B,2,2,5.);
	setElt(B,2,3,1.);

	printf("Matrice A :\n");
	afficheMatrice(A);
	printf("Matrice B :\n");
	afficheMatrice(B);

	
	// QUESTION 2
	printf("QUESTION 2 :\n");
	printf("\n");

	if(isSquare(A))
		printf("Matrice A carré\n");
	else
		printf("Matrice A non carré\n");
	printf("\n");

	if(isSquare(B))
		printf("Matrice B carré\n");
	else
		printf("Matrice B non carré\n");
	printf("\n");


	if(isSymetric(A))
		printf("Matrice A symétrique\n");
	else
		printf("Matrice A non symétrique\n");
	printf("\n");

	if(isSymetric(B))
		printf("Matrice B symétrique\n");
	else
		printf("Matrice B non symétrique\n");
	printf("\n");


	// QUESTION 3
	printf("QUESTION 3 :\n");
	printf("\n");

	Matrix transposedA = transpose(A);
	printf("Transpose de A :\n");
	afficheMatrice(transposedA);
	printf("\n");

	Matrix transposedB = transpose(B);
	printf("Transpose de B :\n");
	afficheMatrice(transposedB);
	printf("\n");


	// QUESTION 4
	printf("QUESTION 4 :\n");
	printf("\n");

	Matrix AplusB = addition(A,B);
	if((AplusB.nb_rows != 0) && (AplusB.nb_colums != 0))
	{	
		printf("Matrice A + Matrice B possible :\n");
		afficheMatrice(AplusB);
	}
	else
		printf("Matrice A + Matrice B impossible !\n");
	printf("\n");


	Matrix BplusA = addition(B,A);
	if((BplusA.nb_rows != 0) && (BplusA.nb_colums != 0))
	{	
		printf("Matrice B + Matrice A possible :\n");
		afficheMatrice(BplusA);
	}
	else
		printf("Matrice B + Matrice A impossible !\n");
	printf("\n");


	Matrix AfoisB = multiplication(A,B);
	if((AfoisB.nb_rows == 0) && (AfoisB.nb_colums == 0))
		printf("Matrice A * Matrice B impossible !\n");
	else
	{
		printf("Matrice A * Matrice B possible :\n");
		afficheMatrice(AfoisB);
	}
	printf("\n");


	Matrix BfoisA = multiplication(B,A);
	if((BfoisA.nb_rows == 0) && (BfoisA.nb_colums == 0))
		printf("Matrice B * Matrice A impossible !\n");
	else
	{
		printf("Matrice B * Matrice A possible :\n");
		afficheMatrice(BfoisA);
	}
	printf("\n");


	Matrix AtransposedFoisB = multiplication(transposedA,B);
	if((AtransposedFoisB.nb_rows == 0) && (AtransposedFoisB.nb_colums == 0))
		printf("Matrice Transposed A * Matrice B impossible !\n");
	else
	{
		printf("Matrice Transposed A * Matrice B possible :\n");
		afficheMatrice(AtransposedFoisB);
	}
	printf("\n");


	Matrix BtransposedFoisA = multiplication(transposedB,A);
	if((BtransposedFoisA.nb_rows == 0) && (BtransposedFoisA.nb_colums == 0))
		printf("Matrice Transposed B * Matrice A impossible !\n");
	else
	{
		printf("Matrice Transposed B * Matrice A possible :\n");
		afficheMatrice(BtransposedFoisA);
	}
	printf("\n");


	Matrix AplusTransposedA = addition(A,transposedA);
	if((AplusTransposedA.nb_rows != 0) && (AplusTransposedA.nb_colums != 0))
	{	
		printf("Matrice A + Matrice Transposed A possible :\n");
		afficheMatrice(AplusTransposedA);
	}
	else
		printf("Matrice A + Matrice Transposed A impossible !\n");
	printf("\n");


	Matrix Afois5 = mult_scalaire(5.,A);
	printf("5 * Matrice A :\n");
	afficheMatrice(Afois5);
	printf("\n");


	Matrix Bfois3 = mult_scalaire(3,B);
	printf("3 * Matrice B :\n");
	afficheMatrice(Bfois3);
	printf("\n");


	// QUESTION 5
	printf("QUESTION 5 :\n");
	printf("\n");

	if(isSymetric(AplusTransposedA))
		printf("Matrice A + Transposed A symétrique\n");
	else
		printf("Matrice A + Transposed A non symétrique\n");
	printf("\n");


	// QUESTION 6
	printf("QUESTION 6 :\n");
	printf("\n");

	Matrix C = setMatrixBlock(A,1,1,B);
	afficheMatrice(C);
	printf("\n");


	// QUESTION 7
	printf("QUESTION 7 :\n");
	printf("\n");

	Matrix D = getMatrixBlock(A,1,1,2,2);
	afficheMatrice(D);
	printf("\n");


	// QUESTION 8
	printf("QUESTION 8 :\n");
	printf("\n");

	printf("Determinant de A : %f\n",determinant(A));
	printf("\n");

	printf("Determinant de B impossible à calculer (à noter que la fonction renvoie quand même %f)\n",determinant(B));
	printf("\n");


	// QUESTION 9
	printf("QUESTION 9 :\n");
	printf("(TOUTE CETTE PARTIE EST EFFECTUEE AVEC LES PIVOTS DE GAUSS !\n");
	printf("\n");

	pivotDeGauss(A);

	int rangA = rang_matrice(A);
	printf("Le rang de A : %d\n",rangA);
	printf("\n");

	pivotDeGauss(B);

	int rangB = rang_matrice(B);
	printf("Le rang de B : %d\n",rangB);
	printf("\n");


	// QUESTION 10
	printf("QUESTION 10 :\n");
	printf("\n");

	pivotDeGauss(AplusTransposedA);
	printf("Determinant de A triangulaire supérieure + sa transposée : %f\n",determinant_gauss(AplusTransposedA));
	printf("\n");

	printf("Les questions 11 et 12 n'ont pas été traités dans ce projet !\n");
	printf("\n");

	// QUESTION 13
	printf("QUESITON 13 :\n");
	printf("\n");
	
	Matrix L = newMatrix(3,3);
	Matrix U = newMatrix(3,3);

	// Comme ma fonction pivot de Gauss modifie directement ma matrice, je ré-initialise
	// les valeurs de ma matrice A.
	setElt(A,1,1,1.);
	setElt(A,1,2,3.);
	setElt(A,1,3,5.);
	setElt(A,2,1,2.);
	setElt(A,2,2,5.);
	setElt(A,2,3,1.);
	setElt(A,3,1,-1.);
	setElt(A,3,2,-4.);
	setElt(A,3,3,-3.);

	decomposition_L_U(A,L,U);

	printf("Matrice A :\n");
	afficheMatrice(A);

	printf("Matrice L :\n");
	afficheMatrice(L);

	printf("Matrice U :\n");
	afficheMatrice(U);


	deleteMatrix(A);
	deleteMatrix(B);
	deleteMatrix(AfoisB);
	deleteMatrix(transposedA);
	deleteMatrix(transposedB);
	deleteMatrix(AplusB);
	deleteMatrix(BplusA);
	deleteMatrix(BfoisA);
	deleteMatrix(AtransposedFoisB);
	deleteMatrix(BtransposedFoisA);
	deleteMatrix(AplusTransposedA);
	deleteMatrix(Afois5);
	deleteMatrix(Bfois3);
	deleteMatrix(C);
	deleteMatrix(D);
	deleteMatrix(L);
	deleteMatrix(U);

	return 0;
}