#define _CRT_SECURE_NO_DEPRECATE
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <cmath>
#include <ctime>        ]
#include <cstdlib>     

#include "Stock.h"
#include "readfiletools.h"
#include "Bootstrapping.h"
#include "ExtractYahoo.h"
#include "Stocklist.h"
#include "PlotChart.h"
#include "bootstrap_tools.h"




using namespace std;


int main()
{
    vector<double> IWB;
    vector<string> DATE;

    cout << "Hi!! We are Russell1000 Tracker, Nice to meet you!" << endl << endl << endl;
    cout << "#########################################################################" << endl;
    cout << "##    ####    ####   #############  ####     ####       ########       ##" << endl;
    cout << "##    ####    ####   #############  ####     ####      ####  ####      ##" << endl;
    cout << "##    ####    ####   ####           ####     ####     ####    ####     ##" << endl;
    cout << "##    ############   #############  ####     ####    ####      ####    ##" << endl;
    cout << "##    ############   #############  ####     ####    ####      ####    ##" << endl;
    cout << "##    ####    ####   ####           ####     ####     ####    ####     ##" << endl;
    cout << "##    ####    ####   #############  #######  #######   ####  ####      ##" << endl;
    cout << "##    ####    ####   #############  #######  #######    ########       ##" << endl;
    cout << "#########################################################################" << endl << endl;
    
    // user input N 
    bootstrap_tools bt;

    cout << "Downloading IWB data..." << endl;
    ExtractIWB2("2020-04-01", "2021-04-20", IWB, DATE);

    srand(unsigned(std::time(0))); 
    StockMap StockList;
    vector<string> TickerList;

    string path = "Allgroups.csv";
    //string path = "TestSet2.csv";
    bt.CreateStocklist(path, StockList, TickerList, DATE);
    ExtractStock2(StockList);
    bt.CheckSize(StockList);
    

    // calculate R market, and R, AR for individual stocks
    vector<double> Rmt = findIWBRmt(IWB);
    GroupOfName grouplist = divide_group(StockList);

    AbnormalMap abnormalReturn;
    bt.ComputingStockRt(abnormalReturn, StockList, Rmt);
    vector<vector<vector<double>>> Result(3, vector<vector<double>>(4));
    Result = bt.LastComputing(grouplist, Rmt, abnormalReturn);


    string input;
    int opt;
    bool cont = true;
    while (cont)
    {
        cout << endl << "Hi!! We are Russell1000 Tracker, Nice to meet you!" << endl;
        cout << endl << "Please input the number 1,2,3,4,5 to continue: " << endl;
        cout << "1: Retrieve historical price of any stocks" << endl;
        cout << "2: Stock Information such as Earning and Earning Surprise" << endl;
        cout << "3: Return Metric for each Earning Surprise group: AAR, AAR-SD, CAAR, CAAR-SD" << endl;
        cout << "4: Plot CAAR of 3 Earning Surprise groups" << endl;
        cout << "5: Exit the Program" << endl;
        cin >> input;

        while ((input.at(0) > '5' || input.at(0) <= '0'))
        {
            cout << "Invalid input! Try Again!" << endl;
            cout << "1: Retrieve historical price of any stocks" << endl;
            cout << "2: Stock Information such as Earning and Earning Surprise" << endl;
            cout << "3: Return Metric for each Earning Surprise group: AAR, AAR-SD, CAAR, CAAR-SD" << endl;
            cout << "4: Plot CAAR of 3 Earning Surprise groups" << endl;
            cout << "5: Exit the Program" << endl;
            cin >> input;
        }

        opt = stoi(input);
        string userticker;
        string selection;
        string input_one = "Y";
        string input_two = "Y";
        string input_three = "Y";
        switch (opt) {
        case 1:
            //choice 1 , historical individual stock price
            while (input_one == "Y" || input_one == "y") {
                cout << endl << "Instruction !!! " << endl;
                cout << "Input stock ticker such as ---> CHE <--- for historical price" << endl << endl;
                cout << "Input the ticker (This is Case Sensitive) :";
                cin >> userticker;
                cout << endl;
                if (StockList.find(userticker) != StockList.end())
                {
                    int sdate = StockList[userticker].Get_StartDateIndex();
                    cout << "Adjust price of stock " << userticker << endl;
                    for (auto price : StockList[userticker].Get_AdjClose()) {
                        cout << DATE[sdate++] << " " << price << endl;
                    }

                }

                else if (userticker == "IWB")
                {
                    int sdate = 0;
                    cout << "Adjust price of stock " << userticker << endl;
                    for (auto itr = IWB.begin(); itr != IWB.end(); itr++) {
                        cout << DATE[sdate++] << " " << *itr << endl;
                    }
                }
                else {
                    cout << "No Data!!! for this input ticker" << endl;
                }

                cout << endl << endl << "Do you wish to Stay for another stock price?" << endl;
                cout << "if yes type : Y or y" << endl;
                cout << "OtherWise type N or n" << endl;
                cout << "---->";
                cin >> input_one;
            }
            break;


        case 2:
            // choice 2 stock infomation
            while (input_two == "Y" || input_two == "y") {
                cout << endl << "Instruction !!! " << endl;
                cout << "Input stock ticker such as ---> CHE <--- for stock information such as EPS" << endl << endl;
                cout << "Input the ticker (This is Case Sensitive) :";
                cin >> userticker;
                cout << endl;
                if (StockList.count(userticker)) {
                    //Daily prices -- Vector checked!
                    //Cumulative daily return -- Vector checked!
                    //The group the stock belongs to
                    //Earning Announcement Date, Period ending, Estimated,Reported Earnings, Surprise and %Surprise
                    //cout << "Ticker:             " << StockList[userticker].Get_Ticker() << endl;
                    //cout << "Earnings Call Date: " << StockList[userticker].Get_AnnounceDate() << endl;
                    //cout << "Actual EPS:         " << StockList[userticker].Get_ActEPS() << endl;
                    //cout << "Estimated EPS:      " << StockList[userticker].Get_EstEPS() << endl;
                    //cout << "Surprise:           " << StockList[userticker].Get_Surprise() << endl;
                    //cout << "Group:              " << StockList[userticker].Get_Group() << endl;
                    //======================================================================================================
                    cout << StockList[userticker] << endl;
                    vector<double> cummulative((2 * bt.get_N()) + 1, 0.0);
                    cout << "Day  ||  Daily Return(%)  ||  Cumulative Return(%)" << endl;
                    for (int i = 1; i <= (2 * bt.get_N()); i++)
                    {
                        double rett = (StockList[userticker].Get_AdjClose()[i] / StockList[userticker].Get_AdjClose()[i - 1] - 1);
                        cummulative[i] = rett + cummulative[i - 1];
                        cout << (i - 2 * bt.get_N() / 2) << "          " << setprecision(6) << rett << "          " << cummulative[i] << endl;
                    }
                    cout << endl;
                }
                else {
                    cout << "No Data!!! for this input ticker" << endl;
                }

                cout << endl << endl << "Do you wish to Stay for another stock information?" << endl;
                cout << "if yes type : Y or y" << endl;
                cout << "OtherWise type N or n" << endl;
                cout << "----> ";
                cin >> input_two;


            }
            break;

        case 3:
            // choose 3 group
            while (input_three == "Y" || input_three == "y") {
                cout << endl << "Input number of the group below : " << endl;
                cout << " 0 |for miss group" << endl;
                cout << " 1 |for meet group" << endl;
                cout << " 2 |for beat group" << endl;
                cout << "---> ";


                int groupselect;
                cin >> groupselect;
                if (groupselect != 1 && groupselect != 2 && groupselect != 0) {
                    cout << "Invalid number!" << endl;
                    break;
                }

                cout << "Day    |   AAR     |    AAR-SD     |    CAAR    |    CAAR-SD " << endl;
                for (int i = 0; i < 2 * bt.get_N(); i++) {
                    cout << setprecision(0) << i - bt.get_N() << "    ";
                    cout << setprecision(6) << Result[groupselect][0][i] << "    " << Result[groupselect][1][i] << "    " << Result[groupselect][2][i] << "    " << Result[groupselect][3][i] << endl; //  DEADHERE
                }

                cout << endl << endl << "Do you wish to Stay for another stock information?" << endl;
                cout << "if yes type : Y or y" << endl;
                cout << "OtherWise type N or n" << endl;
                cout << "----> ";
                cin >> input_three;


            }
            break;

        case 4:
            //call gnuplot and plot.

            plotChart(Result[2][2], Result[1][2], Result[0][2]); 
            cout << "Plot, done!" << endl;
            break;

        case 5:
            // EXIT
            cout << "Confirmed the Exit press Y" << endl;
            cin >> selection;
            if (selection == "Y" || selection == "y")
            {
                cout << "THANK YOU!! Have a Great Day!!" << endl << endl << endl;
                cout << "################################################################################################" << endl;
                cout << "##    ############   ####    ####       #####      ####     ####  ####    ####  ############  ##" << endl;
                cout << "##    ############   ####    ####      #######     #####    ####  ####   ####   ############  ##" << endl;
                cout << "##        ####       ####    ####     #### ####    ######   ####  ####  ####    ####          ##" << endl;
                cout << "##        ####       ############    ####   ####   #######  ####  #########     ############  ##" << endl;
                cout << "##        ####       ############   #############  ####  #######  #########     ############  ##" << endl;
                cout << "##        ####       ####    ####   ####     ####  ####   ######  ####  ####            ####  ##" << endl;
                cout << "##        ####       ####    ####   ####     ####  ####    #####  ####   ####   ############  ##" << endl;
                cout << "##        ####       ####    ####   ####     ####  ####     ####  ####    ####  ############  ##" << endl;
                cout << "################################################################################################" << endl;
                return 0;
            }
            else
            {
                cout << "No Exit, Continue the application" << endl;
                break;
            }
            break;

        default:
            break;
        };
    };

    return 0;

}