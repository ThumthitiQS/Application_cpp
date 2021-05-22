#include "Solver03.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;




class Bond{
private:
    double F;
    double T;
    double C;
    double P;

public:
    Bond(double F_, double T_, double C_, double P_) { F = F_, T = T_, C = C_, P = P_; }
    double Value(double y) {
        double C_cum = 0;
        double Pr;
        for (int n = 1; n <= T; n++) {
            C_cum += C * exp(-y * n);
        }
        Pr = C_cum + (F * exp(-y * T));
        return Pr;
    }

    double Deriv(double y) {
        double C_cum2 = 0;
        double dv;
        for (int n = 1; n <= T; n++) {
            C_cum2 += (C * -n) * exp(-y * n);
        }
        dv = C_cum2 + (F * -T) * exp(-y*T);
        return dv;
    }
    
};


int main()
{
    double F = 100.0;
    double T = 3.0;
    double C = 1.2;
    double P = 98.56;

    double Acc = 0.0001;
    double LEnd = 0.0;
    double REnd = 1.0;
    double Guess = 0.2;

    Bond Bond_1(F,T,C,P);
    cout << setiosflags(ios::fixed) << setprecision(4);

    cout << "F = " << F << endl;
    cout << "T = " << T << endl;
    cout << "coupons:" << endl;
    for (int i = 1; i <= T; i++)
        cout << "C" + to_string(i-1) + " = " << C << endl;
    cout << "tenors:" << endl;
    for (int i = 1; i <= T; i++)
        cout << "T" + to_string(i-1) + " = " << i << endl;
    cout << "P =" << P << endl << endl;
    cout << "Yield by bisection method: " << SolveByBisect<Bond>(&Bond_1, P, LEnd, REnd, Acc) << endl;
    cout << "Yield by Newton-Raphson method: " << SolveByNR<Bond>(&Bond_1,P,Guess,Acc)
        << endl;

    return 0;
}


/* 


F = 100.0000
T = 3.0000
coupons:
C0 = 1.2000
C1 = 1.2000
C2 = 1.2000
tenors :
    T0 = 1
    T1 = 2
    T2 = 3
    P = 98.5600

    Yield by bisection method : 0.0168
    Yield by Newton - Raphson method : 0.0168

*/