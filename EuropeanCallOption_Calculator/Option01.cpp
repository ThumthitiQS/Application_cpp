#include <iostream>
#include <cmath>
#include "Options01.h"
#include "BinModel01.h"
using namespace std;
int GetInputData(int& N, double& K)
{
	cout << "Enter steps to expiry N: "; cin >> N;
	cout << "Enter strike price K: "; cin >> K;
	cout << endl;
	return 0;
}
double CallPayoff(double z, double K)
{
	if (z > K) return z - K;
	return 0.0;
}

double PriceByCRR(double S0, double U, double D, double R, int N, double K)
{
	double q = RiskNeutProb(U, D, R);
	//cout << "q : " << q << endl;
	//double Price[N + 1];    for mac 
	double Price[9];
	//cout << "Price : " << Price << endl;    //Price: 0077F714
	memset(Price, 0, sizeof(Price));  
	//cout << "size of price " << sizeof(Price) << endl; 72
	//cout << "Price : " << Price << endl;   //Price: 0077F714

	for (int i = 0; i <= N; i++)
	{
		Price[i] = CallPayoff(S(S0, U, D, N, i), K);
	}
	for (int n = N - 1; n >= 0; n--)
	{
		for (int i = 0; i <= n; i++)
		{
			Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / (1 + R);
		}
	}
	return Price[0];
}




// simplify to remove all the factorials
double HW1Function(int N, int n)
{
	if (n<0 || n>N) return 0;
	double result=1;

	for (int i = 1; i <= n; i++) result = result*(N-n+i)/i;

	//cout << "n : " << n << endl;
	//cout << "N : " << N << endl;
	//cout << "result : " << result << endl;    //Price: 0077F714
	return result;
}



double HW1PriceByCRR(double S0, double U, double D, double R, int N, double K)
{
	double q = RiskNeutProb(U, D, R);
	double Price = 0;
	for (int n=0; n <= N; n++) //sum up
	{
		Price = Price+HW1Function(N,n)*pow(q,n)*pow(1-q,N-n)* CallPayoff(S(S0, U, D, N, n), K)/pow(1 + R, N);
	}
	return Price;
}

double HW1Factorial(int n)
{
	double num = 1.0;
	if (n <= 0)
		return num;

	do {
		num = num * n;
		n--;
	} while (n > 0);

	return num;
}

