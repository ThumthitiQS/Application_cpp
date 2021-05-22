#include <iostream>
#include <cmath>
#include "BinModel01.h"
#include "Options01.h"
using namespace std;

int main(int argc, char* argv[])
{
double S0 = 0, U = 0, D = 0, R = 0;
if (GetInputData(S0, U, D, R) == 1)
{
	return 1;
}
	

double K = 0; // strike price
int N = 0;  // steps to expiry

cout << "Enter call option data:" << endl;
GetInputData(N, K);

cout << "European call option price = " << PriceByCRR(S0, U, D, R, N, K) << endl << endl;

cout << "Calculate European call option price by HW1 Function: "
	<< HW1PriceByCRR(S0, U, D, R, N, K)
	<< endl << endl;


return 0;
}



/*
Enter S0: 106
Enter U: 0.15125
Enter D: -0.13138
Enter R: 0.00545

Input data checked
There is no arbitrage

Enter call option data:
Enter steps to expiry N: 8
Enter strike price K: 100

European call option price = 21.6811

Calculate European call option price by HW1 Function: 21.6811





*/







