/***************************************************
ISGI::Interaccion
Roberto Vivo', 2016 (v1.0)

Capturar los eventos del usuario

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S6E01::Interaccion"

#include <iostream>			
#include <gl\freeglut.h>
using namespace std;

static float giroxTA = 0, giroyTA = 0;
static float giroxTB = 0, giroyTB = 0;

static enum {ALAMBRICO,SOLIDO,DOBLE} modo;
static int xanterior, yanterior;
static GLubyte objeto[1];

void onMenu(int valor)
{
	if (valor == 0) modo = ALAMBRICO;
	else if (valor == 1) modo = SOLIDO;
	else modo = DOBLE;
	glutPostRedisplay();
}

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Menu
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Camara
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	// Objetos
	glPushMatrix();
	glTranslatef(0.8, 0, 0);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glColor3f(1, 1, 1);
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glColor3f(1, 0, 0);
		glutSolidTeapot(0.5);
	}
	else {
		glColor3f(1, 1, 1);
		glutWireTeapot(0.51);
		glColor3f(1, 0, 0);
		glutSolidTeapot(0.5);
	}
	glPopMatrix();

	// Tetera B
	glPushMatrix();
	glTranslatef(-0.8, 0, 0);
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glColor3f(1, 1, 1);
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glColor3f(0, 0, 1);
		glutSolidTeapot(0.5);
	}
	else {
		glColor3f(1, 1, 1);
		glutWireTeapot(0.51);
		glColor3f(0, 0, 1);
		glutSolidTeapot(0.5);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void select()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Camara
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	// Objetos
	glPushMatrix();
	glTranslatef(0.8, 0, 0);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
		glColor3f(1, 0, 0);
		glutSolidTeapot(0.5);
	glPopMatrix();

	// Tetera B
	glPushMatrix();
	glTranslatef(-0.8, 0, 0);
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
		glColor3f(0, 0, 1);
		glutSolidTeapot(0.5);
	glPopMatrix();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	glViewport(0, 0, w, h);
	// Proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.1, 10);
}

void onKey(unsigned char tecla, int x, int y)
{
	switch (tecla) {
	case 'a': modo = ALAMBRICO;
		break;
	case 's': modo = SOLIDO;
		break;
	case 'd': modo = DOBLE;
		break;
	case 27: exit(0);
	}
	glutPostRedisplay();
}

void onClick(int boton, int estado, int x, int y)
{
	// Almacenar el pixel donde se hizo click
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}

	// Averiguar el viewport
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int vy = viewport[3] - y;
	select();
	glReadPixels(x, vy, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, objeto);
}

void onDrag(int x, int y)
{
	static const float pixelgrados = 1.0;
	if (objeto[0] == 0x00) {
		// Al mover el raton a derecha la x aumenta y el giro
		// es alrededor del eje Y positivo
		giroyTA += (x - xanterior)*pixelgrados;
		// AL mover el raton abajo la y aumenta y el giro
		// es alrededor del eje X positivo
		giroxTA += (y - yanterior)*pixelgrados;
	}
	else {
		giroyTB += (x - xanterior)*pixelgrados;
		giroxTB += (y - yanterior)*pixelgrados;
	}
	xanterior = x;
	yanterior = y;
	glutPostRedisplay();
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(onKey);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);

	// Bucle de atencion a eventos
	glutMainLoop();
}
