// MinMax1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stock
{
    public:
    string name;
    double minPr = 0.0;
    double maxPr = 0.0;
    double avgPr = 0.0;
    double curPr = 0.0;
    double rng = 0.0;
    double avgCurRng = 0.0;
    double highAvgRng = 0.0;
    double lowAvgRng = 0.0;
    double highRng = 0.0;
    double lowRng = 0.0;
    double qtrStartPr = 0.0;
    double qtrEndPr = 0.0;
    public : Stock(){};
    public : Stock(string stkName, vector<double> &v1, int low, int high, double curPr)
    {
        name = stkName;
        this->curPr = curPr;
        double min, max;
        setQtrMinMax(v1, low, high, min, max);
        minPr = min;
        maxPr = max;
        setAvgPr(v1);
        qtrEndPr = v1[0];
        qtrStartPr = v1[v1.size() - 1];
        setStats();
    }
    void setQtrMinMax(vector<double> &v1, int low, int high, double &minVal, double &maxVal)
    {
        if (low == high)
        {
            minVal = v1[low];
            maxVal = v1[low];
            return;
        }

        if ((high - low) == 1)
        {
            minVal = min(v1[low], v1[high]);
            maxVal = max(v1[low], v1[high]);
            return;
        }

        int mid = (low + high) / 2;
        double min1, max1, min2, max2;
        setQtrMinMax(v1, low, mid, min1, max1);
        setQtrMinMax(v1, mid + 1, high, min2, max2);
        minVal = min(min1, min2);
        maxVal = max(max1, max2);
        return;
    }

    void setAvgPr(vector<double> v1)
    {
        double avg = 0;
        for (double val : v1)
        {
            avg += val;
        }
        avg = avg / v1.size();
        avgPr = avg;
    }

    void setStats()
    {
        rng = ((maxPr - minPr) / curPr) * 100;
        highRng = ((maxPr - curPr) / avgPr) * 100;
        lowRng = ((curPr - minPr) / avgPr) * 100;
        avgCurRng = ((avgPr-curPr)/avgPr) * 100;
        highAvgRng = abs(((maxPr - avgPr) / avgPr)) * 100;
        lowAvgRng = abs(((avgPr - minPr) / avgPr)) * 100;
    }
};
