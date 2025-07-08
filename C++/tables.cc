#include <iostream>
using namespace std;

int main()
{
	cout << "Tables de multiplication de 2 a 10 " << endl << endl;
	for(int i(1);i<=10;++i) {
		cout << "Table de multiplication par "<< i << endl;
		for (int j(1);j<=10;++j) {
			cout << j << " * " << i << " = " << i*j << endl;
			}
			cout  << endl;
		}

	return 0;
}
