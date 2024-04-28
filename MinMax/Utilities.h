#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
// Function declarations
void pr(std::string msg);
void prn();
void prVecVal(std::vector<double> v1, std::vector<double> v2);
void prVecVal(std::vector<double> v1);
void pr(double value);
void prl(int n);
//-------------------------------------------
void pr(string msg)
{
    cout << msg;
}

void prn()
{
    pr("\n");
}
// 
void prVecVal(vector<double> v1, vector<double> v2)
{
    prn();
    for (int i = (v1.size() - 1); i >= 0; --i)
    {
        pr(" " + to_string(v1[i]));
        pr("\t\t" + to_string(v2[i]));
        prn();
    }
}

void prVecVal(vector<double> v1)
{
    for (int i = (v1.size() - 1); i >= 0; --i)
    {
        pr(" ");
        pr(v1[i]);       
        prn();
    }
}

void prd(double value)
{
    ostringstream oss;
    oss << value;
    pr(oss.str());
}

void pr(double value)
{
    cout << fixed << setprecision(2) << value;    
}

void prl(int n)
{
    prn();
    for(int i = 0; i < n; i++)
    pr("-");
}
#endif // MY_HEADER_FILE_H