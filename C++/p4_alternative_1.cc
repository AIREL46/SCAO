#include <iostream>
using namespace std;
#include <vector>
#include <array>
#include <string>
enum Couleur{vide, rouge, jaune};
typedef array<array<Couleur,7>,6> Grille;
void initialise(Grille& grille);
void affiche(const Grille& grille);
bool joue(Grille& grille, size_t colonne, Couleur couleur);
int main()
{
	
	Grille grille;
	initialise(grille);
	affiche(grille);
	for(int i(0); i<10; ++i){
		bool valide(joue(grille, 3, rouge));
		if(not valide){
			cout <<"Impossible d'ajouter un pion sur cette colonne"<<endl;
			}
			affiche(grille);
		}
	return 0;
}
void initialise(Grille& grille){
	for (auto &ligne : grille){
		for (auto &kase : ligne){
			kase=vide;
			}
		}
	}
void affiche(const Grille& grille)
	{
	cout <<endl;
	for(auto ligne : grille)
	{
		cout <<" |";
		for (auto kase : ligne)
		{
			if (kase==vide){cout <<' ';}
			else if(kase==rouge){cout <<'0';}
			else {cout <<'X';}
		cout <<'|';}
		cout <<endl;
		}
		cout <<'=';
		for(size_t i(1); i<=grille[0].size(); ++i)
		{cout <<'='<<i;}
		cout <<"==";
		cout <<endl<<endl;
	}
bool joue(Grille& grille, size_t colonne, Couleur couleur){
	if(colonne>6){cout <<"La colonne nest pas valide"<<endl;return false;}
	//Sila colonne est pleine le coup n'est pas valide
	if(grille[0][colonne] != vide){
		return false;
		}
	//On parcourt la colonne en partant du bas jusqu'à ntrouver une case vide
	size_t ligne(grille.size() -1);
	while (grille[ligne][colonne] != vide){
			--ligne;
		}
	//On remplit la case vide trouvée :
	grille[ligne][colonne]=couleur;
	return true;
	}
		
	
