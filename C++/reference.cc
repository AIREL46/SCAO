#include <iostream>
using namespace std;
#include <vector>
#include <string>
struct Maison{string adresse;};
Maison M{""};
struct Personne{string nom; Maison& M;};
void affiche(Personne Px);
int main()
{
	Maison M1{"1, impasse du Languernais 44350 St MOLF"};
	Maison M2{"20, allee Madeleine 44500 La Baule"};
	Personne P1{"Regis LERUSTE", M1};
	Personne P2{"Bruno LERUSTE", M1};
	Personne P3{"Arnaud LERUSTE", M1};
	Personne P4{"Nelly Loiselet", M2};
	Personne P5{"Sandrine Loiselet", M2};
	Personne P6{"Samuel Loiselet", M2};
	
	affiche(P1); affiche(P2); affiche(P3); affiche(P4); affiche(P5); affiche(P6); 
	return 0;
}
void affiche(Personne Px){
	Maison Mx;
	Mx=Px.M;
	string adr;
	adr=Mx.adresse;
	cout <<Px.nom<<" "<<adr<<endl;
	}
