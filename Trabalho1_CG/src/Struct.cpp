#include "headers/Struct.h";

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
	float alfa = 2 * (M_PI / slices);
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
	float texDivY = 1.0 / stacks;
	float texDivX = 1.0 / slices;
	float texYcima, texYbaixo;
	float texXesq = 0, texXdir = 0 + texDivX;

	float h = (M_PI) / stacks;
	float h2 = (2 * M_PI) / slices;

	for (int i = 0; i < slices; i++, texXesq += texDivX, texXdir += texDivX) {

		for (int j = 0; j < stacks; j++) {

			float x2 = radius * cos((i + 1)*h2)*sin(h);
			float y2 = radius * cos(h);
			float z2 = radius * sin((i + 1)*h2)*sin(h);

			float x3 = radius * cos(i*h2)*sin(h);
			float y3 = radius * cos(h);
			float z3 = radius * sin(i*h2)*sin(h);

			if (j == 0) {
				texYcima = 1.0;
				texYbaixo = 1.0 - texDivY;

				LP.push_back(new Point(0, radius, 0));
				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin((i + 1)*h2)*sin((j + 1)*h)));
				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 1)*h), radius*cos((j + 1)*h), radius*sin(i*h2)*sin((j + 1)*h)));
			}

			if (j == stacks - 1) {
				texYcima = 0.0 + texDivY;
				texYbaixo = 0.0;

				LP.push_back(new Point(0, -radius, 0));
				LP.push_back(new Point(radius*cos(i*h2)*sin((j + 1)*h) + x3, -y2, radius*sin(i*h2)*sin((j + 1)*h) + z3));
				LP.push_back(new Point(radius*cos((i + 1)*h2)*sin((j + 1)*h) + x2, -y3, radius*sin((i + 1)*h2)*sin((j + 1)*h) + z2));
			}

			else {
				texYcima = 1.0 - j * texDivY;
				texYbaixo = 1.0 - (j + 1.0)*texDivY;

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