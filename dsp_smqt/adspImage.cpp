#include "adspImage.h"


adspImage::adspImage(vector<double> pixelVals)
{
  pixelValues = pixelVals;
  // allocate space and assign zeroes
  vector<int> v_int(pixelVals.begin(), pixelVals.end());
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

int adspImage::addBit(int x, bool shiftByOne)
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

void adspImage::calculateSMQT(vector<double> v, double prevMean)
{
  if (v.size() <= 1)
  {
    return; // append missing bits for quantization level here
  }
  else
  {
    double mean = calculateMean(v);
    // store indices of pixelvalues that are lower/higher than mean
    vector<int> lowpos, highpos; 
    vector<double> lowValues, highValues;
    int counter = 0;
    for (double &x : v)
    {
      if (x <= mean)
      {
        lowpos.emplace_back(counter);
      }
      else 
      {
        highpos.emplace_back(counter);
      }
      counter++;
    }
    for (int& x : lowpos)
    {
      outputValues.at(x) = addBit(outputValues.at(x), false);
      lowValues.emplace_back(v.at(x));
    }
    for (int& x : highpos)
    {
      outputValues.at(x) = addBit(outputValues.at(x), false);
      highValues.emplace_back(v.at(x));
    }
    if (mean == prevMean)
    {
      return;
    }
    else
    {
      calculateSMQT(lowValues, mean);
      calculateSMQT(highValues, mean);
    }
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