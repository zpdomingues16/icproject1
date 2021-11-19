#include <map>
#include <stdint.h>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include "AudioFile/AudioFile.h"
#include <math.h>
#include <sstream>


using namespace std;

int check_key(map<int, long int> m, int key)	// função para verificar se uma certa key pertence a um map (map é o equivalente a dicionário em python)
{
    // Key is not present
    if (m.find(key) == m.end())
        return '0';
	else
    return '1';
}

int main(int argc, char* argv[]){


  AudioFile<double> audioFile;

  if (argc==1)	{													// indicação da sintaxe de commando
		cout << "Usage: ./program_name ./original_audio_file_name.wav" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)
	}
	else {


  audioFile.load(argv[1]);


  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();
  int bitDepth = audioFile.getBitDepth();

//Devolve para a linha de comando/terminal caracteristicas de audio do ficheiro de input (original)
    cout << "channels = "<< channels << endl;
    cout << "numSamples/channel = "<< numSamples << endl;
    cout << "bitDepth = " << bitDepth << endl;


    map<int,long int> samp1; //Channel 1
    map<int,long int> samp2; //Channel 2
    map<int,long int> samp3; //Channel mono
    map<int, double> entrch1; //Entropia Channel 1
    map<int, double> entrch2; //Entropia Channel 2
    map<int, double> entrmono; //Entropia mono


        int x; //Sample 1 e 2
        int a; //Sample channels to mono
        int b; //Sample channels to mono
        int z; //Sample channels to mono
        float scsamp; //Scale audio output from -1/+1 to bitDepth


   scsamp = (pow(2, bitDepth-1)) - 1; //Cálculo da escala de conversão em função do bitsample/bitdepth.


 //Populate the samp1 and the samp2 map (existing values are counted):

        for (int c = 0; c < channels; c++){
            for (long int i = 0; i < numSamples; i++){

            int x = round((audioFile.samples[c][i])*scsamp); //Como a libraria AudioFile.h devolve os samples num range de -1 a +1, multiplicamos
                                                            //(no caso do sample02.wav) por 2^15-1, uma vez que o bitsample/bitdepth é 16 bits.

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

// Sample channels to mono (average of the channels, sample by sample):
        for (long int i = 0; i < numSamples; i++){
            for (int c = 0; c < channels; c++){

            if (c==0) {
			  a = round((audioFile.samples[c][i])*scsamp);
            }
			if (c==1) {
			  b = round((audioFile.samples[c][i])*scsamp);
            }}

              z = (a + b)/2;

            if (check_key(samp3,z) == '1') {
				samp3[z]++;
				}
				else {
				samp3.insert ( {z,1} );
				}
				}

///// Calculate the entropy:

//Channel 1:
    for (auto const &pair: samp1) {
			entrch1.insert({pair.first, pair.second});
    }


    for (auto const &pair: entrch1) {
			entrch1[pair.first] = entrch1[pair.first] / numSamples; //probabilidade de cada sample.
   }

   for (auto const &pair: entrch1) {
		entrch1[pair.first] = entrch1[pair.first] * (log2 (1 / entrch1[pair.first])); //P(n)*log2(1/P(n))
  }

double entropiach1 = 0;

   for (auto const &pair: entrch1) {
		entropiach1 = entropiach1 + entrch1[pair.first];
         }

    cout << "Entropia channel1 = " << entropiach1 << "bps" << endl;

//Channel 2:
for (auto const &pair: samp2) {
			entrch2.insert({pair.first, pair.second});
    }

    for (auto const &pair: entrch2) {
			entrch2[pair.first] = entrch2[pair.first] / numSamples; //probabilidade de cada sample (não está a calcular bem)
   }

   for (auto const &pair: entrch2) {
		entrch2[pair.first] = entrch2[pair.first] * (log2 (1 / entrch2[pair.first])); //P(n)*log2(1/P(n))
  }

double entropiach2 = 0;

   for (auto const &pair: entrch2) {
		entropiach2 = entropiach2 + entrch2[pair.first];
         }

    cout << "Entropia channel2 = " << entropiach2 << "bps" << endl;

//Mono (average of the channels):
for (auto const &pair: samp3) {
			entrmono.insert({pair.first, pair.second});
    }

    for (auto const &pair: entrmono) {
			entrmono[pair.first] = entrmono[pair.first] / numSamples; //probabilidade de cada sample (não está a calcular bem)
   }

   for (auto const &pair: entrmono) {
		entrmono[pair.first] = entrmono[pair.first] * (log2 (1 / entrmono[pair.first])); //P(n)*log2(1/P(n))
  }

double entropiamono = 0;

   for (auto const &pair: entrmono) {
		entropiamono = entropiamono + entrmono[pair.first];
         }

    cout << "Entropia mono = " << entropiamono << "bps" << endl;

//Nome dos ficheiros de output para os histogramas.


    stringstream arg;
    arg.str (argv[1]);
    string channel1 = arg.str() + "_channel1.txt";
    string channel2 = arg.str() + "_channel2.txt";
    string mono = arg.str() + "_mono.txt";


    ofstream ofs1(channel1);
    ofstream ofs2(channel2);
    ofstream ofs3(mono);


////Populate the corresponding output files:

    for (auto const &pair: samp1) {
        ofs1 << pair.first << "\t" << pair.second << endl;
    }
	for (auto const &pair: samp2) {
        ofs2 << pair.first << "\t" << pair.second << endl;
    }
    for (auto const &pair: samp3) {
        ofs3 << pair.first << "\t" << pair.second << endl;
    }


/////Pode ser usado para criar um ficheiro .txt com os valores para a entropia: ////////
//
//   ofstream ofs4("entopych1.txt");
//
//   for (auto const &pair: entrch1) {
//       ofs4 << "P("<< pair.first << ")=\t" << pair.second << endl;
//   }
////////////////////////////////////////////////////////////////////////////////////////

	}
  return 0;
}
