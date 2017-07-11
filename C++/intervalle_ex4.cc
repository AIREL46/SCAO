#include <iostream>
using namespace std;

int main()
{
	double x;
	cout << "Soit l'intervalle I=[2,3[U]0,1]U[-10,-2] " << endl;
	cout << "Ce programme test la valeur d'un nombre reel introduit par l'operateur " << endl;
	cout << "Entrez un reel : ";
	cin >> x;
	cout << "La valeur de x est : " << x << endl;
	if (((x<=-2) and (x>=-10)) or ((x>=0) and (x<=1))or ((x>=2) and (x<=3))){
		cout << "x est dans l'intervalle" << endl;
		}
	else {cout << "x n'est pas dans l'intervalle" << endl;}
	return 0;
}
