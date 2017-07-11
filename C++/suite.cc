#include <iostream>
using namespace std;

int main()
{
  int debut;
  do {
    cout << "de (>= 1) ? ";
    cin >> debut;
  } while (debut < 1);

  int fin;
  do {
    cout << "a (>= " << debut << ") ? ";
    cin >> fin;
  } while (fin < debut);

  /*******************************************
   * Completez le programme a partir d'ici.
   *******************************************/

for (int x(debut);x<=fin;++x){
		int x1(x);
		int k(0);
		while (x1>0){
		if ((x1 % 3)==0){
			k=k+1;
			x1=x1+4;
			}
		if ((x1 % 4)==0){
			k=k+1;
			x1=x1/2;
			}
		if (not(x1 % 3)==0 and not(x1 % 4)==0){
			k=k+1;
			x1=x1-1;
			}
		
	}
	cout <<x<<" -> "<<k<<endl;
}

  /*******************************************
   * Ne rien modifier apres cette ligne.
   *******************************************/

  return 0;
}
