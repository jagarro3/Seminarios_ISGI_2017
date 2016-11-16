/***************************************************
ISGI::Camara
Roberto Vivo', 2016 (v1.0)

Uso de camaras, marcos y visibilidad en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S4E01::Camara"

#include <iostream>			
#include <utilidades.h>
using namespace std;

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.5, 1, 1, 0, 0, 0, 0, 1, 0);

	ejes();

	glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(0.5);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(0.51);

	glColor3f(0, 1, 0);
	glutSolidSphere(0.3,10,10);

	glFlush();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	float razon = (float)w / h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w>h)
		glOrtho(-0.7*razon, 0.7*razon, -0.7, 0.7, -4, 4);
	else
		glOrtho(-0.7, 0.7, -0.7/razon, 0.7/razon, -4, 4);

	//gluPerspective(60, razon, 0.1, 20);
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}
