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
void demande_et_joue(Grille& grille, Couleur couleur_joueur);
bool est_ce_gagne(const Grille& grille, Couleur couleur_joueur);
unsigned int compte(const Grille& grille, size_t ligne_depart, size_t colonne_depart, int dir_ligne, int dir_colonne);
bool plein(const Grille& grille);
int main()
{
	
	Grille grille;
	initialise(grille);
	affiche(grille);
	Couleur couleur_joueur=jaune;
	bool gagne;
	do {
		demande_et_joue(grille, couleur_joueur);
		affiche(grille);
		gagne=est_ce_gagne(grille, couleur_joueur);
		//On change la couleur pour la couleur de l'autre joueur
		if (couleur_joueur==jaune){
			couleur_joueur=rouge;
			}else{couleur_joueur=jaune;}
		
		}while (not gagne and not plein(grille));
		if (gagne){
		if (couleur_joueur == jaune){cout <<"Le joueur O a gagne!"<<endl;}
		else {cout <<"Le joueur X a gagne!"<<endl;}
		}else{cout <<"Match nul!"<<endl;}
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
	size_t ligne(grille.size() -1);
	while ((ligne<grille.size()) and (grille[ligne][colonne] != vide)){
		--ligne;
		}
	if(ligne<grille.size()){
		grille[ligne][colonne]=couleur;
		return true;
		}else{
			return false;
			}
	}
void demande_et_joue(Grille& grille, Couleur couleur_joueur){
	bool valide;
	cout <<"Joueur";
	if (couleur_joueur==jaune){
		cout <<'X';
		}else{cout <<'O';}
		cout <<" : entrez un numero de colonne"<<endl;
		do {
			size_t colonne;
			cin >>colonne;
			--colonne;
			valide=joue(grille, colonne, couleur_joueur);
			if(not valide){cout <<"Ce coup n'est pas valide"<<endl;}
			}while (not valide);
	}		
bool est_ce_gagne(const Grille& grille, Couleur couleur_joueur)
{
	for(size_t ligne(0); ligne < grille.size(); ++ligne){
		for(size_t colonne(0); colonne < grille[ligne].size(); ++colonne){
			Couleur couleur_case(grille[ligne][colonne]);
			if (couleur_case == couleur_joueur){
				const size_t ligne_max(grille.size() -4);
				const size_t colonne_max(grille[ligne].size() -4);
				if((ligne >=3 and colonne <=colonne_max and compte(grille, ligne, colonne, -1, +1) >= 4) or (colonne <= colonne_max and compte(grille, ligne, colonne, 0, +1) >= 4) or (ligne <= ligne_max and colonne <= colonne_max and compte(grille, ligne, colonne, +1, +1) >= 4) or (ligne <= ligne_max and compte(grille, ligne, colonne, +1, 0) >= 4))
				{return true;}
			}
		}
	}
	return false;
}
unsigned int compte(const Grille& grille, size_t ligne_depart, size_t colonne_depart, int dir_ligne, int dir_colonne)
{
	unsigned int compteur(0);
	size_t ligne(ligne_depart);
	size_t colonne(colonne_depart);
	while (ligne < grille.size() and colonne < grille[ligne].size() and grille[ligne][colonne] == grille[ligne_depart][colonne_depart])
	{
		++compteur;
		ligne   = ligne   + dir_ligne;
		colonne = colonne +dir_colonne;
		}
	return compteur;
	}
bool plein(const Grille& grille)
{for(auto kase : grille[0]){
	if (kase == vide){return false;}
	}
	return true;
	}
