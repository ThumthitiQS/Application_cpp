#pragma once

#include <cmath>
#include "BinModel02.h"
using namespace std;

class Blackschole {
private:
	double S0, r, sigma;
public:
	Blackschole(double S0_, double r_, double sigma_)
	{
		S0 = S0_; r = r_; sigma = sigma_;
	}
	BinModel ApproxBinModel(double h) 
	{
		double U = exp( sigma * sqrt(h)) - 1;
		double D = (1 / (1 + U)) - 1;
		double R = exp(r * h) - 1;
		
		BinModel ApproxModel(S0, U, D, R);
		return ApproxModel;
	}
};