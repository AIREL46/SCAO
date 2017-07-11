#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	const double g(9.81);
	double H0;
	double eps;
	int nbr;
	do 	{
	cout <<"Entrer successivement les valeurs de H0>0, 0<=eps<1, 0<=nbr."<<endl;
	cin >>H0>>eps>>nbr;
	} while (H0<0 or eps>1 or eps<=0 or nbr<=0);
	cout <<g<<" - "<<H0<<" - "<<eps<<" - "<<nbr<<endl<<endl;
	double v(sqrt(2*H0*g));//Vitesse à l'arrivée au sol
	double v1(eps*v);//vitesse après le premier rebond
	double h((v1*v1)/(2*g));
	double h1(0.0);
	cout <<"R1  "<<h<<endl;
	for (int i=1;i<=nbr-1;++i){
		v=sqrt(2*h*g);
		v1=eps*v;
		h=(v*v)/(2*g);
		h1=(v1*v1)/(2*g);
		h=h1;
		cout <<"R"<<i+1<<"  "<<h1<<"  "<<endl;
		}
	return 0;
	
}

