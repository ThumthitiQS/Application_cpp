/*
#include "BinLattice02.h"
#include "BinModel02.h"
#include "Options09.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    BinModel Model;
    if (Model.GetInputData() == 1) return 1;

    ofstream fout;
    fout.open("Results.txt");

    Call Option1;
    Option1.GetInputData();
    BinLattice<double> PriceTree;
    BinLattice<double> XTree;
    BinLattice<double> YTree;


    fout << "S0 = " << Model.GetS0() << endl
        << "U = " << Model.GetU() << endl
        << "D = " << Model.GetD() << endl
        << "R = " << Model.GetR() << endl;

    fout << "N = " << Option1.GetN() << endl
        << "K = " << Option1.GetK() << endl;

    fout << "European call prices by PriceByCRR:“ 
        << Option1.PriceByCRR(Model) << endl << endl;

    fout << "European call prices by PriceByCRRHW6:"
        << Option1.PriceByCRRHW6(Model, PriceTree, XTree, YTree)
        << endl << endl;
    PriceTree.Display(fout);
    fout << "Stock positions in replicating strategy:“ << endl << endl;
        XTree.Display(fout);
    fout << "Money market account positions in replicating strategy:“ << endl << endl;
        YTree.Display(fout);
}
*/




#include "Options09.h"
#include "BinModel02.h"
#include "BinLattice02.h"
#include <iostream>
#include <cmath>
using namespace std;
double EurOption::PriceByCRR(BinModel Model)
{
    double q = Model.RiskNeutProb();
    int N = GetN();
    vector<double> Price(N + 1);
    for (int i = 0; i <= N; i++)
        Price[i] = Payoff(Model.S(N, i));
    for (int n = N - 1; n >= 0; n--)
    {
        for (int i = 0; i <= n; i++)
            Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / (1 + Model.GetR());
    }
    return Price[0];
}


double EurOption::PriceByCRRHW6(BinModel Model, BinLattice<double>& PriceTree, BinLattice<double>& XTree, BinLattice<double>& YTree)
{
    double q = Model.RiskNeutProb();
    int N = GetN();
    PriceTree.SetN(N);
    XTree.SetN(N);
    YTree.SetN(N);
    double EOVal;
    double X_Node, Y_Node;
    for (int i = 0; i <= N; i++) {
        PriceTree.SetNode(N, i, Payoff(Model.S(N, i)));

    }
    for (int n = N-1 ; n >= 0; n--) 
    {
        for (int i = 0; i <= n; i++)
        {
            EOVal = (q * PriceTree.GetNode(n + 1, i + 1) + (1 - q) * PriceTree.GetNode(n + 1, i)) / (1 + Model.GetR());
            X_Node = (PriceTree.GetNode(n + 1, i + 1) - PriceTree.GetNode(n + 1, i)) / (Model.S(n + 1, i + 1) - Model.S(n + 1, i ));
            Y_Node = (PriceTree.GetNode(n + 1, i) - ( X_Node * Model.S(n + 1, i))) / pow( (1 + Model.GetR()  ), (1 + n) )  ;
            PriceTree.SetNode(n, i, EOVal);
            XTree.SetNode(n, i, X_Node);
            YTree.SetNode(n, i, Y_Node);

        }


    }
    return PriceTree.GetNode(0, 0);


}






double AmOption::PriceBySnell(BinModel Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree)
{
    double q = Model.RiskNeutProb();
    int N = GetN();
    PriceTree.SetN(N);
    StoppingTree.SetN(N);
    double ContVal;
    for (int i = 0; i <= N; i++)	//at expiration
    {
        PriceTree.SetNode(N, i, Payoff(Model.S(N, i)));
        StoppingTree.SetNode(N, i, 1);
    }
    for (int n = N - 1; n >= 0; n--)
    {
        for (int i = 0; i <= n; i++)
        {
            ContVal = (q * PriceTree.GetNode(n + 1, i + 1) + (1 - q) * PriceTree.GetNode(n + 1, i)) / (1 + Model.GetR());
            PriceTree.SetNode(n, i, Payoff(Model.S(n, i)));
            StoppingTree.SetNode(n, i, 1);
            if (ContVal > PriceTree.GetNode(n, i))
            {
                PriceTree.SetNode(n, i, ContVal);	// updated to calculated value
                StoppingTree.SetNode(n, i, 0);		// set not eligible for early exercise
            }
            else if (PriceTree.GetNode(n, i) == 0.0)
            {
                StoppingTree.SetNode(n, i, 0);
            }
        }
    }
    return PriceTree.GetNode(0, 0);
}

int Call::GetInputData()
{
    cout << "Enter call option data:" << endl;  int N;
    cout << "Enter steps to expiry N: "; cin >> N;
    SetN(N);
    cout << "Enter strike price K:    "; cin >> K;
    cout << endl;
    return 0;
}
double Call::Payoff(double z)
{
    if (z > K) return z - K;
    return 0.0;
}
int Put::GetInputData()
{
    cout << "Enter put option data:" << endl;  int N;
    cout << "Enter steps to expiry N: "; cin >> N;
    SetN(N);
    cout << "Enter strike price K:    "; cin >> K;
    cout << endl;
    return 0;
}
double Put::Payoff(double z)
{
    if (z < K) return K - z;
    return 0.0;
}
