#include <iostream>
#include "Image.h"

using namespace std;

int main() {
  string blueFn, greenFn, redFn;
  blueFn = "blue.csv";
  greenFn = "green.csv";
  redFn = "red.csv";

  Image origImage("toptal.png");
  origImage.outputFilePixelValues(blueFn); // Output file for blue vector

  origImage.showImage("Orig");

  cin.get();
  origImage.writeToFile();
}


