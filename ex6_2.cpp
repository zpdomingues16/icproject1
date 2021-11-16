#include <map>
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include "AudioFile/AudioFile.h"

using namespace std;

double check_key(map<double, long int> m, double key)				// função para verificar se uma certa key pertence a um map (map é o equivalente a dicionário em python)
{
    // Key is not present
    if (m.find(key) == m.end())
        return '0';
	else
    return '1';
}

int main(int argc, char* argv[]){

  AudioFile<double> audioFile;
  AudioFile<double> audioFileOut;

  audioFile.load("sample02.wav");   //mudar para argv[1]

      if (argc==1)	{													// indicação da sintaxe de commando
		cout << "Usage: ./program_name ./original_audio_file_name.wav" << endl;
	}
	else {


	if (!ifs.is_open()) {								                    // avisa se o ficheiro de texto não for encontrado ("/a" faz emitir um beep)
		cout << "\a" << "failed to open file \"" << argv[1] << "\"" << endl;
	}
	else {

 // audioFileOut.setNumChannels(audioFile.getNumChannels());
 // audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());

  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();
  int bitDepth = audioFile.getBitDepth();


    cout << "channels = "<< channels << endl;
    cout << "numSamples/cnannel = "<< numSamples << endl;
    cout << "bitDepth = " << bitDepth << endl;


 ofstream ofs("channel1.txt");


    map<double,long int> samp;

        double x;

        for (int c = 0; c < 1; c++){
            for (long int i = 0; i < 10000; i++){

            double x = (audioFile.samples[c][i])*32767;

            if (check_key(samp,x) == '1') {		// substitui os caracteres (letras) que não estão em lowercase por lowercase
			samp[x]++;
            }
            else {
            samp.insert ( {x,1} );

//          cout << "sample = " << x << endl;
            }

    }

      // audioFileOut.samples[c][i] = audioFile.samples[c][i];


     for (auto const &pair: samp) {
        ofs << pair.first << " " << pair.second << endl;
    }

      // audioFileOut.samples[c][i] = audioFile.samples[c][i];


 //// audioFile.save (argv[2], AudioFileFormat::Wave);

  return 0;
}}
