#include <iostream>
using namespace std;
#include <vector>

int main()
{
  int const taille(10);
  vector<int> tab;
  for (size_t i(0); i<taille; ++i) {
	  tab.push_back(tab.size());
	  }
	for (auto element : tab){
		cout <<element<<" ";
		}
	cout <<endl;
	for (size_t i(0); i<taille; ++i){
		cout <<"L'element "<<i<<" vaut "<<tab[i]<<endl;
		}
	for (size_t i(0); i<tab.size(); ++i){
		cout <<"Entrez l'element suivant : "<<i<<endl;
		cin >>tab[i];
		}
	for (size_t i(0); i<taille; ++i){
		cout <<"L'element "<<i<<" vaut "<<tab[i]<<endl;
		}
  return 0;
}
