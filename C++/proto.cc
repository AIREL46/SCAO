#include <iostream>
#include <cmath>
using namespace std;

int demander_nombre(){
	int x(0);
	do  {
		
		cin >> x;
			if (x<=0) { cout <<"Les nombres doit etre strictement positif"<<endl;}
			else {cout <<"OK"<<endl;}
		}
	while (x<=0); 
	return (x);
	
}
int main()
{
	cout << "Entrer un premier entier plus grand que 0" << endl;
	int a(demander_nombre());
	cout << "Entrer un deuxieme entier plus grand que 0" << endl;
	int b(demander_nombre());
	cout <<a<<b<<endl;
	return 0;
}


