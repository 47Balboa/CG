#include "../../src/headers/Struct.h"
#include <iostream>
#include <fstream>


using namespace std;

// Respons�vel por guardar os pontos gerados num documento.
void saveFile(Struct *p, string nomeF) {
	fstream(file);
	file.open("../../../3dFiles/" + nomeF, fstream::out);
	
	if (file.is_open()) { // verifica se foi aberto
		vector<Point*> v = p->getLP();

		file << to_string(v.size()) << endl;

		for (vector<Point*>::iterator it = v.begin(); it != v.end(); ++it) { //percorre a lista de pontos toda, escrevendo cada ponto no ficheiro
			file << (*it)->to_String() << endl; 
		}

		file.close(); // fecha o ficheiro
	}
	else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }
}

void help() {
	cout << "*---------------------------HELP---------------------------*" << endl;
	cout << "|                                                          |" << endl;
	cout << "|            Modo de utlizacao:                            |" << endl;
	cout << "| $ generator.exe figura [dimensoes] ficheiro(.3d)         |" << endl;
	cout << "|                                                          |" << endl;
	cout << "|         Figuras:                                         |" << endl;
	cout << "|               -plane :                                   |" << endl;
	cout << "|                     Dimensoes:                           |" << endl;
	cout << "|                            -tamanho.                     |" << endl;
	cout << "|               -box :                                     |" << endl;
	cout << "|                     Dimensoes :                          |" << endl;
	cout << "|                            -X Y Z divisoes(opcional).    |" << endl;
	cout << "|               -sphere :                                  |" << endl;
	cout << "|                     Dimensoes:                           |" << endl;
	cout << "|                            -Raio Fatias Pilhas           |" << endl;
	cout << "|               -cone :                                    |" << endl;
	cout << "|                     Dimensoes:                           |" << endl;
	cout << "|                            - Raio Altura Fatias Pilhas.  |" << endl;
	cout << "|               -cylinder :                                |" << endl;
	cout << "|                     Dimensoes:                           |" << endl;
	cout << "|                            -Raio Altura Fatias.          |" << endl;
	cout << "|                                                          |" << endl;
	cout << "|         Exemplo de utilizacao:                           |" << endl;
	cout << "|           $ generator.exe sphere 1 10 10 sphere.3d       |" << endl;
	cout << "|                                                          |" << endl;
	cout << "*---------------------------HELP---------------------------*" << endl;
} 


int main(int argc, char* argv[]) {

	if (argc >= 2) { 

		//comando help
		if (strcmp(argv[1], "-h") == 0){
			help();
		}

		Struct* p = new Struct();
		string nomeF;

		//gera pontos do plano
		if (strcmp(argv[1], "plane") == 0 && argc == 4) {
			float dim = stof(argv[2]);
			nomeF = argv[3];
			p->genPlane(dim);
			saveFile(p, nomeF);
		}

		if(strcmp(argv[1], "cylinder") == 0 && argc == 6) {
			float radius = stof(argv[2]);
			float height = stof(argv[3]);
			int slices = (int)atoi(argv[4]);
			nomeF = argv[5];
			p->genCylinder(radius, height, slices);
			saveFile(p, nomeF);
		}

		if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
			float radius = stof(argv[2]);
			int slices = atoi(argv[3]);
			int stack = atoi(argv[4]);
			nomeF = argv[5];
			p->genSphere(radius, slices, stack);
			saveFile(p, nomeF);
		}
		
		/*
		else {
			cout << "N�o tem argumentos suficientes" << endl;
			return 0;
		}
		*/
		/*
		//desenha box
		if (strcmp(argv[1], "box") == 0 && argc > 5) {
			int x = atoi(argv[2]);
			int y = atoi(argv[3]);
			int z = atoi(argv[4]);

			if (argc == 6) p.genBox(x,y,z);

			if (argc == 7) {
				int divisions = atoi(argv[5]);
				p.genBox(x,y,z,divisions);
			}
		}
		else {
			cout << "N�o tem argumentos suficientes" << endl;
			return 0;
		}

		//desenha esfera
		if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
			int radius = atoi(argv[2]);
			int slices = atoi(argv[3]);
			int stack = atoi(argv[4]);

			p.genSphere(radius, slices, stack);
		}
		else {
			cout << "N�o tem argumentos suficientes" << endl;
			return 0;
		}
		*/
		//desenha cone
		if (strcmp(argv[1], "cone") == 0 && argc == 7) {
			int radius = atoi(argv[2]);
			int height = atoi(argv[3]);
			int slices = atoi(argv[4]);
			int stack = atoi(argv[5]);

			p->genCone(radius,height,slices,stack);
			saveFile(p, nomeF);
		}
		else cout << "Nao tem argumentos suficientes ou figura nao existe" << endl;
		
	}
	
	else{
		cout << "Nao tem argumentos suficientes! Se precisar de ajuda execute 'generator.exe -h'" << endl; 
		return 0;
	}
}
