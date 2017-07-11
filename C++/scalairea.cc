#include <iostream>
using namespace std;
#include <vector>
int scalaire(vector<int> u, vector<int> v);
int main()
{
  int n_max(5);
  int n(0);
  while (n>n_max or n<=0) {
  cout <<"entrez la taille des vecteur <=5"<<endl;
  cin >>n;
  cout <<n_max<<" "<<n<<endl;
	}
  vector<int> vecteur1(n);
  vector<int> vecteur2(n);
  for (size_t i(0); i<vecteur1.size();++i) {
	  cout <<"Entrez la composante "<<i<<" du vecteur 1 : ";
	  cin >>vecteur1[i];
	  cout <<endl;
	  }	
   for (size_t i(0); i<vecteur2.size();++i) {
	  cout <<"Entrez la composante "<<i<<" du vecteur 2 : ";
	  cin >>vecteur2[i];
	  cout <<endl;
	  }
	cout <<scalaire(vecteur1, vecteur2)<<endl;
	
  return 0;
}
int scalaire(vector<int> u, vector<int> v) {
	int x(0);
	int y(0);
	for (size_t i(0); i<u.size(); ++i){
	x=u[i]*v[i];
	y=y+x;
	}
	return y;
	}
