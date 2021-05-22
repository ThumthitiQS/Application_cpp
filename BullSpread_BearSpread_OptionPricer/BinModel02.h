#pragma once

class BinModel
{
private:
	double S0;
	double U;
	double D;
	double R;
public:
	//computing tisk neurtal prob
	double RiskNeutProb();
	//computing the stock price at node n,i 
	double S(int n, int i);
	//inputing, displaying and checking model data
	int GetInputData();
	double GetR();

};