#include "../../src/headers/Struct.h"
#include "../headers/BezierPatch.h"
#include <iostream>
#include <fstream>


using namespace std;

// Responsável por guardar os pontos gerados num documento.
void saveFile(Struct *p, string nomeF) {
	fstream(file);
	file.open("../3dFiles/" + nomeF, fstream::out);
	
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




string getLineNumber(string file_name, int n_line) {

	string line;

	ifstream file;
	file.open(file_name);

	if (file.is_open()) {
		for (int i = 0; i < n_line; i++)
			getline(file, line);
		file.close();
	}
	else cout << "Unable to open patch file: " << file_name << "." << endl;


	return line;
}

// le do ficheiro patch e cria os pontos para gerar a nova figura
void readPatch(int tessellation, string input_file, string output_file) {

	string line, token, line_cpy, n_line;
	int n_patches, n_points, position;
	int index;
	int contador = 0; // retirar
	float value;
	float vertex_coords[3];

	vector<BezierPatch*> patches_list;

	ifstream file;
	file.open(input_file);

	if (file.is_open()) {

		// Number of patches
		getline(file, line);
		n_patches = atoi(line.c_str());

		// Parsing indexes
		for (int i = 0; i < n_patches; i++) {

			getline(file, line);

			BezierPatch* patch = new BezierPatch();
			patches_list.push_back(patch);

			for (int j = 0; j < 16; j++) {

				position = line.find(",");
				token = line.substr(0, position);
				index = atoi(token.c_str());
				line.erase(0, position + 1);

				n_line = getLineNumber(input_file, n_patches + 3 + index);
				line_cpy = n_line;

				for (int j = 0; j < 3; j++) {
					position = n_line.find(",");
					token = n_line.substr(0, position);
					vertex_coords[j] = atof(token.c_str());
					n_line.erase(0, position + 1);
				}

				n_line = line_cpy;
				patch->addPonto(new Point(vertex_coords[0], vertex_coords[1], vertex_coords[2]));
			}
		}
		vector<Point*> res = renderBezierPatch(tessellation, patches_list);
		
		printFileBezier(res, output_file);

		file.close();
	}

	else cout << "Nao se conseguiu abrir o ficheiro " << input_file << "." << endl;
}



void help() {
	cout << "*---------------------------------HELP---------------------------------*" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|            Modo de utlizacao:                                        |" << endl;
	cout << "| $ generator.exe figura [dimensoes] ficheiro(.3d)                     |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|         Figuras:                                                     |" << endl;
	cout << "|               -plane :                                               |" << endl;
	cout << "|                     Dimensoes:                                       |" << endl;
	cout << "|                            -tamanho.                                 |" << endl;
	cout << "|               -box :                                                 |" << endl;
	cout << "|                     Dimensoes :                                      |" << endl;
	cout << "|                            -X Y Z divisoes(opcional).                |" << endl;
	cout << "|               -sphere :                                              |" << endl;
	cout << "|                     Dimensoes:                                       |" << endl;
	cout << "|                            -Raio Fatias Pilhas                       |" << endl;
	cout << "|               -cone :                                                |" << endl;
	cout << "|                     Dimensoes:                                       |" << endl;
	cout << "|                            - Raio Altura Fatias Pilhas.              |" << endl;
	cout << "|               -cylinder :                                            |" << endl;
	cout << "|                     Dimensoes:                                       |" << endl;
	cout << "|                            -Raio Altura Fatias.                      |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|               -torus :                                               |" << endl;
	cout << "|                     Dimensoes:                                       |" << endl;
	cout << "|                            -TamanhoCoroa RaioExterior Stacks Aneis   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|               -cintura de asteroides :                               |" << endl;
	cout << "|                     Dimensoes:                                       |" << endl;
	cout << "|                            -TamanhoCoroa RaioExterior Faces  Aneis   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|         Exemplo de utilizacao:                                       |" << endl;
	cout << "|           $ generator.exe sphere 1 10 10 sphere.3d                   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "*---------------------------------HELP---------------------------------*" << endl;
} 


int main(int argc, char* argv[]) {

	if (argc >= 2) {

		//comando help
		if (strcmp(argv[1], "-h") == 0) {
			help();
			return 0;
		}

		Struct* p = new Struct();
		string nomeF;

		//gera pontos do plano
		if (strcmp(argv[1], "plane") == 0 && argc == 4) {
			float dim = stof(argv[2]);
			nomeF = argv[3];
			p->genPlane(dim);
			saveFile(p, nomeF);
			return 0;
		}

		if (strcmp(argv[1], "cylinder") == 0 && argc == 6) {
			float radius = stof(argv[2]);
			float height = stof(argv[3]);
			int slices = (int)atoi(argv[4]);
			nomeF = argv[5];
			p->genCylinder(radius, height, slices);
			saveFile(p, nomeF);
			return 0;
		}

		if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
			float radius = stof(argv[2]);
			int slices = atoi(argv[3]);
			int stack = atoi(argv[4]);
			nomeF = argv[5];
			p->genSphere(radius, slices, stack);
			saveFile(p, nomeF);
			return 0;
		}


		//desenha box
		if (strcmp(argv[1], "box") == 0 && argc > 5) {
			float x = stof(argv[2]);
			float y = stof(argv[3]);
			float z = stof(argv[4]);

			if (argc == 6) { p->genBox(x, y, z, 1); nomeF = argv[5]; }

			if (argc == 7) {
				int divisions = atoi(argv[5]);
				p->genBox(x, y, z, divisions);
				nomeF = argv[6];
			}
			saveFile(p, nomeF);

			return 0;
		}

		if (strcmp(argv[1], "torus") == 0 && argc == 7) {

			float raioIn = stof(argv[2]);
			float raioEx = stof(argv[3]);
			int sides = atoi(argv[4]);
			int rings = atoi(argv[5]);

			p->genTorus(raioIn, raioEx, sides, rings);

			nomeF = argv[6];

			saveFile(p, nomeF);

			return 0;
		}

		//le o ficheiro de patch e produz a figura
		if (strcmp(argv[1], "bezierPatch") == 0 && argc == 5) {

			int tess = atoi(argv[2]); // nivel de tesselação
			string input_file = argv[3]; // ficheiro do patch

			nomeF = argv[4];

			//saveFile();

			return 0;
		}

		//desenha cintura de asteroides
		if (strcmp(argv[1], "cintura") == 0 && argc == 7) {

			float raioIn = stof(argv[2]);
			float raioEx = stof(argv[3]);
			int sides = atoi(argv[4]);
			int rings = atoi(argv[5]);

			p->genCintura(raioIn, raioEx, sides, rings);

			nomeF = argv[6];

			saveFile(p, nomeF);

			return 0;
		}

		//desenha cone
		if (strcmp(argv[1], "cone") == 0 && argc == 7) {
			float radius = stof(argv[2]);
			float height = stof(argv[3]);
			int slices = atoi(argv[4]);
			int stack = atoi(argv[5]);
			nomeF = argv[6];

			p->genCone(radius,height,slices,stack);
			saveFile(p, nomeF);
			return 0;
		}
		else { cout << "Nao tem argumentos suficientes ou figura nao existe" << endl; }
		
	}
	
	else{
		cout << "Nao tem argumentos suficientes! Se precisar de ajuda execute 'generator.exe -h'" << endl; 
		return 0;
	}
}
