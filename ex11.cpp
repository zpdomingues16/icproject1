#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <string>

vector<double> signalToNoise(Mat image1, Mat image2){
    vector<double> sums;
    vector<double> psnr;
    for (size_t channel = 0; channel < 3; channel++){
        double sum = 0;
        sums.push_back(sum);
        for (int r = 0; r < image1.rows; r++){
            for (int c = 0; c < image2.cols; c++){
                sums[channel] = sums[channel] + pow(image1.at<Vec3b>(r,c)[channel] - image2.at<Vec3b>(r,c)[channel],2);
                
            }
        }
        double snr = 10*log10(pow(256,2)*image1.rows*image1.cols/sums[channel]);
        psnr.push_back(snr);
    }
    return psnr;
}