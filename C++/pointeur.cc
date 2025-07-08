#include <iostream>
using namespace std;
#include <vector>
#include <string>
struct Maison{string adresse;};



struct Personne{string nom; Maison* Pm;};
void affiche(Personne Px);
int main()
{
	
	Maison M1{"1, impasse du Languernais 44350 St MOLF"};
	Maison M2{"20, allee Madeleine 44500 La Baule"};
	Maison M3{"5B, rue Champ Lagarde 78000 Versailles"};
	Maison* Pm1;//Initialisation du pointeur Pm1 (affectation statique)
	Pm1=new Maison(M1);//Affectation à Pm1 de la Maison M1 (affectation dynamique)
	Maison* Pm2;
	Pm2=new Maison(M2);
	Maison* Pm3;
	Pm3=new Maison(M3);
	Personne P1{"Regis LERUSTE", Pm1};
	Personne P2{"Bruno LERUSTE", Pm1};
	Personne P3{"Arnaud LERUSTE", Pm3};
	Personne P4{"Nelly Loiselet", Pm2};
	Personne P5{"Sandrine Loiselet", Pm2};
	Personne P6{"Samuel Loiselet", Pm2};
	vector <Personne> liste {P1,P2,P3,P4,P5,P6};
	for (size_t i(0); i<liste.size(); ++i){
		Personne Py;
		Py=liste[i];
		cout <<i+1<<" - ";
		affiche(Py);
		}
	delete Pm1;	Pm1=nullptr;
	delete Pm2;	Pm2=nullptr;
	delete Pm2;	Pm2=nullptr;
	return 0;
}
void affiche(Personne Px){
	Personne P;
	Maison M;
	P=Px; M=*P.Pm;
	cout <<P.nom<<" habite "<<M.adresse<<endl;
	}
