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
    vector<long unsigned int> outputValues;
    double calculateMean(vector<double> v);
    int addBit(long unsigned int x, bool shiftByOne);
    
  public:
    adspImage(vector<double> pixelVals);
    ~adspImage();

    void calculateSMQT(vector<unsigned int> v, int L=8);
    vector<double> getPixelValues();
    void outputCSV();
    vector<double> getOutputValues();
};

