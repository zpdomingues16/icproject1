#include <iostream>
#include <fstream>
#include "AudioFile/AudioFile.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <sstream>


using namespace std;

int main(int argc, char* argv[]){

string help=argv[1];

  AudioFile<double> audioFile;
  AudioFile<double> audioFileOut;

    int channels = audioFile.getNumChannels();
    int numSamples = audioFile.getNumSamplesPerChannel();
    int bitDepth = audioFile.getBitDepth();


    if (argc<=2 || help=="/?")	{	// indicação da sintaxe de commando
		cout << "Usage: ./program_name ./original_audio_file_name.wav ./bitreduced_audio_file_name.wav [-b final desired bit number] \n\n options:\n\t -b\t Final desired bit number.\n\t\t 50% if not specified, 8bit minimun.\n" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)

	}

    if (argc==4){
        string option=argv[3];
        if (option=="-b")	{	     // indicação da sintaxe de commando
		cout << "The final desired bit number after the argument \"-b\", is missing\n\n options:\n\t -b\t Final desired bit number.\n\t\t 50% if not specified, 8bit minimun.\n" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)

		}}

else {

    if (argc!=5){


  int nbits = pow(2,(bitDepth/2)-1);

  audioFile.load(argv[1]);

//Devolve para a linha de comando/terminal as caracteristicas de audio do ficheiro de input (original)

   cout << "Original file characteristics:\n channels = "<< channels << "\n numSamples/channel = "<< numSamples << "\n bitDepth = " << bitDepth << endl;

  audioFileOut.setNumChannels(audioFile.getNumChannels());
  audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());

  float scsamp; //Scale audio output from -1/+1 to bitDepth

  scsamp = (pow(2, bitDepth-1)) - 1; //Cálculo da escala de conversão em função do bitsample/bitdepth.

  for (int c = 0; c < channels; c++){
    for (int i = 0; i < numSamples; i++){
        audioFileOut.samples[c][i] = trunc(((audioFile.samples[c][i])*scsamp)/nbits);
    }
    };

    }

    if (argc==5){
    int arg4;
    stringstream ss;
    ss << argv[4];
    ss >> arg4;


 //   if (!(ss >> arg4)) {
 //   cerr << "Invalid number: " << argv[4] << '\n';
 //       } else if (!ss.eof()) {
 //       cerr << "Trailing characters after number: " << argv[1] << '\n';
 //       }

	if (arg4>=bitDepth){
        cout << "The final desired bit number has to be less than " << bitDepth << endl;
	}


  audioFile.load(argv[1]);

//Devolve para a linha de comando/terminal as caracteristicas de audio do ficheiro de input (original)

   cout << "Original file characteristics:\n channels = "<< channels << "\n numSamples/channel = "<< numSamples << "\n bitDepth = " << bitDepth << endl;

  audioFileOut.setNumChannels(audioFile.getNumChannels());
  audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());

   int nbits = bitDepth-arg4;

  float scsamp; //Scale audio output from -1/+1 to bitDepth

  scsamp = (pow(2, bitDepth-1)) - 1; //Cálculo da escala de conversão em função do bitsample/bitdepth.
    int halfbit = bitDepth/2;

    int argx=arg4;

  for (int c = 0; c < channels; c++){
    for (int i = 0; i < numSamples; i++){

      if (argx > halfbit){

      audioFileOut.samples[c][i] = trunc(trunc(((audioFile.samples[c][i])*scsamp)/nbits)*nbits);
    }

    else {audioFileOut.samples[c][i] = trunc(((audioFile.samples[c][i])*scsamp)/nbits);

    }

    };
    }
    }


  audioFile.save (argv[2], AudioFileFormat::Wave);

  //audioFile.load(argv[3]);
 // int bitDepth2 = audioFile.getBitDepth();
 // cout << "Final file characteristics:\n channels = "<< channels << "\n numSamples/channel = "<< numSamples << "\n bitDepth = " << bitDepth2 << endl;

	}

  return 0;
}
