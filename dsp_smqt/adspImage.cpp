#include "adspImage.h"

adspImage::adspImage(vector<double> pixelVals)
{
  pixelValues = pixelVals;
  // allocate space and assign zeroes
  vector<unsigned int> v_int(pixelVals.begin(), pixelVals.end());
  outputValues = v_int;
  fill(outputValues.begin(), outputValues.end(), 0);
}

adspImage::~adspImage()
{
}

double adspImage::calculateMean(vector<double> v)
{
  double sum = accumulate(v.begin(), v.end(), 0.0);
  double mean = sum / v.size();
  return mean;
}

int adspImage::addBit(unsigned int x, bool insertOne)
{
	if (insertOne)
  {
    return x << 1 | 1;
  }
  else
  {
    return x << 1;
  }
}

void adspImage::calculateSMQT(vector<unsigned int>& inputVectorPositions, int L) {
  if (L == 0)
  {
    return;
  }
  else
  {
    int pos;
    vector<double> inputVector;

    for (unsigned int &x : inputVectorPositions) {
      inputVector.emplace_back(pixelValues.at(x));
    }

    double mean = calculateMean(inputVector);
    vector<unsigned int> lowpos, highpos;

    for(int i = 0; i < inputVectorPositions.size(); i++){
      pos = inputVectorPositions.at(i);
      if(pixelValues.at(pos) <= mean){
        lowpos.emplace_back(pos);
        outputValues.at(pos) = addBit(outputValues.at(pos), false);
      }
      else {
        highpos.emplace_back(pos);
        outputValues.at(pos) = addBit(outputValues.at(pos), true);
      }
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
    file << outputValues.at(i) << endl;
  }
  cout << outputValues.size();
  file.close();
}

vector<double> adspImage::getOutputValues(int L)
{
  //make 2d vector
  padBit(L);
  vector<double> out(outputValues.begin(), outputValues.end());
  return out;
}
//for padding of 
void adspImage::padBit(int quanL){
	unsigned int padding,pad = 0;
	for (int i = 0; i < outputValues.size(); i++){
		for (int j = 0; j < 8-quanL; j++){
			//shift bits to the left add 0
			outputValues.at(i) = addBit(outputValues.at(i),false);
		}
	}
}

void adspImage::getPicDiff(string filename, vector<double> outputVector)
{
	ofstream file;
	file.open(filename);
	for (int i = 0; i < outputVector.size(); i++)
	{
		file << outputVector.at(i) << "," << endl;
	}
	file.close();

}
