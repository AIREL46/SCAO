#include <iostream>
using namespace std;
#include <vector>
#include <string>
struct Personne{
	string nom;
	double taille;
	int age;
	char sexe;
	};
Personne naissance();
void anniversaire(Personne& p);
void affiche(Personne const& p);

int main()
{
	
	Personne untel(naissance());
	cout <<untel.nom<<" "<<untel.taille<<" "<<untel.sexe<<" "<<untel.age<<endl;
	anniversaire(untel);
	cout <<untel.nom<<" "<<untel.taille<<" "<<untel.sexe<<" "<<untel.age<<endl;
	affiche(untel);
	cout <<endl;
  return 0;
}
Personne naissance(){
	Personne p;
	cout <<"saisie d'une nouvelle personne"<<endl;
	cout <<"Entrer son nom : ";
	cin >>p.nom;
	cout <<"Entrer sa taille : ";
	cin >>p.taille;
	cout <<"Entrer son age : ";
	cin >>p.age;
	do {
		cout <<"Homme (M) ou femme (F) : ";
		cin >>p.sexe;
		} while ((p.sexe !='F') and (p.sexe !='M'));
	return p;
	}
void anniversaire(Personne& p) {
	++(p.age);
	}
void affiche(Personne const& p){
	cout <<p.nom<<", ";
	switch (p.sexe){
		case 'M' : cout <<"homme";break;
		case 'F' : cout <<"femme";break;
		default : cout <<"alien";break;
		}
	cout <<", "<<p.taille<<" m, "<<p.age<<" an";
	if (p.age>1){cout <<"s.";}
	}
