
#include <iostream>

#include "Deflnt_header.h"
#include <iostream>
#include <cmath>
using namespace std;
double f(double x) {
	return x * x * x - x * x + 1;
}
int main()
{
	Deflnt MyInt(1.0, 2.0, *f);
	int N;
	cout << "enterstep N "; cin >> N;
	cout << "Trapzoid val " << endl;
	cout << MyInt.ByTrapzoid(N) << endl;

	cout << "Simpson val " << endl;
	cout << MyInt.BySimpson() << endl;
	return 0;
}
