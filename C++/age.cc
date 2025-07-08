#include <iostream>
using namespace std;

int main()
{
	int age;
	cout << "Entrez votre age : ";
	cin >> age;	
	
	int an(2014);
	int an_n;
	an_n = an - age;
	
	cout << "Votre annee de naissance est : " << an_n << endl;
		
	return 0;
}
