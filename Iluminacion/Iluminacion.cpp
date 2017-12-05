/***************************************************
ISGI::Iluminacion
Roberto Vivo', 2017 (v1.0)

Manejo de luces y materiales en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S7E01::Iluminacion"

#include <iostream>		
#include <sstream>
#include <gl/freeglut.h>
#include <Utilidades.h>

using namespace std;

static enum { ALAMBRICO, SOLIDO, DOBLE } modo;
static float girox = 0, giroy = 0;
static float giroxTA = 0, giroyTA = 0, giroxTB = 0, giroyTB = 0;
static float xanterior, yanterior;
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

	// Crear menu de contexto
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Luces 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, BLANCO);
	glLightfv(GL_LIGHT0, GL_SPECULAR, BLANCO);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GRISOSCURO);

	// Materiales
	glMaterialfv(GL_FRONT, GL_DIFFUSE, BLANCO);
	glMaterialfv(GL_FRONT, GL_SPECULAR, AMARILLO);
	glMaterialf(GL_FRONT, GL_SHININESS, 25);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL); // Con glColor podemos cambiar el color difuso

	// Sombreado
	glShadeModel(GL_FLAT);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	GLfloat posicionL0[] = { 0,1,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicionL0);

	// Suelo
	glColor3fv(ROJO);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(-2, -1, 2);
	glVertex3f(2, -1, 2);
	glVertex3f(2, -1, -2);
	glVertex3f(-2, -1, -2);
	glEnd();

	ejes();

	// Tetera blanca
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.7, 0, 0);
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glutSolidTeapot(0.5);
	}
	else {
		glutSolidTeapot(0.5);
		glColor3f(0, 0.5, 0);
		glutWireTeapot(0.51);
	}
	glPopMatrix();

	// Tetera amarilla
	glPushMatrix();
	glColor3fv(BRONCE);
	glTranslatef(-0.7f, 0, 0);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glutSolidTeapot(0.5);
	}
	else {
		glutSolidTeapot(0.5);
		glColor3f(0, 0.5, 0);
		glutWireTeapot(0.51);
	}
	glPopMatrix();



	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	// Marco dentro del area de dibujo
	glViewport(0, 0, w, h);
	float razon = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, razon, 0.1, 20);
}
void select()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

	//ejes();

	// Tetera blanca
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.7, 0, 0);
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();

	// Tetera amarilla
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-0.7f, 0, 0);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();

	glPopAttrib();
	//glutSwapBuffers();
}

void onKey(unsigned char tecla, int x, int y)
{
	switch (tecla) {
	case 'a':
		modo = ALAMBRICO;
		break;
	case 's':
		modo = SOLIDO;
		break;
	case 'd':
		modo = DOBLE;
		break;
	case 27:
		exit(0);
	}
	glutPostRedisplay();
}

void onClick(int boton, int estado, int x, int y)
{
	// Almaceno la coordenada que se pulso
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}
	// Que mide el viewport?
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float vy = viewport[3] - y;
	select();
	glReadPixels(x, vy, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, objeto);
}

void onDrag(int x, int y)
{
	static const float pixel2grados = 1;
	/*
	// Al mover el cursor hacia la derecha la x aumenta y el giro es
	// alrededor de y positivo
	giroy += (x - xanterior)*pixel2grados;
	// Al mover el curso hacia abajo la y aumenta y el giro es
	// alrededor de x positivo
	girox += (y - yanterior)*pixel2grados;
	*/
	if (objeto[0] == 0x00) {
		giroyTA += (x - xanterior)*pixel2grados;
		giroxTA += (y - yanterior)*pixel2grados;
	}
	else {
		giroyTB += (x - xanterior)*pixel2grados;
		giroxTB += (y - yanterior)*pixel2grados;
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
	glutInitWindowSize(600, 600);
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
