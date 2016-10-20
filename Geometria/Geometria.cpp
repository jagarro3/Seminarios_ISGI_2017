/***************************************************
ISGI::Geometria
Roberto Vivo', 2016 (v1.0)

Dibujo basico de formas

Dependencias:
+freeglut +utilidades
***************************************************/
#define PROYECTO "ISGI::S2E01::Geometria"

#include <iostream>									// Biblioteca de entrada salida
#include <gl\freeglut.h>							// Biblioteca grafica
using namespace std;

// Globales
static GLfloat coordenadas[10];
static const GLfloat colores[15] = { 1,1,1, 1,0,1, 0,1,1,
									 1,1,0, 0,0,1 };
static const GLuint pentagono[5] = { 0,1,2,3,4, };

void init()
// Funcion de inicio
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	GLfloat radio = 0.5;
	for (int i = 0; i < 10; i+=2) {
		coordenadas[i] = radio*cos(i * 3.1415926 / 5);
		coordenadas[i + 1] = radio*sin(i * 3.1415926 / 5);
	}

	// Habilitar arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, coordenadas);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colores);

/*	// Lista para dibujar el pentagono
	pentagono = glGenLists(1);
	glNewList(pentagono, GL_COMPILE);
	//glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT | GL_POINT_BIT);
	//glColor3f(1.0, 1.0, 0.0);
	glPointSize(10);
	//glPolygonMode(GL_FRONT, GL_POINT);
	glBegin(GL_POLYGON);
	GLfloat radio = 0.5;
	for (int i = 0; i < 5; i++) {
		glVertex3f(radio*cos(i * 2 * 3.1415926 / 5),
			radio*sin(i * 2 * 3.1415926 / 5),
			0.0);
	}
	glEnd();
	//glPopAttrib();
	glEndList();
*/

}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Dibujo un pentagono en modo retenido (lista)

	glColor3f(1.0, 0.0, 0.0);
	//glPolygonMode(GL_FRONT, GL_FILL);
//	glCallList(pentagono);
	glDrawElements(GL_LINE_LOOP, 5, GL_UNSIGNED_INT, pentagono);
	//glColor3f(1.0, 1.0, 1.0);
	//glPolygonMode(GL_FRONT, GL_LINE);
//	glCallList(pentagono);

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
	glutReshapeFunc(reshape);					// Alta de la funcion de atencion a reshape
	init();
	glutMainLoop();										// Puesta en marcha del programa
}
