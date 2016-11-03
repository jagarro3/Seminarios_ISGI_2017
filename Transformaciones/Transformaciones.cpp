/***************************************************
ISGI::Transformaciones
Roberto Vivo', 2016 (v1.0)

Dibujar una flor con listas y transformaciones

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S3E01::Flor"

#include <iostream>									// Biblioteca de entrada salida
#include <gl\freeglut.h>							// Biblioteca grafica
using namespace std;

static GLuint petalo, corola, flor;

void init()
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	// Petalo
	petalo = glGenLists(1);
	glNewList(petalo,GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glScalef(0.15, 0.5, 0.05);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	glPopAttrib();
	glEndList();

	// Corola
	corola = glGenLists(1);
	glNewList(corola, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glRotatef(i*360.0 / 12, 0, 0, 1);
		glTranslatef(0,0.25,0);
		glScalef(0.5, 0.5, 1.0);
		glCallList(petalo);
		glPopMatrix();
	}
	glColor3f(1.0, 1.0, 0.0);
	glScalef(0.2, 0.2, 0.05);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	glPopAttrib();
	glEndList();

	// Flor
	flor = glGenLists(1);
	glNewList(flor, GL_COMPILE);
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0, -0.75 / 2.0, 0);
	glScalef(0.10, 1.25, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0, 0.5, 0);
	glCallList(corola);

	glPopMatrix();
	glPopAttrib();
	glEndList();

}

void display()
// Funcion de atencion al dibujo
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glCallList(flor);
	glFlush();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
}

void main(int argc, char** argv)
// Programa principal
{
	glutInit(&argc, argv);								// Inicializacion de GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);		// Alta de buffers a usar
	glutInitWindowSize(600, 600);						// Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO);							// Creacion de la ventana con su titulo
	cout << PROYECTO << " en marcha" << endl;			// Mensaje por consola
	glutDisplayFunc(display);							// Alta de la funcion de atencion a display
	glutReshapeFunc(reshape);							// Alta de la funcion de atencion a reshape
	init();
	glutMainLoop();										// Puesta en marcha del programa
}
