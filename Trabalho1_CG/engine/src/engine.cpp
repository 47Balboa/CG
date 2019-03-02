
#include "headers/parser.h"
#include <GL/glut.h>

vector<Point*> LP;



void help() {
	cout << "*---------------------------------HELP--------------------------------------*" << endl;
	cout << "|                                                                           |" << endl;
	cout << "|      Modo de utilizacao:                                                  |" << endl;
	cout << "|                       engine.exe (ficheiro xml)                           |" << endl;
	cout << "|   Nota: Os ficheiros 3d tem de estar gerados (pelo generator).            |" << endl;
	cout << "|                                                                           |" << endl;
	cout << "|                                                                           |" << endl;
	cout << "|            Exemplo de utilizacao:                                         |" << endl;
	cout << "|                          engine.exe plane.xml                             |" << endl;
	cout << "|                                                                           |" << endl;
	cout << "*---------------------------------------------------------------------------*" << endl;

}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawFigure() {
	int size = LP.size();
	int i = 0;
	while (i < size) {
		glBegin(GL_TRIANGLES);
		glColor3f(256, 0, 0);
		glVertex3f(LP[i]->getX(), LP[i]->getY(), LP[i]->getZ());
		glVertex3f(LP[i+1]->getX(), LP[i+1]->getY(), LP[i+1]->getZ());
		glVertex3f(LP[i+2]->getX(), LP[i+2]->getY(), LP[i+2]->getZ());
		glEnd();
		i += 3;
	}
}


void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	//px = 3.0;
	//py = 3.0;
	//pz = 3.0;

	gluLookAt(4.0, 4.0, 4.0,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	drawFigure(); // desenha a figura pretendida

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	// put code to process regular keys


}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here

}

int main(int argc, char **argv) {
	

	if (argc == 2) {
		if (!strcmp(argv[1], "-h")) { help(); return 0;}
		string name = readXML(argv[1]);
		readFile(name, &LP);
	}
	else { cout << "Nao esta a passar os argumentos corretos! Se precisar de ajuda, execute o comando 'engine.exe -h'" << endl; return 0; }

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TrabalhoCG-Fase1-Engine");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
