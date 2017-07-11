#include <iostream>
using namespace std;
#include <vector>
#include <string>
int demander_nombre();
int main()
{
	double valeur1(3.14);
	double valeur2(3.1416);
	double valeur3(3.141555);
	double* choix(nullptr);
	cout <<"valeur de pi selon precision souhaitee (1, 2 ou 3) : ";
	int ch(demander_nombre());
	if (ch==1){choix=&valeur1;}
	if (ch==2){choix=&valeur2;}
	if (ch==3){choix=&valeur3;}
	cout <<*choix<<endl;
	return 0;
}
int demander_nombre(){
	int x(0);
	do  {
		
		cin >> x;
			if (x<=0 or x>3) { cout <<"Le nombre doit etre 1, 2 ou 3"<<endl;}
			else {cout <<"OK"<<endl;}
		}
	while (x<=0 or x>3); 
	return (x);
	}
