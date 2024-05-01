// MinMax1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <sstream>
#include "Stock.h"
#include "constants.h"
#include "Utilities.h"

using namespace std;

void analysis(Stock aStk);
void generateStkPrices(vector<double> &v1, double rng, int days, double curPrc, bool curQtr);
double getAverage(vector<double> v1);
int main()
{
    double range = TEN_PERCENT;
    vector<double> v1, v2, v3, v4;
    bool curQtr = true;
    double iniPr = 0.0;
    iniPr = STK_PRICE;
    string stkName;
    pr("\nEnter the Stock name :\t");
    cin >> stkName;

    pr("\nEnter an initial value to generate the Stock prices :\t"); 
    cin >> iniPr;

    generateStkPrices(v1, range, QTR_DAYS, iniPr, curQtr);
    double avgPrice = getAverage(v1);
    double curStkPrice = avgPrice;   
    range = FIVE_PERCENT;
    curQtr = true;
    generateStkPrices(v1, range, QTR_DAYS, curStkPrice, curQtr);
    Stock q1Stk(stkName, v1, 0,  QTR_DAYS - 1, curStkPrice);  

    // range = FIVE_PERCENT;
    // curQtr = false;
    // double lastQtrStartPrc = v1.back();
    // generateStkPrices(v2, range, QTR_DAYS, lastQtrStartPrc, curQtr);
    // Stk q2Stk(v2, 0,  QTR_DAYS - 1, v2[0]);  

   // prVecVal(v1, v2); 
    prn();
    prVecVal(v1);
    prn();
   // pr("\nQ1 Analysis : ");
    analysis(q1Stk);   
    // pr("\n\nQ2 Analysis : ");
    // analysis(q2Stk);
    prn();
    prn();
}

void analysis(Stock aStk)
{
    Stock theStk = aStk;   
    pr("\nStock Analysis : ");    
    prl(18);
    pr("\nStock Name : " + theStk.name);
    pr("\nCurrent Stk Price : ");
    pr(theStk.curPr);
    pr("\tStk start Price : ");
    pr(theStk.qtrStartPr);
    pr("\tStk end Price : ");
    pr(theStk.qtrEndPr);
    pr("\nMax Price : ");
    pr(theStk.maxPr);
    pr("\tMin Price : ");
    pr(theStk.minPr);
    pr("\tAvg Price : ");
    pr(theStk.avgPr);
    pr("\nRange : ");
    pr(theStk.rng);
    pr("\tHigh : ");
    pr(theStk.highRng);
    pr("\tLow : ");
    pr(theStk.lowRng);

    if(theStk.avgPr > theStk.curPr && theStk.highRng > 50 && theStk.lowRng < 1 )
    {
        pr(BUY_AT_DIPS);
    }

    if(theStk.avgPr < theStk.curPr && theStk.highRng > 30){
        pr(POS_HOLD);
    }

    if(theStk.rng > 50 && (   (theStk.highRng >1 && theStk.highRng < 2) || (theStk.lowAvgRng > 1 && theStk.lowAvgRng < 2)  )  )
    {
        pr(VOLATILE_AWAY);
    }

    if(theStk.highRng < 5 && theStk.lowRng < 5)
    {
        pr(STABLE_HOLD);
    }

    if(theStk.avgPr < theStk.curPr && theStk.highRng > 30)
    {
        pr(HIGHGROWTH_ADD);
    }
    
    if(theStk.avgPr < theStk.curPr && theStk.lowRng > 30)
    {
        pr(NEGTREND_DISPOSE);
    }

     if((theStk.avgCurRng < 5)  && theStk.rng < 25)
    {
        pr(NOMOV_DISPOSE);
    }

    if(theStk.avgPr > theStk.curPr && theStk.rng > 35 && theStk.rng < 50)
    {
        pr(HIGHGROWTH_ADD);
    }

    if(theStk.rng >= 30 && theStk.rng < 40 && theStk.highRng < 25 && theStk.lowRng < 25)
    {
        pr(NOREC);
    }

    if(theStk.rng >= 40 && theStk.rng <50 && theStk.highRng > 23  && theStk.highRng < 30 && theStk.lowRng > 23  && theStk.lowRng < 30)
    {
        pr(NOREC);
    }

    if(theStk.highAvgRng < 3)
    {
        pr(GROWPOT_ADD);
    }

    if(theStk.lowAvgRng < 3)
    {
        pr(RISK_DISPOSE);
    }
}

void generateStkPrices(vector<double> &v1, double rng, int days, double curPrc, bool curQtr)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis((-1 * rng), rng);
    double prevPrice = 0;
    double curPrice = curPrc;
    v1.clear();
    for (int i = 0; i <= days; i++)
    {
        if (curQtr && i < days)
        {
            v1.push_back(curPrice);
        }
        else if (!curQtr && i == 0)
        {
            // v1.push_back(0);
        }
        else if (!curQtr && i > 0)
        {
            v1.push_back(curPrice);
        }       
        prevPrice = (curPrice / (1 + dis(gen)));
        prevPrice = round(prevPrice * 100.0) / 100.0;
        curPrice = prevPrice;
    }
}

double getAverage(vector<double> v1)
{
    double avg = 0;
    for (double val : v1)
    {
        avg += val;
    }
    avg = avg / v1.size();
    return avg;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
