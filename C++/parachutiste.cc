#include <iostream>
#include <cmath>    // pour exp()
using namespace std;

int main()
{
  double masse(80.0);
  do {
    cout << "masse du parachutiste (>= 40) ? ";
    cin >> masse;
  } while (masse < 40.0);

  double h0(39000.0);
  do {
    cout << "hauteur de depart du parachutiste (>= 250) ? ";
    cin >> h0;
  } while (h0 < 250.0);

  /*******************************************
   * Completez le programme a partir d'ici.
   *******************************************/
	const double g(9.81);
	double v0(0.0);
	double t0(0.0);
	double v(v0);
	double a(g);
	double h(h0);
	double s0(2.0);
	double t(t0);
	double s(s0/masse);
	double q(0.0);
	bool vs(true);
	bool am(true);
	bool op(false);
	do {
	q=exp(-s*(t-t0));
	v=(g/s)*(1-q)+(v0*q);
	if (v>343 and vs) {
		vs=false;
		cout <<"Felix depasse la vitesse du son"<<endl;}
	h=h0-(g/s)*(t-t0)-((v0-g/s)/s)*(1-q);
	a=g-(s*v);
	if (a<0.5 and am) {
		am=false;
		cout <<"Felix a atteint sa vitesse maximun"<<endl;}
	if (h<2500 and (not op)) {
		op=true;
		s0=25.0;
		s=s0/masse;
		t0=t;
		v0=v;
		h0=h;
		cout <<"Felix ouvre son parachute"<<endl;}
	cout <<t<<" - "<<h<<" - "<<v<<" - "<<a<<endl;
	t=t+1;
	}
	while (h>0);

  /*******************************************
   * Ne rien modifier apres cette ligne.
   *******************************************/

  return 0;
}
