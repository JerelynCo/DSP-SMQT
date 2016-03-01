#include "adspImage.h"


adspImage::adspImage(vector<double> pixelVals)
{
  pixelValues = pixelVals;
  // allocate space and assign zeroes
  vector<long unsigned int> v_int(pixelVals.begin(), pixelVals.end());
  outputValues = v_int;
  std::fill(outputValues.begin(), outputValues.end(), 0);
}


adspImage::~adspImage()
{
}

double adspImage::calculateMean(vector<double> v)
{
  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double mean = sum / v.size();

  return mean;
}

int adspImage::addBit(long unsigned int x, bool shiftByOne)
{
  if (shiftByOne)
  {
    return x << 1 | 1;
  }
  else
  {
    return x << 1;
  }
}
//
//void adspImage::calculateSMQT(vector<double> v, int L)
//{
//  if (L < 1)
//  {
//    return; // append missing bits for quantization level here
//  }
//  else
//  {
//    double mean = calculateMean(v);
//    // store indices of pixelvalues that are lower/higher than mean
//    vector<int> lowpos, highpos; 
//    vector<double> lowValues, highValues;
//    int counter = 0;
//    for (double &x : v)
//    {
//      if (x <= mean)
//      {
//        lowpos.emplace_back(counter);
//      }
//      else 
//      {
//        highpos.emplace_back(counter);
//      }
//      counter++;
//    }
//    for (int& x : lowpos)
//    {
//      outputValues.at(x) = addBit(outputValues.at(x), false);
//      lowValues.emplace_back(v.at(x));
//    }
//    for (int& x : highpos)
//    {
//      outputValues.at(x) = addBit(outputValues.at(x), true);
//      highValues.emplace_back(v.at(x));
//    }
//    calculateSMQT(lowValues, L-1); // you forgot about the lowpos,highpos -_-
//    calculateSMQT(highValues, L-1);
//    
//  }
//}

void adspImage::calculateSMQT(vector<unsigned int> inputVectorPositions, int L)
{
  if (L == 0)
  {
    return;
  }

  else
  {
    vector<double> inputVector;
    for (unsigned int &x : inputVectorPositions)
    {
      inputVector.emplace_back(pixelValues.at(x));
    }
    double mean = calculateMean(inputVector);
    vector<unsigned int> lowpos, highpos;
    int counter = 0;
    for (double &x : inputVector)
    {
      if (x <= mean)
      {
        lowpos.emplace_back(counter);
        outputValues.at(counter) = addBit(outputValues.at(counter), false);
      }
      else 
      {
        highpos.emplace_back(counter);
        outputValues.at(counter) = addBit(outputValues.at(counter), true);
      }
      counter++;
    }
    calculateSMQT(lowpos, L - 1);
    calculateSMQT(highpos, L - 1);
  }
}


vector<double> adspImage::getPixelValues()
{
  return pixelValues;
}

void adspImage::outputCSV()
{
  ofstream file;
  file.open("smqt.csv");
  for (int i = 0; i < outputValues.size(); i++)
  {
    file << outputValues.at(i) << "," << endl;
  }
  file.close();
}