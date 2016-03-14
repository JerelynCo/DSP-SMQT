#pragma once
#ifdef _WIN32
#include "opencv2/highgui/highgui.hpp"
#elif __linux__
#include <opencv2/opencv.hpp>
#endif
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;



class Image
{
private:
  Mat mmImg;
  
  // Pixel variables
  vector <double> mvBlue, mvGreen, mvRed;
public:
  int rowSize = 0;
  int colSize = 0;
   
  Image(string fn);
  Mat getImage();
  
  vector<double> getBlueVector(), getGreenVector(), getRedVector(); // For pixel-level operation
  void outputFilePixelValues(string outputFn);

  void showImage(string windowName);
  void writeToFile();
  Mat get2Dmat(String filename, vector<double> oneD);
};
