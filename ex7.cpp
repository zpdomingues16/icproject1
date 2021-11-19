#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

double check_key(map<int, int> m, int key)				// função para verificar se uma certa key pertence a um map (map é o equivalente a dicionário em python)
{
    // Key is not present
    if (m.find(key) == m.end())
        return '0';
	else
    return '1';
}

int main(int argc, char* argv[])
{	
	ifstream ifs(argv[1]);
	ofstream ofs1("b.txt");
	ofstream ofs2("g.txt");
	ofstream ofs3("r.txt");
	ofstream ofs4("bw.txt");

	map<int,int> r;
	map<int,int> g;
	map<int,int> b;
	map<int,int> gr;

	Mat img = imread(argv[1]);
	
	if (img.empty()) 
  {
    cout << "Error : Image cannot be loaded..!!" << endl;
    return -1;
  }
  
	Mat img2; 
	cvtColor(img,img2,CV_RGB2GRAY);
	
	for (int r1 = 0; r1 < img.rows; r1++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			Vec3b x = img.at<Vec3b>(r1,c);
			
			if (check_key(r,x[0]) == '1') {		
				r[x[0]]++;
				}
			else {
				r.insert ( {x[0],1} );
				}
			if (check_key(g,x[1]) == '1') {		
				g[x[1]]++;
				}
			else {
				g.insert ( {x[1],1} );
				}
			if (check_key(b,x[2]) == '1') {		
				b[x[2]]++;
				}
			else {
				b.insert ( {x[2],1} );
				}}
		}

	for (int r1 = 0; r1 < img2.rows; r1++)
	{
		for (int c = 0; c < img2.cols; c++)
		{
			int xbw = img2.at<int>(r1,c);
			
			if (check_key(gr,xbw) == '1') {		
				gr[xbw]++;
				}
			else {
				gr.insert ( {xbw,1} );
				}}
		}
	for (auto const &pair: r){
		ofs1 << pair.first << " " << pair.second <<endl;
	}
	for (auto const &pair: g){
		ofs2 << pair.first << " " << pair.second <<endl;
	}
	for (auto const &pair: b){
		ofs3 << pair.first << " " << pair.second <<endl;
	}
	for (auto const &pair: gr){
		ofs4 << pair.first << " " << pair.second <<endl;
	}
	return 0;}

