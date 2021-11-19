#include <iostream>
#include <fstream>


using namespace std;

/// Copia um ficheiro de texto para outro, caracter a caracter.
int main(int argc, char *argv[]){

	if (argc==1)	{													// indicação da sintaxe de commando
		cout << "Usage: ./program_name ./original_text_file_name.txt ./name_of_copy_file.txt" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)
	}
	else {

	ifstream ifs(argv[1]); ///Argumento para o nome do ficheiro original.
	ofstream ofs(argv[2]); ///Argumento para o nome do ficheiro copia.

	char x;

	while(ifs.get(x)) {     ///Passa os caracteres para a variavel "x" um a um.
		ofs << x << endl;   ///Insere os caracteres no stream de saida/ficheiro.
	}
	ofs.close();            ///Fecha o ficheiro.
	}
	return 0;
}
