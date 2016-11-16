/***************************************************
ISGI::Geometria
Roberto Vivo', 2016 (v1.0)

Dibujar formas basicas en OpenGL

Dependencias:
+freeglut +utilidades
***************************************************/
#define PROYECTO "ISGI::S2E01::Geometria"

#include <iostream>									// Biblioteca de entrada salida
//#include <gl\freeglut.h>	// Biblioteca grafica
#include <Utilidades.h>

using namespace std;
static GLfloat coordenadas[10];
static const GLfloat colores[15] = { 1,1,1, 1,0,1, 0,1,1,
								     0,0,1, 1,1,0 };
static const GLuint pentagono[5] = { 0,1,2,3,4 };

void init()
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

	// Cargar el vector de coordenadas
	GLfloat radio = 0.5;
	for (int i = 0; i < 10; i+=2) {
		coordenadas[i] = radio*cos( PI / 5.0 * i);
		coordenadas[i + 1] = radio*sin(PI / 5.0 * i);
	}

	// Habilitar los arrays de OpenGL
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, coordenadas);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colores);



/*
	// Identificador de la lista
	pentagono = glGenLists(1);

	// Construir la lista
	glNewList(pentagono, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	GLfloat radio = 0.5;
	for (int i = 0; i < 5; i++) {
		glVertex3f(	radio*cos(2 * PI / 5.0 * i),
					radio*sin(2 * PI / 5.0 * i),
					0.0);
	}
	glEnd();
	glPopAttrib();
	glEndList();
*/
}

void display()
// Funcion de atencion al dibujo
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0);
	glPointSize(10);
	//glPolygonMode(GL_FRONT, GL_POINT);
	//glCallList(pentagono);
	glDrawElements(GL_POINTS, 5, GL_UNSIGNED_INT, pentagono);
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glCallList(pentagono);
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_INT, pentagono);
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
	glutInitWindowSize(600, 400);						// Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO);							// Creacion de la ventana con su titulo
	cout << PROYECTO << " en marcha" << endl;			// Mensaje por consola
	glutDisplayFunc(display);							// Alta de la funcion de atencion a display
	glutReshapeFunc(reshape);		// Alta de la funcion de atencion a reshape
	init();
	glutMainLoop();										// Puesta en marcha del programa
}
