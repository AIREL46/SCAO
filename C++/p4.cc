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
	//On parcourt la colonne en partant du bas
	size_t ligne(grille.size() -1);
	//...jusqu'à trouver une case vide
	//...ou jusqu'en haut de colonne si la colonne est pleine :
	bool pleine(false);
	while ((not pleine) and (grille[ligne][colonne] != vide)){
		if(ligne==0){
			pleine=true;
			}else{
				--ligne;
				}
		}
		//Si on n'est pas arrivé jusqu'en haut de la colonne, on remplit la case vide trouvée
		//Sinon, c'est que la colonne est pleine et le coup n'est pas valide
		if(not pleine){
			grille[ligne][colonne]=couleur;
			return true;
			}else{
				return false;
				}
	}
