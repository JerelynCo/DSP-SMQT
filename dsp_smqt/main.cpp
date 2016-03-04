#include <iostream>
#include "Image.h"
#include "adspImage.h"

using namespace std;

int main() {
	String filename = "toptal.png";
	  Image origImage(filename);
	  vector<Mat> BGR;
	  Mat finImage(origImage.rowSize, origImage.colSize, CV_64FC1);
	  string blueFn, greenFn, redFn;
	  blueFn = "blue.csv";
	  //greenFn = "green.csv";
	  //redFn = "red.csv";

	  
	  imshow("Orig", origImage.getImage());
	  //origImage.outputFilePixelValues(blueFn); // Output file for blue vector

	  //origImage.showImage("Orig");
	  cout << "Create adspImage Object.." << endl;

	  //blue is a type
  
	  adspImage red(origImage.getBlueVector());
	  adspImage green(origImage.getGreenVector());
	  adspImage blue(origImage.getRedVector());
	  cout << "Calculate SMQT.." << endl;

	  vector<unsigned int> redPixelPositions(red.getPixelValues().size());
	  iota(begin(redPixelPositions), end(redPixelPositions), 0);

	  vector<unsigned int> greenPixelPositions(green.getPixelValues().size());
	  iota(begin(greenPixelPositions), end(greenPixelPositions), 0);

	  vector<unsigned int> bluePixelPositions(blue.getPixelValues().size());
	  iota(begin(bluePixelPositions), end(bluePixelPositions), 0);

	  red.calculateSMQT(redPixelPositions, 8);
	  green.calculateSMQT(greenPixelPositions, 8);
	  blue.calculateSMQT(bluePixelPositions, 8);
	  //put code to output the picture
	  
	  
	  	  
	  vector<double> blueVal = blue.getOutputValues();
	  vector<double> greenVal = green.getOutputValues();
	  vector<double> redVal = red.getOutputValues();

	  BGR.push_back(origImage.get2Dmat(filename,blueVal));
	  BGR.push_back(origImage.get2Dmat(filename, greenVal));
	  BGR.push_back(origImage.get2Dmat(filename, redVal));
	  
	  /*cv::Mat twoDblue(origImage.rowSize, origImage.colSize, CV_64F);
	  cv::Mat twoDgreen(origImage.rowSize, origImage.colSize, CV_64F);
	  cv::Mat twoDred(origImage.rowSize, origImage.colSize, CV_64F);
	  
	 
	  int counter = 0;
	  for (int i = 0; i < origImage.rowSize; i++)
	  {
		  for (int j = 0; j < origImage.colSize; j++)
		  {
			  twoDblue.at<double>(i, j) = blueVal[counter];
			  twoDgreen.at<double>(i, j) = redVal[counter];
			  twoDred.at<double>(i, j) = greenVal[counter];
			  counter++;
		  }
		  
	  }*/
	  

	  merge(BGR, finImage);
	  imshow("new", finImage);

	  
	  waitKey(0);
	  return 0;
}

/* Showing Green 
//load double to Mat
Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
cout << "C = " << endl << " " << C << endl << endl;

vector<Mat> rgbChannels(3);
split(src, rgbChannels);

Mat g, fin_img;
g = Mat::zeros(Size(src.cols, src.rows), CV_8UC1);

{
vector<Mat> channels;
channels.push_back(g);
channels.push_back(rgbChannels[1]);
channels.push_back(g);
merge(channels, fin_img);
namedWindow("G", 1); imshow("G", fin_img);
}*/

/*

std::vector<double> row1;
row1.push_back(1.0); row1.push_back(2.0); row1.push_back(3.0);

std::vector<double> row2;
row2.push_back(4.0); row2.push_back(5.0); row2.push_back(6.0);

std::vector<std::vector<double> > vector_of_rows;
vector_of_rows.push_back(row1);
vector_of_rows.push_back(row2);

// make sure the size of of row1 and row2 are the same, else you'll have serious problems!
cv::Mat my_mat(vector_of_rows.size(), row1.size(), CV_64F);
int counter = 0; 
for (int i = 0; i < origImage.rowSize; i++)
{
for (int j = 0; j < origImage.colSize; j++)
{
my_mat.at<double>(i,j) = vector_of_rows[i][j];
}
}

std::cout << my_mat << std::endl;

/*int j = 0;
for (int i = 0; i <blueVal.size(); i++)
{
if ((i%origImage.colSize == 0) && (i != 0))
{
j++;
}
twoDblue.at<double>(j, i-origImage.colSize*j) = blueVal[i];
twoDgreen.at<double>(j, i - origImage.colSize*j) = redVal[i];
twoDred.at<double>(j, i - origImage.colSize*j) = greenVal[i];
}*/


