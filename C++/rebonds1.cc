#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double g(9.81);
	cout << g <<endl;
	double H0(0.0);
	double eps(0.0);
	int nbr(0);
	double v(0.0);
	double v1(0.0);
	double h(0.0);
	double h1(0.0);
	cout << v << v1 << h << h1 << endl;
	cout << "Entrer la hauteur initiale H0>0 : " ;
	cin >> H0;
	cout << "Entrer le coefficient de rebond 0<=eps<1 : " ;
	cin >> eps;
	cout << "Entrer le nombre de rebonds 0<=nbr : " ;
	cin >> nbr;
	h=H0;
	v=sqrt(2*h*g);
	v1=eps*v;
	h1=(pow(v1,2))/(2*g);
	cout << "h : "<< h << "  h1 : "<< h1 << "  v : "<< v << "  v1 : "<< v1 << endl;
	
	if (H0>0 and eps>0 and eps<1 and nbr>0) {
		cout << "Les valeurs sont coherentes" << endl;
			for (int i(1);i	<= nbr;++i) {
			h=h1;
			v=v1;
			v=sqrt(2*h*g);
			v1=eps*v;
			h1=(pow(v1,2))/(2*g);
			cout << " i : "<< i << "h : "<< h << "  h1 : "<< h1 << "  v : "<< v << "  v1 : "<< v1 << endl;}
		}
	else
		{cout << "Les valeurs ne sont pas coherentes" << endl;
		
		}
	return 0;
}
