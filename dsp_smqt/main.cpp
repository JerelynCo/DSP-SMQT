#include "Image.h"
#include "adspImage.h"

using namespace std;

#define rgtFile filename.substr(filename.length() - 4) 

int main() {
	  int L = 0;
	  string filename = "";
	  string newFile = "new";
	  string save = "no";
	  int loop = 0;
	  vector<adspImage> colorChan;
	  vector<Mat> BGR;
	  //check for valid filename done inside image.cpp
	  do
	  {
		 
		  cout << "enter filename:";
		  getline(cin, filename);
		  Image origImage(filename);
		  
		  Mat finImage(origImage.rowSize, origImage.colSize, CV_8UC1);
		  cout << "Please enter the L:";
		  cin >> L;
		  while (cin.fail())
		  {
			  cin.clear();
			  cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			  cout << "Please enter a number for L: ";
			  cin >> L;
		  }

		  cout << "Create adspImage Object.." << endl;

		  adspImage blue(origImage.getBlueVector());
		  adspImage green(origImage.getGreenVector());
		  adspImage red(origImage.getRedVector());
		  cout << "Calculate SMQT.." << endl;

		  colorChan.push_back(blue);
		  colorChan.push_back(green);
		  colorChan.push_back(red);
	
		  for (int i = 0; i < colorChan.size(); i++)
		  {
			  vector<unsigned int> colorChanPixelPositions(colorChan[i].getPixelValues().size());
			  iota(begin(colorChanPixelPositions), end(colorChanPixelPositions), 0);
			  colorChan[i].calculateSMQT(colorChanPixelPositions, L);
			  vector<double> colorChanVal = colorChan[i].getOutputValues(L);
			  BGR.push_back(origImage.get2Dmat(filename, colorChanVal));
		  }

		  imshow("Orig", origImage.getImage());
		  merge(BGR, finImage);
		  imshow("new", finImage);
		  waitKey(0);
		  destroyAllWindows();
		  do
		  {
			  cout << "new file name with a .png file extension and longer than 4 charcters:";
			  cin.get();
			  getline(cin, newFile);
		  } while (newFile.length() < 4);
		  //to make sure the program does not have an error when no file extension is entered
		  if (newFile.substr(newFile.length() - 4) != ".png")
		  {
			  newFile = newFile + ".png";
		  }

		  imwrite(newFile, finImage);
		  colorChan.clear();
		  BGR.clear();
		  origImage.~origImage();

		  cout << "save another file?enter 1:";
		  cin >> loop;
	  } while (loop == 1);
	  return 0;
}

