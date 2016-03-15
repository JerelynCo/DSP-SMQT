#include "Image.h"
#include "adspImage.h"

using namespace std;

#define rgtFile filename.substr(filename.length() - 4) 

int main() {
	  int L = 0;
	  string filename = "toptal.png";
	  string newFile = "new";
	  string save = "no";
	  vector<adspImage> colorChan;
	  vector<Mat> BGR;
	  //check for valid filename done inside image.cpp
	  	  
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
	  //imwrite("new.png", finImage);
	  
	  waitKey(0);
	  destroyAllWindows();

	  cout << "new file name:";
	  cin.get();
	  getline(cin, newFile);

	  if (newFile.substr(newFile.length() - 4)!=".png")
	  {
		  newFile = newFile+".png";
	  }

	  imwrite(newFile, finImage);
	  
	  return 0;
}

/*do
{
cout << "Please input correct filename:";
getline(cin, filename);
while (filename.length()<4)
{
cout << "Please input correct filename:";
getline(cin, filename);
}
} while ((rgtFile != ".png"&& rgtFile !=".jpg"));*/
//cout << "Please input correct filename:";
//getline(cin, filename);
/*cout << "new file name:";
cin.get();
getline(cin, newFile);
imwrite(newFile+".png", finImage);*/