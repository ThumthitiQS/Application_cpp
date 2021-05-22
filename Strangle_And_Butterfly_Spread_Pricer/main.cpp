#include "Spread.h"
#include "BinModel02.h"
#include "Options06.h"
#include "DoubleDigitOpt.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	BinModel Model;
	if (Model.GetInputData() == 1)
		return 1;
	Call Option1;
	Option1.GetInputData();
	cout << "European call option price = "
		<< Option1.PriceByCRR(Model) <<
		endl << endl;

	Put Option2;
	Option2.GetInputData();
	cout << "European put option price = " <<Option2.PriceByCRR(Model) << endl << endl;
	DoubDigitOpt Option3_dd;
	Option3_dd.GetInputData();
	cout << "European double-digital option price = " << Option3_dd.PriceByCRR(Model) << endl <<endl;
	StrangleOpt Option4_so;
	Option4_so.GetInputData();
	cout << "European double-digital option price = " << Option4_so.PriceByCRR(Model) << endl <<endl;
	ButterflyOpt Option5_bo;
	Option5_bo.GetInputData();
	cout << "European double-digital option price = " << Option5_bo.PriceByCRR(Model) << endl << endl;
	return 0;
}




/*
Enter S0: 106
Enter U:  0.15125
Enter D:  -0.13138
Enter R:  0.00545

Input data checked
There is no arbitrage
Enter Call option data:
Enter steps to expiry N:8
Enter strike price K: 100

European call option price = 21.6811

Enter Call option data:
Enter steps to expiry N:8
Enter strike price K: 100

European put option price = 11.4261

Enter double-digital option data:
Enter steps to expiry N: 8
Enter parameter K1: 100
Enter parameter K2: 110

European double-digital option price = 0.26075

Enter European strangle option data:
Enter steps to expiry N: 8
Enter parameter K1:      100
Enter parameter K2:      110


European double-digital option price = 28.3914

Enter European butterfly spread option data:
Enter steps to expiry N: 8
Enter parameter K1:      100
Enter parameter K2:      110


European double-digital option price = 1.04313


*/