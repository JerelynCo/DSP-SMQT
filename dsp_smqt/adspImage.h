#pragma once
#include <vector>
#include <numeric>
#include <iostream>
#include <fstream>
using namespace std;

class adspImage
{
  private:
	
	int L = 0;
    vector<double> pixelValues;
    vector<unsigned int> outputValues;
    double calculateMean(vector<double> v);
    int addBit(unsigned int x, bool shiftByOne);
	
    
  public:
    adspImage(vector<double> pixelVals);
    ~adspImage();

    void calculateSMQT(vector<unsigned int>& v,int L);
    vector<double> getPixelValues();
    void outputCSV();
    vector<double>getOutputValues(int L);
	void padBit(int quanL);
	
};

