#include <iostream>
using namespace std;
int demander_nombre();
int main()
{
	int y (demander_nombre());
	int z (demander_nombre());
	cout <<"y = "<<y<<"  z = "<<z<<endl;
	
	return 0;
}
int demander_nombre(){
	int x;
	do {
	cout <<"Introduire un nombre entier compris entre 5 et 10"<<endl;
	cin >>x;
	}
	while (x<0 or x<5 or x>10);
	return x;
	}
