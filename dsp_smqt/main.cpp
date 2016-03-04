#include <iostream>
#include "Image.h"
#include "adspImage.h"

using namespace std;

int main() {
	  //vector<Mat> RGB(3);
	  string blueFn, greenFn, redFn;
	  blueFn = "blue.csv";
	  //greenFn = "green.csv";
	  //redFn = "red.csv";

	  Image origImage("toptal.png");
	  origImage.outputFilePixelValues(blueFn); // Output file for blue vector

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
	  //imwrite(/**filename**/,); to output an image
	  /*
		put 3 channels
		cv::Mat m = cv::Mat::ones(4, 3, CV_64F);    // 3 cols, 4 rows
		cv::Mat row = cv::Mat::ones(1, 3, CV_64F);  // 3 cols
		m.push_back(row);         
	  */
	  
	  /*cv::Mat RGB = cv::Mat::ones(3, origImage.colSize, CV_8UC1);    // dimension of matirx based on image dimension
	  cv::Mat red = cv::Mat::ones(1, origImage.colSize, CV_64F);  // 

	  RGB.push_back(red.getOutputValues());
	  RGB.push_back(green.getOutputValues());
	  RGB.push_back(blue.getOutputValues());*/
	  vector<Mat> BGR;
	  Mat finImage(origImage.rowSize, origImage.colSize, CV_64FC1);
	  	  
	  vector<double> blueVal = blue.getOutputValues();
	  vector<double> greenVal = green.getOutputValues();
	  vector<double> redVal = red.getOutputValues();
	  
	  cv::Mat twoDblue(origImage.rowSize, origImage.colSize, CV_64F);
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
		  
	  }
	  BGR.push_back(twoDblue);
	  BGR.push_back(twoDgreen);
	  BGR.push_back(twoDred);

	  merge(BGR, finImage);
	  imshow("new", finImage);

	  /*
	  Mat C;
	  for (int i = 0; i < 198442; i++){
		  C = (Mat_<double>(1,origImage.rowSize*origImage.colSize) << blueVal.at(i));
	  }
	  
	  cout << "C = " << endl << " " << C << endl << endl;*/


	  imshow("Orig", origImage.getImage());
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

*/
