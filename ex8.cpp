#include <iostream>
#include "AudioFile/AudioFile.h"
#include <math.h>  

int main(int argc, char* argv[]){
  
  AudioFile<double> audioFile;
  AudioFile<double> audioFileOut;
  
  audioFile.load(argv[1]);
  
  audioFileOut.setNumChannels(audioFile.getNumChannels());
  audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());
  
  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();

  for (int c = 0; c < channels; c++){
    for (int i = 0; i < numSamples; i++)
    {
      audioFileOut.samples[c][i] = ((trunc((audioFile.samples[c][i])*32767000))/2)*2;
    };
  }

  audioFile.save (argv[2], AudioFileFormat::Wave);
  
  return 0;
}
