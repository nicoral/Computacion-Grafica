#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <time.h>
#include <cstring>
#define pi 3.14159265358979323846

using namespace std;

// define glu objects

GLUquadricObj* cilindro;
GLUquadricObj* disco;

// lighting
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[] = { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; // light on = 1, light off = 0
static int view_state = 1; // Ortho view = 1, Perspective = 0

GLfloat xi = 0.0;
GLfloat yi = 0.0;
//Valor inicial de lados de un poligono
GLint numLados = 1;
//Valor inicial de escalamiento
GLint escala = 1;
//Vectores de almacen de los poligonos (12 lados maximos)
GLdouble puntosx[13];
GLdouble puntosy[13];
//Angulo inicial para la rotacion
GLdouble angulo = 0;

//Valores para el circulo y linea en caso de elegir la opcion
GLint radio = 3;
float x0 = 0.0;
float yy = 0.0;
float x1 = 5.0;
float yy2 = 3.0;
//Valores del mouse
bool pressed;
double preMouseX, preMouseY, actualMouseX, actualMouseY;

void Sprint(int x, int y, char* st)
{
	int l, i;
	l = strlen(st);
	glRasterPos3i(x, y, -1);

	for (i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}

}
static void TimeEvent(int te)
{
	int timent;
	int i;

	glutPostRedisplay();
	glutTimerFunc(100, TimeEvent, 1);
}
void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	// Lighting is added to scene
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	cilindro = gluNewQuadric();
	gluQuadricDrawStyle(cilindro, GLU_FILL);
	gluQuadricNormals(cilindro, GLU_SMOOTH);
	gluQuadricOrientation(cilindro, GLU_OUTSIDE);
	gluQuadricTexture(cilindro, GL_TRUE);



}

void tecla(int tecla, int x, int y) {
	switch (tecla)
	{
	case GLUT_KEY_RIGHT:
		if (xi < 10)
			xi += 0.5;
		break;

	case GLUT_KEY_LEFT:
		if (xi > -10)
			xi -= 0.5;
		break;

	case GLUT_KEY_UP:
		if (yi < 10)
			yi += 0.5;
		break;

	case GLUT_KEY_DOWN:
		if (yi > -10)
			yi -= 0.5;
		break;

	case GLUT_KEY_HOME:
		escala = escala + 1;
		break;
	case GLUT_KEY_PAGE_UP:
		if (escala <= 1)
			escala = 1;
		else
			escala = escala - 1;
		break;

	case GLUT_KEY_PAGE_DOWN:
		angulo += 5;
		break;

	case GLUT_KEY_END:
		angulo -= 5;
		break;

	default:
		break;
	}


}

void mouse(int mouse, int state, int x, int y)
{

	if (mouse == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		actualMouseX= x;
		actualMouseY = y;
		pressed = true;
	}
	else if (mouse == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		preMouseX = x;
		preMouseY = y;
		pressed = false;
	}

}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, 8.0, -8.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xi, yi, 0);
	glScaled(escala, escala, 1.0);
	glRotated(angulo, 0.0, 0.0, 1.0);


	// Turn Perspective mode on/off
	if (view_state == 0)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(60.0, 1, 1.0, 30.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	if (light_state == 1)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL); // Enable for lighing
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL); // Disable for no lighing
	}
	if (pressed) {
		double x = preMouseX - actualMouseX;
		double y = preMouseY - actualMouseY;
		double lenVector = sqrt(pow(x, 2) + pow(y, 2));
		if (lenVector != 0) {
			xi -= (x / lenVector) * 0.1;
			yi -= (y / lenVector) * 0.1;
		}
		cout << xi << "\t" << yi << endl;
		gluLookAt(0, 0, -5, xi, yi, 0, 0, 1, 0);
	}
	

	glPushMatrix();

	glTranslatef(0, 0, -14);
	glRotatef(180, 1.0, 0.0, 0.0);

	glPushMatrix();// Draw hour hand
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(0, 0, 0.0);
	gluCylinder(cilindro, 0.75, 0, 4, 16, 16);

	glPushMatrix();// Draw next arm axis.
	glColor3f(0.0, 1.0, 1.0); // give it a color
	glTranslatef(5.0, 5.0, 0.0);
	glutSolidCube(1.0);

	glEnd();
	glPopMatrix(); // Cierra la matriz
	glFlush();
	glutSwapBuffers();




}



void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Inicializa la matriz de proyeccion
	glOrtho(-10.0, 10.0, -10.00, 10.0, 0.1, 20.0); // WorkSpace
	glMatrixMode(GL_MODELVIEW); // cambiamos la matrix :D

}
void keyboard(unsigned char tecla, int x, int y) 
{
	if (tecla == 'V' || tecla == 'v') {
		view_state = abs(view_state - 1);
		cout << view_state << endl;
	}
}


int main(int argc, char** argv)
{
	cout << "Teclas de direccion para moverse " << endl;
	cout << "Page_Down-Rotacion positiva || End-Rotacion negativa" << endl;
	cout << "Home-Aumentar escalado || Page_UP-Disminuir escalado" << endl;
	cout << "Tecla V para cambiar la perspectiva" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Poligonos");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(tecla);
	glutMouseFunc(mouse);
	glutMainLoop();



	return 0;
}