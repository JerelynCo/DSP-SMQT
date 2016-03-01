#pragma once
#include <vector>
#include <numeric>
#include <iostream>
#include <fstream>

using namespace std;

class adspImage
{
  private:
    int recursion_count = 0;
    vector<double> pixelValues;
    vector<long unsigned int> outputValues;
    double calculateMean(vector<double> v);
    int addBit(long unsigned int x, bool shiftByOne);
    
  public:
    adspImage(vector<double> pixelVals);
    ~adspImage();
    void calculateSMQT(vector<unsigned int> v, int L=8);
    vector<double> getPixelValues();
    void outputCSV();
};

