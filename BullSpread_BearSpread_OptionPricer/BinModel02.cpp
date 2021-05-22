#include "BinModel02.h"
#include <iostream>
#include <cmath>
using namespace std;


int BinModel::GetInputData()
{
	//entering data
	cout << "Enter S0: "; cin >> S0;
	cout << "Enter U:  "; cin >> U;
	cout << "Enter D:  "; cin >> D;
	cout << "Enter R:  "; cin >> R;
	cout << endl;
	//making sure that 0 < s0 , -1 < D <U , -1 <R
	if (S0 <= 0 || -1 >= D || -1 >= U || D >= U || -1 >= R)
	{
		cout << "illegal data ranges" << endl;
		cout << "Terminating program" << endl;
		return 1;
	}
	//check for arbitrage
	if (R >= U || R <= D)
	{
		cout << "Arbitrage exists" << endl;
		cout << "Terminating program" << endl;
		return 1;

	}
	cout << "Input data checked" << endl;
	cout << "There is no arbitrage" << endl;

	return 0;
}





double BinModel::RiskNeutProb()
{
	return (R - D) / (U - D);
}
double BinModel::S(int n, int i)
{
	return S0 * pow(1 + U, i) * pow(1 + D, n - i);

}





double BinModel::GetR()
{
	return R;
}
