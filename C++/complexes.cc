#include <iostream>
using namespace std;
#include <vector>
#include <string>
struct Complexe {
	double x;
	double y;
	};
void affiche(Complexe a);
Complexe addition(Complexe z1, Complexe z2);
Complexe soustraction(Complexe z1, Complexe z2);
Complexe multiplication(Complexe z1, Complexe z2);
Complexe division(Complexe z1, Complexe z2);
int main()
{
  cout <<"Addition : ";
  affiche (addition({1,0}, {0,1}));
  cout <<"Soustraction : ";
  affiche (soustraction({1,0}, {0,1}));
  cout <<"Multiplication : ";
  affiche (multiplication({1,1}, {1,1}));
  cout <<"Division : ";
  affiche (division({2,-3}, {1,1}));
  return 0;
}
void affiche(Complexe a){
	
	cout <<a.x<<", "<<a.y<<endl;
	}
Complexe addition(Complexe z1, Complexe z2){
	cout <<"("<<z1.x<<", "<<z1.y<<")"<<" + "<<"("<<z2.x<<", "<<z2.y<<") = ";
	Complexe somme({(z1.x+z2.x),(z1.y+z2.y)});
	return somme;
	}
Complexe soustraction(Complexe z1, Complexe z2){
	cout <<"("<<z1.x<<", "<<z1.y<<")"<<" + "<<"("<<z2.x<<", "<<z2.y<<") = ";
	Complexe difference({(z1.x-z2.x),(z1.y-z2.y)});
	return difference;
	}
Complexe multiplication(Complexe z1, Complexe z2){
	cout <<"("<<z1.x<<", "<<z1.y<<")"<<" + "<<"("<<z2.x<<", "<<z2.y<<") = ";
	Complexe produit({(z1.x*z2.x)-(z1.x*z2.y),(z1.x*z2.y)+(z1.y*z2.x)});
	return produit;
	}
Complexe division(Complexe z1, Complexe z2){
	cout <<"("<<z1.x<<", "<<z1.y<<")"<<" + "<<"("<<z2.x<<", "<<z2.y<<") = ";
	Complexe quotient({((z1.x*z2.x)+(z1.y*z2.y))/((z1.y*z2.x)+(z2.y*z2.y)),((z1.y*z2.x)-(z1.x*z2.y))/((z2.x*z2.x)+(z2.y*z2.y))});
	return quotient;
	}
