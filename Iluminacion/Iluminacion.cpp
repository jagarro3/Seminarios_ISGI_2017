/***************************************************
ISGI::Iluminacion
Roberto Vivo', 2016 (v1.0)

Luces y materiales en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S7E01::Iluminacion"

#include <iostream>			
#include <Utilidades.h>
using namespace std;

static float girox = 0, giroy = 0;
static int xanterior, yanterior;

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, BLANCO);

	// Luces
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, BLANCO);
	glLightfv(GL_LIGHT0, GL_SPECULAR, GRISCLARO);

	// Material
	glMaterialfv(GL_FRONT, GL_DIFFUSE, BRONCE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, AMARILLO);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);

	// Sombreado
	glShadeModel(GL_FLAT);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Poner aqui la posicion de la luz si se quiere
	// solidaria a la camara

	// Camara
	gluLookAt(1, 1, 3, 0, 0, 0, 0, 1, 0);
	// Luces en sistema de la escena
	static const float PL0[] = { 0,1,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, PL0);
	// Objetos
	ejes();
	glColor3f(1, 0, 0);
	glRotatef(girox, 1, 0, 0);
	glRotatef(giroy, 0, 1, 0);
	glutSolidTorus(0.2, 0.5, 60, 60);

	glutSwapBuffers();
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

void onClick(int boton, int estado, int x, int y)
{
	// Almacenar el pixel donde se hizo click
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}
}

void onDrag(int x, int y)
{
	static const float pixelgrados = 1.0;
	giroy += (x - xanterior)*pixelgrados;
	girox += (y - yanterior)*pixelgrados;

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
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);

	// Bucle de atencion a eventos
	glutMainLoop();
}
