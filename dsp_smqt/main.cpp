#include <iostream>
#include "Image.h"
#include "adspImage.h"

using namespace std;

int main() {
  //string blueFn, greenFn, redFn;
  //blueFn = "blue.csv";
  //greenFn = "green.csv";
  //redFn = "red.csv";

  Image origImage("toptal.png");
  //origImage.outputFilePixelValues(blueFn); // Output file for blue vector

  origImage.showImage("Orig");
  cout << "Create adspImage Object.." << endl;
  adspImage blue(origImage.getBlueVector());
  cout << "Calculate SMQT.." << endl;
  blue.calculateSMQT(blue.getPixelValues(), 0);
  cout << "Calculation Done!! CSV File created." << endl;
  blue.outputCSV();
  cin.get();
  //origImage.writeToFile();
}


