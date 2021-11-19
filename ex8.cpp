#include <iostream>
#include <fstream>
#include "AudioFile/AudioFile.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>


using namespace std;

int main(int argc, char* argv[]){


  AudioFile<double> audioFile;
  AudioFile<double> audioFileOut;

     if (argc==1)	{													// indica��o da sintaxe de commando
		cout << "Usage: ./program_name ./original_audio_file_name.wav ./bitreduced_audio_file_name.wav" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)
	}
	else {

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
	}

  return 0;
}
