#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{	

	ifstream ifs(argV[1]);
	ofstream ofs("pixel.txt");

	double check_key(map<double, long int> m, double key)				// função para verificar se uma certa key pertence a um map (map é o equivalente a dicionário em python)
{
    // Key is not present
    if (m.find(key) == m.end())
        return '0';
	else
    return '1';
}

	map<double,double> pixel;

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
			double x = img<Vec3b>(r,c)
			if (check_key(pixel,x) == '1') {		
				pixel[x]++;
				}
				else {
				pixel.insert ( {x,1} );
				}}
		}
	}

	for (auto const &pair: pixel){
		ofs << pair.first << " " << pair.second <<endl;
	}
	return 0;
}
