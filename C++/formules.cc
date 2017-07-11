#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double x;
	cout << "Rappels : le logarithme est defini sur les reels strictement positifs " << endl;
	cout << "La racine carree est defini sur les reels positif ou nuls " << endl;
	cout << "La fraction 1/x sur les reels non nuls " << endl;
	cout << "Entrez un reel : ";
	cin >> x;
	cout << "La valeur de x est : " << x << endl;
	if ((1-exp(x)) != 0) { cout <<"Le resultat de la premiere equation est : " << (1-exp(x))<< endl ;}
	else { cout << "Pour cette premiere equation l'expression i est indefini"<< endl;}
	if ((x>=0) and ((x-1)!=0)) { cout <<"Le resultat de la deuxieme equation est : " << (x*log(x))*exp(2/x-1) << endl ;}
	else { cout << "Pour cette deuxieme equation l'expression i est indefini"<< endl;}	
	if (pow(x,2)-8*x >0 and (2-x) !=0) { cout <<"Le resultat de la troisieme equation est : " << (-x-sqrt((pow(x,2)-8*x)))/2-x << endl ;}
	else { cout << "Pour cette troisieme equation l'expression i est indefini"<< endl;}		
	if (pow(x,2)-1/x >=0 and x!=0) { cout <<"Le resultat de la quatrieme equation est : " << ( ((sin(x)-x/20)) )<< "  "<<(log(sqrt(pow(x,2)-1/x))) <<endl ;}
	else { cout << "Pour cette quatrieme equation l'expression i est indefini"<< endl;}
	return 0;
}
