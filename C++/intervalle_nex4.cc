#include <iostream>

using namespace std;

int main() 
{
  cout <<"Entrer un reel x : "<<endl;
  int x;
  cin >>x;
  cout <<"x = "<<x<<endl;
  if ((x>=-10 and x<=-2) or (x>=0 and x<=1) or (x>=2 and x<=3)){
	cout <<"x appartient a l'intervalle []"<<endl;
	}
	else {
	cout <<"x n'appartient pas a l'intervalle []"<<endl;	
	}
  return 0;
}
