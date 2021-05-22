#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Stock.h"
#include "Stocklist.h"
#include"bootstrap_tools.h"

using namespace std;


vector<double> findIWBRmt(vector<double> iwb)
{
    vector<double> IWBTradeRt;

    for (int i = 0; i < iwb.size() - 1; i++)
    {
        double temp = (iwb[i + 1] - iwb[i]) / iwb[i];
        IWBTradeRt.push_back(temp);
    }
    cout << "Rmt calculation done" << endl;
    return IWBTradeRt;
}
// we use this to compute return for each ticker
void bootstrap_tools::ComputingStockRt(AbnormalMap& abnormalReturn, StockMap& StockList, const vector<double>& Rmt)
{
    for (auto itr = StockList.begin(); itr != StockList.end(); itr++) {
        vector<double> abnormal;
        vector<double> stockPrice = itr->second.Get_AdjClose();
        string stockName = itr->first;
        int startDate = itr->second.Get_StartDateIndex();

        for (int i = 0; i < 2 * N; i++)
        {
            double first = stockPrice[i];
            double second = stockPrice[i + 1];

            double Rit = (second - first) / first;
            itr->second.Set_Return(Rit);

            double ARit = Rit - Rmt[startDate + 1+i];
            itr->second.Set_AbnormalReturn(ARit);
            abnormal.push_back(ARit);
        }
        abnormalReturn.insert({ stockName,abnormal });
    };
    cout << "calculationStockReturn" << endl;
}

// we use this to compute AAR for each group
vector<double> bootstrap_tools::ComputingAAR(AbnormalMap& abnormalReturn)
{
    vector<double> calculation(2*N, 0.0); //Create a vector of size 2*N with all values as 0.0
    for (auto it = abnormalReturn.begin(); it != abnormalReturn.end(); it++) {
        for (int i = 0; i < 2*N; i++) {
            calculation[i] += it->second[i] / random; //random is M
        }
    }
    return calculation;
}
//=============================================================================

// we use this to compute the CAAR based on each day.
vector<double> bootstrap_tools::ComputingCAAR(vector<double> &calculation)
{
    vector<double> calculationCAAR(2 * N, 0.0); //Create a vector of size 2*N with all values as 0.0
    calculationCAAR[0] = calculation[0];

    for (int i = 1; i < calculation.size(); i++) {
        calculationCAAR[i] = calculationCAAR[i - 1] + calculation[i];
    }
    return calculationCAAR;
}

//operator overloading
// we use this to compute addition of vectors.
vector<double> operator +(vector<double>& V1, const vector<double>& V2) {
    for (int i = 0; i < V1.size(); i++) {
        // This is for calculating average AAR and CAAR, you have 2N days of data for each stock, and 50 stocks for each group.
        V1[i] = V1[i] + V2[i] / random; // change to 50
    }
    return V1;
}
// we use this to compute repeatx2 and vector.
vector<double> operator+(vector<vector<double>>& V1, vector<double>& V2) {
    for (int i = 0; i < V2.size(); i++)//2N 
    {
        for (int j = 0; j < V1.size(); j++) //repeat 
        {
            // This is used to calculate the AARSD and CAARSD
            V2[i] = V2[i] + V1[j][i] / V1.size();
        }
    }
    return V2;
}


// we use this to compute the subtraction between container and vector.
vector<vector<double>> operator -(vector<vector<double>>& V1, const vector<double>& V2) {
    for (int i = 0; i < V2.size(); i++) {
        for (int j = 0; j < V1.size(); j++) {
            V1[j][i] = V1[j][i] - V2[i];
        }
    }
    return V1;
}
// we use this to compute the matrix square.
vector<vector<double>> operator ^(vector<vector<double>>& V1, vector<vector<double>>& V2)
{
    for (int i = 0; i < V1[0].size(); i++) {
        for (int j = 0; j < V1.size(); j++) {
            V1[j][i] = V2[j][i] * V2[j][i];
        }
    }
    return V1;
}

// This is used to calculate the square root of the vector.
vector<double> ComputingSQRT(vector<double>& V1)
{
    for (int i = 0; i < V1.size(); i++) {
        V1[i] = sqrt(V1[i]);
    }
    return V1;

}


vector<vector<vector<double>>> bootstrap_tools::LastComputing(GroupOfName &grouplist, vector<double> &Rmt, AbnormalMap &abnormalReturn)
{
    vector<double> temp(2 * N, 0.0);
    vector<double> group1AAR(2 * N, 0.0);
    vector<double> group1AARsd(2 * N, 0.0);
    vector<double> group2AAR(2 * N, 0.0);
    vector<double> group2AARsd(2 * N, 0.0);
    vector<double> group3AAR(2 * N, 0.0);
    vector<double> group3AARsd(2 * N, 0.0);
    vector<vector<double>> group1AARtemp(repeat, temp);
    vector<vector<double>> group2AARtemp(repeat, temp);
    vector<vector<double>> group3AARtemp(repeat, temp);
    vector<vector<double>> group1CAARtemp(repeat, temp);
    vector<vector<double>> group2CAARtemp(repeat, temp);
    vector<vector<double>> group3CAARtemp(repeat, temp);
    vector<double> group1CAAR(2 * N, 0.0);
    vector<double> group1CAARsd(2 * N, 0.0);
    vector<double> group2CAAR(2 * N, 0.0);
    vector<double> group2CAARsd(2 * N, 0.0);
    vector<double> group3CAAR(2 * N, 0.0);
    vector<double> group3CAARsd(2 * N, 0.0);



    vector<vector<vector<double>>> Result(3, vector<vector<double>>(4));

    // we use this to compute all the abonormal return for all stock.
    // and simulate for fourty times.
    for (int j = 0; j < repeat; j++) {
        // shuffle the stocks.

        GroupOfName RandomSet = SelectRandom(grouplist);

        //we use this to compute abnormal return for miss group.
        AbnormalMap AbRt1;
        //we use this to compute abnormal return for meet group.
        AbnormalMap AbRt2;
        //we use this to compute abnormal return for the beat group.
        AbnormalMap AbRt3;

        // we use this to compute divide the stock in the abnormal return map(abnormalReturn) 
        // into three groups based on the group data we have in RandomSet.

        for (int i = 0; i < 3; i++) {
            for (auto it = RandomSet[i].begin(); it != RandomSet[i].end(); it++) //go over each group
            { 
                if (abnormalReturn.find(*it) != abnormalReturn.end()) {
                    string name = *it;
                    if (i == 0) {
                        AbRt1.insert({ name,abnormalReturn[name] });
                    }
                    else if (i == 1) {
                        AbRt2.insert({ name,abnormalReturn[name] });
                    }
                    else {
                        AbRt3.insert({ name,abnormalReturn[name] });
                    }
                }
            }
        }


        //we use this to compute the average abnormal return of each group.
        vector<double> MeanAbRt1;
        MeanAbRt1 = ComputingAAR(AbRt1);
        vector<double> MeanAbRt2;
        MeanAbRt2 = ComputingAAR(AbRt2);
        vector<double> MeanAbRt3;
        MeanAbRt3 = ComputingAAR(AbRt3);



        // we use this to compute the abnormal return of each stock in every simulation(repeatx2N)
        group1AARtemp[j] = MeanAbRt1;
        group2AARtemp[j] = MeanAbRt2;
        group3AARtemp[j] = MeanAbRt3;


        // we use this to compute average AAR for three groups(# simulations) like 1 value for each, vector<double> group1AAR(2 * N, 0.0);
        group1AAR = operator+ (group1AAR, MeanAbRt1);
        group2AAR = operator+ (group2AAR, MeanAbRt2);
        group3AAR = operator+ (group3AAR, MeanAbRt3);

        //we use this to compute average CAAR for 3 groups (30 simulation).
        vector<double> CuAbRt1;
        vector<double> CuAbRt2;
        vector<double> CuAbRt3;

        CuAbRt1 = ComputingCAAR(MeanAbRt1);
        CuAbRt2 = ComputingCAAR(MeanAbRt2);
        CuAbRt3 = ComputingCAAR(MeanAbRt3);

        //This is the container that contains the CAAR of each stock in every simulation
        group1CAARtemp[j] = CuAbRt1;
        group2CAARtemp[j] = CuAbRt2;
        group3CAARtemp[j] = CuAbRt3;

        //These are the calculation of average CAAR for three groups (# simulations)
        group1CAAR = operator+(group1CAAR, CuAbRt1);
        group2CAAR = operator+(group2CAAR, CuAbRt2);
        group3CAAR = operator+(group3CAAR, CuAbRt3);
       // cout << "CAAR3" << endl;

    }


    //SD formula: sqrt(sum([x_i - average x)^2]/n)

    group1AARtemp = group1AARtemp - group1AAR;
    group1AARtemp = group1AARtemp ^ group1AARtemp;
    group1AARsd = operator+(group1AARtemp, group1AARsd);
    group1AARsd = ComputingSQRT(group1AARsd);

    group2AARtemp = group2AARtemp - group2AAR;
    group2AARtemp = group2AARtemp ^ group2AARtemp;
    group2AARsd = operator+(group2AARtemp, group2AARsd);
    group2AARsd = ComputingSQRT(group2AARsd);


    group3AARtemp = group3AARtemp - group3AAR;
    group3AARtemp = group3AARtemp ^ group3AARtemp;
    group3AARsd = operator+(group3AARtemp, group3AARsd);
    group3AARsd = ComputingSQRT(group3AARsd);

    group1CAARtemp = operator-(group1CAARtemp, group1CAAR);
    group1CAARtemp = operator ^(group1CAARtemp, group1CAARtemp);
    group1CAARsd = operator+(group1CAARtemp, group1CAARsd);
    group1CAARsd = ComputingSQRT(group1CAARsd);

    group2CAARtemp = operator-(group2CAARtemp, group2CAAR);
    group2CAARtemp = operator ^(group2CAARtemp, group2CAARtemp);
    group2CAARsd = operator+(group2CAARtemp, group2CAARsd);
    group2CAARsd = ComputingSQRT(group2CAARsd);

    group3CAARtemp = operator-(group3CAARtemp, group3CAAR);
    group3CAARtemp = operator ^(group3CAARtemp, group3CAARtemp);
    group3CAARsd = operator+(group3CAARtemp, group3CAARsd);
    group3CAARsd = ComputingSQRT(group3CAARsd);



    // Assign the result of 30 simulations for AAR, AARSD, CAAR, CAARSD into the matrix that is created.(The form of the matrix will be 3*4*10).

    Result[0][0] = group1AAR;
    Result[0][1] = group1AARsd;
    Result[0][2] = group1CAAR;
    Result[0][3] = group1CAARsd;

    Result[1][0] = group2AAR;
    Result[1][1] = group2AARsd;
    Result[1][2] = group2CAAR;
    Result[1][3] = group2CAARsd;

    Result[2][0] = group3AAR;
    Result[2][1] = group3AARsd;
    Result[2][2] = group3CAAR;
    Result[2][3] = group3CAARsd;


    return Result;
}
