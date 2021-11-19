#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){	

	ifstream ifs(argv[1]);
	ofstream ofs(argv[2]);
	
	char x;
	
	while(ifs.get(x)) {  
		ofs << x << endl;
	}
	ofs.close();
	
	return 0;
}
