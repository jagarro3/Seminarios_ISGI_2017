/***************************************************
ISGI::Transformaciones
Roberto Vivo', 2017 (v1.0)

Dibujar una flor con transformaciones en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S3E01::FLOR"

#include <iostream>			
#include <gl/freeglut.h>
#include <Utilidades.h>

using namespace std;

static GLuint petalo, corola, flor;

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	petalo = glGenLists(1);
	glNewList(petalo, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);
	glScalef(0.3 / 2.0, 1.0 / 2.0, 0.3 / 2.0);
	glutSolidSphere(1, 20, 20);
	glPopAttrib();
	glEndList();

	corola = glGenLists(1);
	glNewList(corola, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);

	//petalos de la corola
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glRotatef(i*360.0 / 12.0 + 15, 0, 0, 1);
		glTranslatef(0, 0.25, 0);
		glScalef(0.5, 0.5, 0.5);
		glCallList(petalo);
		glPopMatrix();
	}

	glColor3f(1, 1, 0);
	glScalef(0.4 / 2.0, 0.4 / 2.0, 0.4 / 2.0);
	glutSolidSphere(1, 20, 20);
	glPopAttrib();
	glEndList();

	flor = glGenLists(1);
	glNewList(flor, GL_COMPILE);
	// tallo
	glPushMatrix();
	glColor3f(0,1,0),
	glTranslatef(0, -0.25 / 2.0, 0);
	glScalef(0.05 / 1.0, 0.75 / 1.0, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	// corola
	glPushMatrix();
	glTranslatef(0, 0.25, 0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(corola);
	glPopMatrix();
	glEndList();


	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//ejes();
	for (int i = 0; i < 50; i++) {
		glPushMatrix();
		glTranslatef((rand() % 200 - 100) / 100.0, (rand() % 100 - 50) / 100.0, 0);
		glScalef(0.5, 0.5, 0.5);
		glCallList(flor);
		glPopMatrix();
	}


	glFlush();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}
