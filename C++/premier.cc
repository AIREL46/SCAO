#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int n(1);
	int D(0);
	do  {
		cout << "Entrer un entier plus grand que 0" << endl;
		cin >> n;
			if (n<=0) { cout <<"Le nombre doit etre strictement positif"<<endl;}
			else {cout <<"OK"<<endl;}
		}
	while (n<=0);
	if (fmod(n,2)==0 and n!=2) {cout <<n<<" ce nombre est pair: "<<endl;}
	else {cout <<"ce nombre n'est pas pair sauf s'il est egal a 2"<<endl;}
	for (int i(2);i<=sqrt(n);++i) {
			if (fmod(n,i)==0) {
			D=i;}
			else {
			}
		
		}
	if (D!=0) {cout <<"Ce nombre n'est pas premier car il es divisible par :" <<D<<endl;}
	else {cout <<"Ce nombre est premier"<<endl;}
	return 0;
}
