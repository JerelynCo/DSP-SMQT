#include <iostream>
#include <string>
#include "Image.h"
#include "adspImage.h"

using namespace std;

int main() {
	  int L = 0;
	  string filename = "toptal.png";
	  string newFile = "new";
	  string save = "no";
	  vector<Mat> BGR;
	  
	  cout << "Please input correct filename:";
	  getline(cin, filename);
	  Image origImage(filename);
	  Mat finImage(origImage.rowSize, origImage.colSize, CV_8UC1);
	  cout << "Please enter the L:";
	  cin >> L;
	  
	  cout << "Create adspImage Object.." << endl;
	  
	  adspImage blue(origImage.getBlueVector());
	  adspImage green(origImage.getGreenVector());
	  adspImage red(origImage.getRedVector());
	  cout << "Calculate SMQT.." << endl;

	  vector<unsigned int> redPixelPositions(red.getPixelValues().size());
	  iota(begin(redPixelPositions), end(redPixelPositions), 0);
	  vector<unsigned int> greenPixelPositions(green.getPixelValues().size());
	  iota(begin(greenPixelPositions), end(greenPixelPositions), 0);
	  vector<unsigned int> bluePixelPositions(blue.getPixelValues().size());
	  iota(begin(bluePixelPositions), end(bluePixelPositions), 0);

	  blue.calculateSMQT(bluePixelPositions, L);
	  green.calculateSMQT(greenPixelPositions, L);
	  red.calculateSMQT(redPixelPositions, L);

	  vector<double> blueVal = blue.getOutputValues(L);
	  vector<double> greenVal = green.getOutputValues(L);
	  vector<double> redVal = red.getOutputValues(L);

	  BGR.push_back(origImage.get2Dmat(filename,blueVal));
	  BGR.push_back(origImage.get2Dmat(filename, greenVal));
	  BGR.push_back(origImage.get2Dmat(filename, redVal));
	 	  
	  imshow("Orig", origImage.getImage());
	  merge(BGR, finImage);
	  imshow("new", finImage);
	  
	  /*cout << "new file name:";
	  cin.get();
	  getline(cin, newFile);
	  imwrite(newFile+".png", finImage);*/
     
	  imwrite("5.png", finImage);
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

/* cv::Mat twoDblue(origImage.rowSize, origImage.colSize, CV_8UC1);
cv::Mat twoDgreen(origImage.rowSize, origImage.colSize, CV_8UC1);
cv::Mat twoDred(origImage.rowSize, origImage.colSize, CV_8UC1);


int counter = 0;
for (int i = 0; i < origImage.rowSize; i++)
{
for (int j = 0; j < origImage.colSize; j++)
{
twoDblue.at<unsigned char>(i, j) = blueVal[counter];
twoDgreen.at<unsigned char>(i, j) = greenVal[counter];
twoDred.at<unsigned char>(i, j) = redVal[counter];
counter++;
}

}
BGR.push_back(twoDblue);
BGR.push_back(twoDgreen);
BGR.push_back(twoDred);*/
//string blueFn, greenFn, redFn;
//blueFn = "blue.csv";
//greenFn = "green.csv";
//redFn = "red.csv";

//origImage.outputFilePixelValues(blueFn); // Output file for blue vector
//origImage.showImage("Orig");

