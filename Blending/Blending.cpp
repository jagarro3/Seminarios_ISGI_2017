/***************************************************
ISGI::Blending
Roberto Vivo', 2016 (v1.0)

Texturas en OpenGL

Dependencias:
+freeglut, +freeimage
***************************************************/
#define PROYECTO "ISGI::S9E01::Blending"

#include <iostream>			
#include <Utilidades.h>
using namespace std;

static float girox = 0, giroy = 0;
static int xanterior, yanterior;
static GLuint tex;
static GLuint ventana;

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
	glMaterialf(GL_FRONT, GL_SHININESS, 60);

	// Sombreado
	glShadeModel(GL_SMOOTH);

	// Texturas
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	loadImageFile("nubes.jpg");

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &ventana);
	glBindTexture(GL_TEXTURE_2D, ventana);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	loadImageFile("ventana.png");

	// separar textura de brillos
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,
	//	GL_SEPARATE_SPECULAR_COLOR);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, tex);
	texturarFondo();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Poner aqui la posicion de la luz si se quiere
	// solidaria a la camara

	// Camara
	gluLookAt(2, 2, 3, 0, 0, 0, 0, 1, 0);
	// Luces en sistema de la escena
	static const float PL0[] = { 0,1,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, PL0);
	// Objetos
	ejes();

	glRotatef(girox, 1, 0, 0);
	glRotatef(giroy, 0, 1, 0);

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	// esferica
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glutSolidTorus(0.3, 0.5, 40, 40);
	glPopAttrib();

	// Ventana solidaria a la camara cubriendo todo
	// el volumen de la vista
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, ventana);
	static GLfloat v0[] = { -1,-1,0 };
	static GLfloat v1[] = { 1,-1,0 };
	static GLfloat v2[] = { 1, 1,0 };
	static GLfloat v3[] = { -1, 1,0 };
	quadtex(v0, v1, v2, v3, 0, 1, 0, 1);
	glDepthMask(GL_TRUE);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

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
	// Uso de freeimage
	FreeImage_Initialise();
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);

	// Bucle de atencion a eventos
	glutMainLoop();
	FreeImage_DeInitialise();
}
