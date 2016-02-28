#pragma once
#include <vector>
#include <numeric>
#include <iostream>
#include <fstream>

using namespace std;

class adspImage
{
  private:
    vector<double> pixelValues;
    vector<int> outputValues;
    double calculateMean(vector<double> v);
    int addBit(int x, bool shiftByOne);
    
  public:
    adspImage(vector<double> pixelVals);
    ~adspImage();
    void calculateSMQT(vector<double> v, double prevMean);
    vector<double> getPixelValues();
    void outputCSV();
};

