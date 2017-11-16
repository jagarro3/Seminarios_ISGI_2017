/***************************************************
ISGI::Animacion
Roberto Vivo', 2017 (v1.0)

Manejo del tiempo en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S5E01::Animacion"

#include <iostream>		
#include <sstream>
#include <gl/freeglut.h>
#include <Utilidades.h>

using namespace std;

#define tasaFPS 60

// variable que depende del tiempo
static float alfa = 0;

void init()
// Inicializaciones
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void muestraFPS()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int fotogramas = 0;
	int ahora, tiempo_transcurrido;

	// Cada que pase por aqui incremento los fotogramas
	fotogramas++;

	// Calculo el tiempo transcurrido
	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_transcurrido = ahora - antes;
	// si ha transcurrido un segundo, mostrar los fotogramas
	if (tiempo_transcurrido > 1000) {
		// modificar la barra de titulo
		stringstream titulo;
		titulo << "FPS= " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		// reinicio a cuenta
		fotogramas = 0;
		antes = ahora;
	}

}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 2, 2, 0, 0, 0, 0, 1, 0);

	ejes();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0.7, 0, 0);
	glRotatef(alfa, 0, 1, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-0.7f, 0, 0);
	glRotatef(alfa / 2, 0, 1, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	muestraFPS();

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
	gluPerspective(60, razon, 0.1, 20);
}

void update()
{
	/*
	// Variar la variable entre frames sin control de tiempo
	alfa += 0.5;
	*/

	// Animacion coherente con el tiempo transcurrido
	static const float omega = 1;	// vueltas por segundo

	// Incialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	// Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;

	alfa += omega * 360 * tiempo_transcurrido;
	antes = ahora;


	// Encolar un evento de redibujo
	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	// Sirve para re-arrancar el reloj de cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);

	update();
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
	//glutIdleFunc(update);
	glutTimerFunc(1000 / tasaFPS, onTimer, 1000 / tasaFPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}
