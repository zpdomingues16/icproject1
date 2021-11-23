#include <map>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

char check_key(map<char, int> m, char key)				// função para verificar se uma certa key pertence a um map (map é o equivalente a dicionário em python)
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
	ofstream ofs("character_ocurrences.txt");

    if (argc==1)	{													// indicação da sintaxe de commando
		cout << "Usage: ./program_name ./file_name.txt" << endl;
	}
	else {


	if (!ifs.is_open()) {								                    // avisa se o ficheiro de texto não for encontrado e toca um som/alarme.
		cout << "failed to open file \"" << argv[1] << "\"" << "\a" << endl;
	}
	else {

	map<char, int> chars;								// criação do map com o nome "chars"
	char x;
	while(ifs.get(x)){  								// extrai os caracteres do ifs
		if (check_key(chars,tolower(x)) == '1') {		// substitui os caracteres (letras) que não estão em lowercase por lowercase
			chars[tolower(x)]++;
		}
		else {											// quando estão todas as letras em lowercase...
			if (isalpha(x)) {							// verifica se o character é uma letra
			chars.insert ( {tolower(x),1} );};			// e se for letra faz o insert da mesma no map com valor inicial 1
		}
	}

	for (auto const &pair: chars) {
        ofs << pair.first << " " << pair.second << endl;	// faz "output" do map no ficheiro "character_ocurrences.txt"
    }
	}}
	return 0;
}

