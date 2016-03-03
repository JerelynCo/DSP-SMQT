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
  cout << "Calculate SMQT.." << endl;

  vector<unsigned int> bluePixelPositions(blue.getPixelValues().size());
  iota(begin(bluePixelPositions), end(bluePixelPositions), 0);

  blue.calculateSMQT(bluePixelPositions, 8);

  imshow("Orig", origImage.getImage());
  waitKey(0);
  return 0;
}


