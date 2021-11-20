#include <iostream>
using namespace std;
#include "AudioFile/AudioFile.h"



vector<double> signalToNoise(AudioFile<double> audio1, AudioFile<double> audio2){
    vector<double> sums;
    vector<double> psnr;
    for (int c = 0; c < audio1.getNumChannels(); c++){
        double sum = 0;
        sums.push_back(sum);
        for (int s = 0; s < audio1.getNumSamplesPerChannel(); s++){
                sums[c] = sums[c] + pow((audio1.samples[c][s] - audio2.samples[c][s])*exp2(15),2);
        }
        double snr = 10*log10(pow(exp(16),2)*audio1.getNumSamplesPerChannel()/sums[c]);
        psnr.push_back(snr);
    }
    return psnr;
}