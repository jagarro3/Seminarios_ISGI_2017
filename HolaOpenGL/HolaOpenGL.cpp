/***************************************************
ISGI::Hola OpenGL
Roberto Vivo', 2016 (v1.0)

Esqueleto basico de un programa en OpenGL

Dependencias:
+freeglut
***************************************************/
#define PROYECTO "ISGI::S1E01::Hola Mundo"

#include <iostream>			
#include <gl\freeglut.h>
using namespace std;

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
	glutInitWindowSize(600, 400);						
	glutCreateWindow(PROYECTO);	
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);							
	glutReshapeFunc(reshape);	

	// Bucle de atencion a eventos
	glutMainLoop();										
}
