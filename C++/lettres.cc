#include <iostream>
using namespace std;

void espaces(int decalage)
{
  for(int i(0); i < decalage; ++i) {
    cout << ' ';
  }
}

void barre_horizontale(int longueur, int decalage)
{
  espaces(decalage);
  for(int i(0); i < longueur; ++i) {
    cout << '-';
  }
}

void barre_verticale(int decalage)
{
  espaces(decalage);
  cout << '|';
}

void barre_a_droite(int decalage)
{
  espaces(decalage);
  cout << '/';
}

void barre_a_gauche(int decalage)
{
  espaces(decalage);
  /* Attention, cette ligne affiche bien UN SEUL caractere \ !  *
   * En C++, il faut repeter deux fois le caractere \ pour en   *
   * n'afficher qu'un seul.                                     */
  cout << '\\';
}

void fin_ligne()
{
  cout << endl;
}

void affiche_N(int hauteur)
{
  for(int i(0); i < hauteur; ++i) {
    barre_verticale(0);
    barre_a_gauche(i);
    barre_verticale(hauteur-i-1);
    fin_ligne();
  }
}

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
void affiche_L(int hauteur)
{
	for(int i(0); i < hauteur; ++i) {
		if (i<hauteur-1) {barre_verticale(0);}
		else {barre_horizontale(7,0);}
    fin_ligne();
  }
	}
void affiche_O(int hauteur)
{
	for(int i(0); i < hauteur; ++i) {
		if (i==0 or i==hauteur-1) {barre_horizontale(6,1);}
		if (i>0 and i<hauteur-1) {barre_verticale(0);barre_verticale(7);}
    fin_ligne();
  }
	}
void affiche_Z(int hauteur)
{
	for(int i(0); i < hauteur; ++i) {
		if (i==0 or i==hauteur-1) {barre_horizontale(7,0);}
		else {barre_a_droite(hauteur-i);}
    fin_ligne();
  }
	}
void affiche_A(int hauteur)
{
	for(int i(0); i < hauteur; ++i) {
        barre_a_droite(6-i);
        if (i==3) {barre_horizontale(6,0);barre_a_gauche(0);}
        else {barre_a_gauche(2*i);}
    fin_ligne();
  }
	}
/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  const int hauteur(7);
  affiche_L(hauteur);
  fin_ligne();
  affiche_O(hauteur);
  fin_ligne();
  affiche_Z(hauteur);
  fin_ligne();
  affiche_A(hauteur);
  return 0;
}
