#include <iostream>
using namespace std;

int main()
{
	double x;
	cout << "Soit I l'intervalle [-1,1] " << endl;
	cout << "Ce programme test la valeur d'un nombre reel introduit par l'operateur " << endl;
	cout << "et indique l'appartenance de ce nombre a l'intervalle [-1,1] " << endl;
	cout << "Entrez un reel : ";
	cin >> x;
	cout << "La valeur de x est : " << x << endl;
	if (x>1) {
		cout << " x n'appartient pas a I " << endl;}
	else {
		if (x<-1) {
		cout << " x n'appartient pas a I " << endl;}
		else {
		cout << " x appartient a I " << endl;}
	}
	
	return 0;
}
