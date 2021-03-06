#include "Image.h"

Image::Image(string fn)
{
  // Loading of image
  mmImg = imread(fn, CV_LOAD_IMAGE_COLOR);

  if (mmImg.empty())
  {
    cout << "Image not loaded. Make sure correct filename and/or directory entered." << endl;
  }

  Vec3f vIntensity; // Temporary vector to hold three pixels intensities

  // Iterating across rows and columns to get BGR values (blue, green, red)
  for (int row = 0; row < mmImg.rows; row++)
  {
    for (int col = 0; col < mmImg.cols; col++)
    {
      vIntensity = mmImg.at<Vec3b>(row, col);

      mvBlue.push_back(vIntensity.val[0]);
      mvGreen.push_back(vIntensity.val[1]);
      mvRed.push_back(vIntensity.val[2]);
    }
  }
}

Mat Image::getImage()
{
  return mmImg;
}

vector<double> Image::getBlueVector()
{
  return mvBlue;
}

vector<double> Image::getGreenVector()
{
  return mvGreen;
}

vector<double> Image::getRedVector()
{
  return mvRed;
}

void Image::outputFilePixelValues(string outputFn){
  vector<double> vColorVector;
  ofstream file;

  if (outputFn.compare("blue.csv") == 0)
  {
    vColorVector = mvBlue;
  }

  else if (outputFn.compare("green.csv") == 0)
  {
    vColorVector = mvGreen;
  }

  else if (outputFn.compare("red.csv") == 0)
  {
    vColorVector = mvRed;
  }

  else
  {
    cout << "Assign a valid output filename (R: red.csv, G: green.csv, B: blue.csv)";
    return; // "break" out of method
  }

  file.open(outputFn);
  for (int i = 0; i < vColorVector.size(); i++)
  {
    file << vColorVector.at(i) << "," << endl;
  }
  file.close();
}

void Image::showImage(string windowName)
{
  namedWindow(windowName, CV_WINDOW_AUTOSIZE);
  imshow(windowName, mmImg);
  waitKey(0);
}

void Image::writeToFile()
{
  vector<int> vCompression_params;
  int iCompression = 9;
  bool bSuccess;

  // Writing image to file
  vCompression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  vCompression_params.push_back(iCompression);
  bSuccess = imwrite("toptal_written.png", mmImg, vCompression_params);
  if (!bSuccess){
    cout << "ERROR : Failed to write the image" << endl;
  }
}
