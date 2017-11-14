/***************************************************
ISGI::Camara
Roberto Vivo', 2017 (v1.0)

Uso de la camara virtual en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S4E01::Camara"

#include <iostream>			
#include <gl/freeglut.h>
#include <Utilidades.h>

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

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 0, -3);
	glutWireTeapot(0.5);
	glPopMatrix();

	gluLookAt(-2, 2, 2, 0, 0, 0, 0, 1, 0);

	ejes();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 0.5, 0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 0, -3);
	glutWireTeapot(0.5);
	glPopMatrix();


	glFlush();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	// Marco dentro del area de dibujo
	glViewport(0, 0, w, h);
	float razon = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
	if (razon > 1) {    // El marco es mas ancho que alto
		glOrtho(-2*razon, 2*razon, -2, 2, -2, 2);
	}
	else {
		glOrtho(-2, 2, -2/razon, 2/razon, -2, 2);
	}
	*/
	gluPerspective(60, razon, 0.1, 20);
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}
