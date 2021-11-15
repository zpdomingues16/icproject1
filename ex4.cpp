#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat img = imread(argv[1]);
	
	if (img.empty()) 
  {
    cout << "Error : Image cannot be loaded..!!" << endl;
    return -1;
  }
  
	Mat img2 = Mat::zeros(Size(img.rows, img.cols), CV_8UC3);

	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			img2.at<Vec3b>(r,c) = img.at<Vec3b>(r,c);
		}
	}
	imwrite(argv[2], img2);
	return 0;
}
