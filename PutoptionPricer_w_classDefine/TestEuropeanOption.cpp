

#include "EuropeanOption.h"
#include <iostream>
using namespace std;


int main()
{ // All options are European
	// Call option on a stock
	EuropeanOption callOption;
	cout << "Call option on a stock: " << callOption.Price() << endl;

	//parameter
	double r = 0.1;
	double sig = 0.3;
	double K = 50;
	double T = 0.25;
	double U = 50;
	char optType = 'P';

	//print
	EuropeanOption putoption(r, sig, K, T, U, optType);

	cout << "2:" << putoption.PutPrice() << endl;

	double D = 1.5;

	double T2 = 2.0 / 12;

	cout << "U = " << putoption.calspd(D, T2) << endl;

	cout << "3:" << putoption.PutPrice() << endl;


}


/*
Call option on a stock: 2.13293
2:2.37561
U = 48.5248
3:3.03039
*/