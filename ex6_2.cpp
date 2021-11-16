#include <map>
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include "AudioFile/AudioFile.h"
#include <math.h>  


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

  audioFile.load(argv[1]);  

      if (argc==1)	{													// indicação da sintaxe de commando
	cout << "Usage: ./program_name ./original_audio_file_name.wav" << endl;
	}
	else {


	//if (!audioFile.is_open()) {								                    // avisa se o ficheiro de texto não for encontrado ("/a" faz emitir um beep)
	//	cout << "\a" << "failed to open file \"" << argv[1] << "\"" << endl;
	//}

 // audioFileOut.setNumChannels(audioFile.getNumChannels());
 // audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());

  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();
  int bitDepth = audioFile.getBitDepth();


    cout << "channels = "<< channels << endl;
    cout << "numSamples/cnannel = "<< numSamples << endl;
    cout << "bitDepth = " << bitDepth << endl;


ofstream ofs1("channel1.txt");
ofstream ofs2("channel2.txt");
ofstream ofs3("mono.txt");


    map<double,long int> samp1;
    map<double,long int> samp2;
    map<double,long int> samp3;


        double x;

        for (int c = 0; c < channels; c++){
            for (long int i = 0; i < numSamples; i++){

            double x = round((audioFile.samples[c][i])*32767);
			if (c==0) {
				if (check_key(samp1,x) == '1') {		
				samp1[x]++;
				}
				else {
				samp1.insert ( {x,1} );
				}}
			else if (c==1) {
				if (check_key(samp2,x) == '1') {		
				samp2[x]++;
				}
				else {
				samp2.insert ( {x,1} );
				}}
				
//          cout << "sample = " << x << endl;
            }}
         for (auto const &pair: samp1) {
			samp3.insert( {pair.first, pair.second});
    }
    for (auto const &pair: samp2) {
			if (check_key(samp2,pair.first) == '1') {
				samp3[pair.first] = samp3[pair.first] + samp2[pair.first];
			}
			else {
				samp3.insert( {pair.first, pair.second});
}}
	for (auto const &pair: samp3) {
			samp3[pair.first]=samp3[pair.first]/2;
      // audioFileOut.samples[c][i] = audioFile.samples[c][i];
}
		

    for (auto const &pair: samp1) {
        ofs1 << pair.first << " " << pair.second << endl;
    }
	for (auto const &pair: samp2) {
        ofs2 << pair.first << " " << pair.second << endl;
    }
    for (auto const &pair: samp3) {
        ofs3 << pair.first << " " << pair.second << endl;
    }

      // audioFileOut.samples[c][i] = audioFile.samples[c][i];


 //// audioFile.save (argv[2], AudioFileFormat::Wave);

  return 0;
}
