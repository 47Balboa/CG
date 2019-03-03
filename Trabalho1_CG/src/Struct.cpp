#include "headers/Struct.h"

Struct::Struct(){
}

Struct::Struct(vector<Point*> L) {
	LP = L;
}

vector<Point*> Struct::getLP() {
	return LP;
}
	
void Struct::setLP(vector<Point*> L) {
	LP = L;
}

//Responsavel por gerar os pontos dos (2) triângulos pertencentes ao plano.
void Struct::genPlane(float size)
{
	float h = size/2;
	LP.push_back(new Point(-h, 0, h));
	LP.push_back(new Point(h, 0, h));
	LP.push_back(new Point(-h, 0, -h));
	LP.push_back(new Point(-h, 0, -h));
	LP.push_back(new Point(h, 0, h));
	LP.push_back(new Point(h, 0, -h));
}

//Responsavel por gerar os pontos dos triângulos relativos ao cilindro.
void Struct::genCylinder(float radius, float height, int slices) {
	float beta = atan(radius / height);
	float alfa = (float) (2 * (M_PI / slices));
	for (int i = 0; i < slices; i++) {
		float x0 = sin((i + 1)*alfa)*radius;
		float x1 = sin(i*alfa)*radius;
		float z0 = cos((i + 1)*alfa)*radius;
		float z1 = cos(i*alfa)*radius;

		LP.push_back(new Point(x0, -height / 2, z0));
		LP.push_back(new Point(x1, -height / 2, z1));
		LP.push_back(new Point(0.0f, -height / 2, 0.0f));

		LP.push_back(new Point(0.0f, height / 2, 0.0f));
		LP.push_back(new Point(x1, height / 2, z1));
		LP.push_back(new Point(x0, height / 2, z0));
		
		LP.push_back(new Point(x0, -height / 2, z0));
		LP.push_back(new Point(x0, height / 2, z0));
		LP.push_back(new Point(x1, height / 2, z1));
		
		LP.push_back(new Point(x1, -height / 2, z1));
		LP.push_back(new Point(x0, -height / 2, z0));
		LP.push_back(new Point(x1, height / 2, z1));
	}
}

// Responsavel por gerar os pontos dos triangulos relativos a esfara.
void Struct::genSphere(float radius, int slices, int stacks) {

	float h = (float) (M_PI) / stacks;
	float h2 = (float) (2 * M_PI) / slices;

	for (int i = 0; i < slices; i++) {

		for (int j = 0; j < stacks; j++) {

			float x2 = radius * cos((i + 1)*h2)*sin(h);
			float y2 = radius * cos(h);
			float z2 = radius * sin((i + 1)*h2)*sin(h);

			float x3 = radius * cos(i*h2)*sin(h);
			float y3 = radius * cos(h);
			float z3 = radius * sin(i*h2)*sin(h);

			if (j == 0) {

				LP.push_back(new Point(0, radius, 0));
				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin((i + 1)*h2)*sin((j + 1)*h)));
				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin(i*h2)*sin((j + 1)*h)));
			}

			if (j == stacks - 1) {

				LP.push_back(new Point(0, -radius, 0));
				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 1)*h) + x3, -y2, radius*sin(i*h2)*sin((j + 1)*h) + z3));
				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 1)*h) + x2, -y3, radius*sin((i + 1)*h2)*sin((j + 1)*h) + z2));
			}

			else {

				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin((i + 1)*h2)*sin((j + 1)*h)));
				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 2)*h), radius*cos((j + 2)*h), radius*sin((i + 1)*h2)*sin((j + 2)*h)));
				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin(i*h2)*sin((j + 1)*h)));

				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin(i*h2)*sin((j + 1)*h)));
				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 2)*h), radius*cos((j + 2)*h), radius*sin((i + 1)*h2)*sin((j + 2)*h)));
				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 2)*h), radius*cos((j + 2)*h), radius*sin(i*h2)*sin((j + 2)*h)));
			}
		}
	}
}

void Struct::genCone(float radius, float height, int slices, int stacks) {
	float alfa = (float) (2 * M_PI) / slices; //angulo alfa
	float alturaStack = height / stacks; // altura de uma stack 
	float tangenteBeta = height / radius;

	float alturaBaixo = 0; //altura parte de baixo
	float alturaCima; //altura parte de cima
	float raio2; //raio do circulo superior

	//um slice pode ser resumido em quatro pontos 
	//ligados entre a camada superior e inferior
	//   __
	//  /\/
	//   
	float x1, x2, x3, x4, z1, z2, z3, z4;

	float alfaI;
	float alfaIMais1;

	//este ciclo exterior trata das camadas
	//o que faz com que o cone seja
	//desenhado por "andares" 
	//que convergem no topo do cilindro
	for (int j = 1; j <= stacks; j++) {
		alturaCima = alturaStack * j;
		raio2 = (height - alturaCima) / tangenteBeta;

		//este ciclo foca-se num slice particular
		//portanto, quando 
		for (int i = 1; i <= slices + 1; i++) {

			alfaI = alfa * i;
			alfaIMais1 = alfa * (i + 1);

			x1 = radius * sin(alfaI);
			z1 = radius * cos(alfaI);

			x2 = radius * sin(alfaIMais1);
			z2 = radius * cos(alfaIMais1);

			x3 = raio2 * sin(alfaI);
			z3 = raio2 * cos(alfaI);

			x4 = raio2 * sin(alfaIMais1);
			z4 = raio2 * cos(alfaIMais1);

			if (j == 1) {

				//triangulo da base
				LP.push_back(new Point(0, 0, 0));
				LP.push_back(new Point(x2, 0, z2));
				LP.push_back(new Point(x1, 0, z1));

				//triangulos do lado
				LP.push_back(new Point(x1, 0, z1));
				LP.push_back(new Point(x2, 0, z2));
				LP.push_back(new Point(x3, alturaCima, z3));

				LP.push_back(new Point(x2, 0, z2));
				LP.push_back(new Point(x4, alturaCima, z4));
				LP.push_back(new Point(x3, alturaCima, z3));

			}// estamos no topo do cone
			else if (j == stacks) {

				//um unico triangulo no topo (por slice)
				LP.push_back(new Point(x1, alturaBaixo, z1));
				LP.push_back(new Point(x2, alturaBaixo, z2));
				LP.push_back(new Point(0, height, 0));
			}
			else {
				//se nao estivermos no topo ou na base estamos a desenhar os lados do cone

				//triangulos relativos aos lados do cone		
				LP.push_back(new Point(x1, alturaBaixo, z1));
				LP.push_back(new Point(x2, alturaBaixo, z2));
				LP.push_back(new Point(x3, alturaCima, z3));
		
				LP.push_back(new Point(x2, alturaBaixo, z2));
				LP.push_back(new Point(x4, alturaCima, z4));
				LP.push_back(new Point(x3, alturaCima, z3));
			}
		}

		//subimos de patamar
		alturaBaixo = alturaCima;
		//consequentemente tambem muda o circulo da base
		radius = raio2;
	}
}