#include <map>
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include "AudioFile/AudioFile.h"
#include <math.h>


using namespace std;

int check_key(map<int, long int> m, int key)				// função para verificar se uma certa key pertence a um map (map é o equivalente a dicionário em python)
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


  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();
  int bitDepth = audioFile.getBitDepth();


    cout << "channels = "<< channels << endl;
    cout << "numSamples/cnannel = "<< numSamples << endl;
    cout << "bitDepth = " << bitDepth << endl;



ofstream ofs1("channel1.txt");
ofstream ofs2("channel2.txt");
ofstream ofs3("mono.txt");
ofstream ofs4("entopych1.txt");



    map<int,long int> samp1;
    map<int,long int> samp2;
    map<int,long int> samp3;
    map<int, double> samp4;


        int x;
        int a;
        int b;
        int z;

 //Populate the samp1 and the samp2 map (existing values are counted):

        for (int c = 0; c < channels; c++){
            for (long int i = 0; i < 10000; i++){

            int x = round((audioFile.samples[c][i])*32767);

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


            }}

// Sample channels to mono:

        for (long int i = 0; i < 10000; i++){
            for (int c = 0; c < channels; c++){

            if (c==0) {
			  a = round((audioFile.samples[c][i])*32767);
            }
			if (c==1) {
			  b = round((audioFile.samples[c][i])*32767);
            }}

              z = (a + b)/2;

            if (check_key(samp3,z) == '1') {
				samp3[z]++;
				}
				else {
				samp3.insert ( {z,1} );
				}
				}

//Populate the corresponding output files:

    for (auto const &pair: samp1) {
        ofs1 << pair.first << "\t" << pair.second << endl;
    }
	for (auto const &pair: samp2) {
        ofs2 << pair.first << "\t" << pair.second << endl;
    }
    for (auto const &pair: samp3) {
        ofs3 << pair.first << "\t" << pair.second << endl;
    }

// Calculate the entropy:



    for (auto const &pair: samp1) {
			samp4.insert({pair.first, pair.second});
    }


    for (auto const &pair: samp4) {
			samp4[pair.first] = samp4[pair.first] / 10000; //probabilidade de cada sample (não está a calcular bem)
   }

   for (auto const &pair: samp4) {
		samp4[pair.first] = log2 (1 / samp4[pair.first]) * samp4[pair.first]; //P(n)*log2(1/P(n))
  }

///////////////////Por acabar////////////////////////////////////////

  // para finalizar falta somar todos os valores de pair.first: H()=somatorio P(n)*log2(1/P(n))

//.
//.
//.
//.
//////////////////////////////////////////////////////////////
	
for (auto const &pair: samp4) {
        ofs4 << "P("<< pair.first << ")=\t" << pair.second << endl;
    }


  return 0;
}

