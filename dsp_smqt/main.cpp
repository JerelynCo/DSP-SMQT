#include <iostream>
#include "Image.h"
#include "adspImage.h"

using namespace std;

int main() {
  string blueFn, greenFn, redFn;
  blueFn = "blue.csv";
  //greenFn = "green.csv";
  //redFn = "red.csv";

  Image origImage("toptal.png");
  origImage.outputFilePixelValues(blueFn); // Output file for blue vector

  //origImage.showImage("Orig");
  cout << "Create adspImage Object.." << endl;

  adspImage blue(origImage.getBlueVector());
  adspImage green(origImage.getGreenVector());
  adspImage red(origImage.getRedVector());
  cout << "Calculate SMQT.." << endl;

  vector<unsigned int> bluePixelPositions(blue.getPixelValues().size());
  iota(begin(bluePixelPositions), end(bluePixelPositions), 0);
  vector<unsigned int> greenPixelPositions(green.getPixelValues().size());
  iota(begin(greenPixelPositions), end(greenPixelPositions), 0);
  vector<unsigned int> redPixelPositions(red.getPixelValues().size());
  iota(begin(redPixelPositions), end(redPixelPositions), 0);

  blue.calculateSMQT(bluePixelPositions, 8);
  green.calculateSMQT(greenPixelPositions, 8);
  red.calculateSMQT(redPixelPositions, 8);
  vector<double> blueOut, redOut, greenOut;
  blueOut = blue.getOutputValues();
  greenOut = green.getOutputValues();
  redOut = red.getOutputValues();
  cout << "Calculation Done!! Combining color channels.." << endl;
  vector<Mat> channels;
  auto imageSize = origImage.getImage().size();
  Mat fin_img, matGreen(imageSize, CV_8UC1), matRed(imageSize, CV_8UC1), matBlue(imageSize, CV_8UC1);
  int counter = 0;
  for (int i = 0; i < matGreen.rows; i++)
  {
    for (int j = 0; j < matGreen.cols; j++)
    {
      matGreen.at<unsigned char>(i, j) = greenOut.at(counter);
      matBlue.at<unsigned char>(i, j) = blueOut.at(counter);
      matRed.at<unsigned char>(i, j) = redOut.at(counter);
      counter++;
    }
  }
  channels.push_back(matBlue);
  channels.push_back(matGreen);
  channels.push_back(matRed);
  merge(channels, fin_img);
  namedWindow("Result", 1);
  namedWindow("Orig", 1);
  imshow("Result", fin_img);
  imshow("Orig", origImage.getImage());
  waitKey(0);
  return 0;
}


