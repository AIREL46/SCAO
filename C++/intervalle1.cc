#include <iostream>

using namespace std;

int main() 
{
  cout <<"Entrer un reel x : "<<endl;
  int x;
  cin >>x;
  cout <<"x = "<<x<<endl;
  if (x<-1 and x>1){
	cout <<"x appartient a l'intervalle [-1, 1]"<<endl;
	}
	else {
	cout <<"x n'appartient pas a l'intervalle [-1, 1]"<<endl;	
	}
  return 0;
}
