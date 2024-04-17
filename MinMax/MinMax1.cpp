// MinMax1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct MinMax
{
    double min;
    double max;
};

const double STK_PRICE = 163.75;
const double TEN_PERCENT = 0.1;
const double FIVE_PERCENT = 0.05;
const int QTR_DAYS = 60;

void analysis(double min, double max, double avg, double cur);
void generateStkPrices(vector<double> &v1, double low, double high, int days);
double getAverage(vector<double> v1);
MinMax findMinMax(vector<double> &v1, int low, int high);
void prVecVal(vector<double> v1);
void pr(double value);
void pr(string msg);
void prn();
int main()
{
    double low = -1* TEN_PERCENT;
    double high = TEN_PERCENT;
    vector<double> v1;
    generateStkPrices(v1, low, high, QTR_DAYS);
    double avgPrice = getAverage(v1);
    MinMax minMax = findMinMax(v1, 0, QTR_DAYS-1);
    double min = minMax.min;
    double max = minMax.max;
    prVecVal(v1);
    pr("\nMin : " + to_string(min));
    pr("\nMax : " + to_string(max));
    pr("\nStk Price : " + to_string(STK_PRICE) + "\nAvg price : " + to_string(avgPrice));  
    analysis(min, max, avgPrice, STK_PRICE) ;
}

void analysis(double min, double max, double avg, double cur)
{
      double rangeVar = ((max-min)/cur)*100;
      double maxVar = ((max-cur)/avg)*100;
      double minVar = ((cur-min)/avg)*100;

      pr("\n Range : " + to_string(rangeVar)); 
      pr("\n High : " + to_string(maxVar)); 
      pr("\n Low : " + to_string(minVar)); 
}


void generateStkPrices(vector<double> &v1, double low, double high, int days)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(low, high);   
    double prevPrice = 0;
    double curPrice = STK_PRICE; 
    
    for (int i = 0; i < days; i++)
    {  
        v1.push_back(curPrice);      
        pr("\n" + to_string(v1[i]));
        prevPrice = (curPrice /(1 + dis(gen)));
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

MinMax findMinMax(vector<double> &v1, int low, int high)
{
    MinMax result;
    if (low == high)
    {
        result.min = v1[low];
        result.max = v1[low];
        return result;
    }

    if ((high - low) == 1)
    {
        result.min = min(v1[low], v1[high]);
        result.max = max(v1[low], v1[high]);
        return result;
    }

    int mid = (low + high) / 2;
    MinMax left = findMinMax(v1, low, mid);
    MinMax right = findMinMax(v1, mid + 1, high);

    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);
    return result;
}

void prVecVal(vector<double> v1)
{
    for (int i = (v1.size() -1);i >=0;  --i)
    {
        pr("" + to_string(i) + " ) " + to_string(v1[i]));
        prn();
    }
}

void pr(double value)
{
    ostringstream oss;
    oss << value;
    pr(oss.str());
}

void pr(string msg)
{
    cout << msg;
}

void prn()
{
    pr("\n");
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
