#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double g(9.81);
	cout << g <<endl;
	double H0(0.0);
	double eps(0.0);
	double v(0.0);
	double v1(0.0);
	double h(0.0);
	double h1(0.0);
	double h_fin(0.0);
	int nbr(0);
	cout << v << v1 << h << h1 << h_fin << endl;
	
	do {
		cout << "Entrer la hauteur initiale H0>0 : " ;
		cin >> H0;
			if (H0<=0) {cout << "La hauteur initiale H0 doit etre >0 " << endl ;}
			else {cout << "La hauteur initiale H0 est correcte " << endl ;}
		}
	while (H0<=0);
	cout << "Entrer le coefficient de rebond 0<=eps<1 : " ;
	cin >> eps;
	cout << "Entrer la hauteur finale desire 0<h_fin<H0 : " ;
	cin >> h_fin;
	h=H0;
	v=sqrt(2*h*g);
	v1=eps*v;
	h1=(pow(v1,2))/(2*g);
	cout << "h : "<< h << "  h1 : "<< h1 << "  v : "<< v << "  v1 : "<< v1 << endl;
	
	if (H0>0 and eps>0 and eps<1 and h_fin>0 and h_fin<H0) {
		cout << "Les valeurs sont coherentes" << endl;
			do {
			nbr=nbr+1;
			h=h1;
			v=v1;
			v=sqrt(2*h*g);
			v1=eps*v;
			h1=(pow(v1,2))/(2*g);
			cout << "nbr : " << nbr << " h : "<< h << "  h1 : "<< h1 << "  v : "<< v << "  v1 : "<< v1 << endl;
			}
			while (h>=h_fin);
		}
	else
		{cout << "Les valeurs ne sont pas coherentes" << endl;
		
		}
	return 0;
}
