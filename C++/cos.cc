#include <iostream>
#include <cmath>
using namespace std;
double demander_nombre();
double factorielle (int k);
double somme_partielle(double x,int N);
int main()
{
	cout << "Entrer la valeur de N plus grand que 0" << endl;
	double N(demander_nombre());
	cout << "Entrer la valeur de x dans [0,2*pi]" << endl;
	double x(demander_nombre());
	double C(cos (x));
	cout <<" x= "<<x<<" Cos x = "<<C<<" avec N = "<<N<< " Somme partielle "<<" = "<<somme_partielle (x,N)<<endl;
	return 0;
}
double demander_nombre(){
	double a(0.0);
	do  {
		cin >> a;
			if (a<0.0) { cout <<"Les nombres doit etre strictement positif"<<endl;}
			else {cout <<"OK"<<endl;}
		}
	while (a<0.0); 
	return (a);
	}
double factorielle (int k) {
		double fact(k);
		if (k==0){fact=1;}
		else {
		double y(fact-1);
		fact=fact*y;
		for (int i(k-1);i>1;--i){
			y=y-1;
			fact=fact*y;
			}
		}
return fact;
}
double somme_partielle(double x,int N){
	double sp(0.0);
	for (int i(0);i<=N;++i){
		double spe(sp);
		spe=(pow(-1,i)*pow(x,2*i)/factorielle (2*i));
		sp=sp+spe;
		}
	return sp;
}
