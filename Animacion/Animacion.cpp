/***************************************************
ISGI::Animacion
Roberto Vivo', 2016 (v1.0)

Manejo del tiempo para animacion en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S5E01::Animacion"

#include <iostream>		
#include <sstream>
#include <gl\freeglut.h>
#define tasaFPS 30

using namespace std;

static float alfa = 0.0;

void FPS()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	int tiempo = (ahora - antes);
	static int fotogramas = 0;

	fotogramas++;
	if (tiempo >= 1000) {
		stringstream titulo;
		titulo << "FPS= " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		fotogramas = 0;
		antes = ahora;
	}
}

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Camara
	gluLookAt(0, 2, 4, 0, 0, 0, 0, 1, 0);

	// Objetos
	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glRotatef(alfa, 0, 1, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	glTranslatef(0.5, 0, 0);
	glRotatef(alfa/2, 0, 1, 0);
	glutWireTeapot(0.5);

	glutSwapBuffers();

	FPS();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	glViewport(0, 0, w, h);

	// Proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (float)w / h, 0.1, 20);
}

void update()
{
	/*
	// Modificar alfa sin coherencia temporal
	alfa += 0.1;
	*/

	// Animacion temporalmente coherente
	static float omega = 360; //grados/segundo
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;

	alfa += omega * tiempo_transcurrido;

	antes = ahora;

	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	glutTimerFunc(tiempo, onTimer, tiempo);
	update();
}

void main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(update);
	glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}
