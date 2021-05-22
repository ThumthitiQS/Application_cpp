#include "BinModel02.h"
#include "Options06.h"
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	BinModel Model;
	if (Model.GetInputData() == 1) return 1;
	Call Option1;
	Option1.GetInputData();
	cout << "European call option price = " << Option1.PriceByCRR(Model) << endl << endl;
	Put Option2;
	Option2.GetInputData();
	cout << "European put option price = " << Option2.PriceByCRR(Model) << endl << endl;

	BullSpread Bull;
	Bull.GetInputData();
	cout << "European BullSpread Price = " << Bull.PriceByCRR(Model) << endl << endl;
	BearSpread Bear;
	Bear.GetInputData();
	cout << "European BearSpread Price = " << Bear.PriceByCRR(Model) << endl << endl;
	return 0;


}



/*

Enter S0 : 106
Enter U : 0.15125
Enter D : -0.13138
Enter R : 0.00545

Input data checked
There is no arbitrage
Enter Call option data :
Enter steps to expiry N : 8
Enter strike price K : 100

European call option price = 21.6811

Enter Call option data :
Enter steps to expiry N : 8
Enter strike price K : 100

European put option price = 11.4261

Enter Call option data :
Enter steps to expiry N : 8
Enter strike price K1 : 100

Enter strike price K2 : 110

European BullSpread Price = 4.71584

Enter Call option data :
Enter steps to expiry N : 8
Enter strike price K1 : 100

Enter strike price K2 : 110

European BearSpread Price = 4.85866

*/