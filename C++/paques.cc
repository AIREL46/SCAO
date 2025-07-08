#include <iostream>
#include <cmath>    // pour exp()
using namespace std;
int demander_annee ();
void affiche_date(int an1, int nbrj);
int date_paques (int an1);
int main()
{
  int an1(demander_annee());
  int nbrj(0);
  nbrj=date_paques (an1);
  affiche_date(an1, nbrj);
  return 0;
}
int demander_annee () {
	int an3(2014);
	do {
	cout <<"Entrez une annee (1583-4000) : ";
	cin >>an3;}
	while (an3<1583 or an3>4000);
	return an3;
	}
void affiche_date(int an1, int nbrj) {
	if (nbrj<=31) {cout <<"Date de paques en "<<an1<<" : "<<nbrj<<" mars"<<endl;}
	if (nbrj>31) {cout <<"Date de paques en "<<an1<<" : "<<nbrj-31<<" avril"<<endl;}
	
	
	}
int date_paques (int an1) {
	int nbrj(0);
	int siecle(an1/100);
	int p((13+(8*siecle))/25);
	int q(siecle/4);
	int M((15-p+siecle)-(q % 30));
	int N((4+siecle)-(q % 7));
	int d((M+19*(an1 % 19)) % 30);
	int e((2*(an1 % 4)+4*(an1 % 7)+(6*d)+N) % 7);
	nbrj=e+d+22;
	if (e==6 and (d==29 or (d==28 and (11*(M+1) % 30)<19))) {
		nbrj=nbrj-7;
		}
	return nbrj;
	}
