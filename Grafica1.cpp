
/*#include <GL/glut.h>

void Display_cb()
{
	glutSwapBuffers();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(480, 360);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Ejemplo");
	glutDisplayFunc(Display_cb);
	glutMainLoop();
	return 0;
}*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846
using namespace std;

GLfloat xi = 0.0;
GLfloat yi = 0.0;
GLint escala = 1;
GLdouble puntosx[13];
GLdouble puntosy[13];
GLdouble angulo = 0;



void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void lineMidPoint(float x1, float y1, float x2, float y2)
{
	float r, g, b, al = 1.0f;
	float x, y;
	float a;

	a = (y2 - y1) / (x2 - x1);

	glEnable(GL_POINT_SMOOTH);
	//glPointSize(10.0f);
	glBegin(GL_POINTS);
	glClearColor(1.0, 0, 0, 1.0);
	for (x = x1; x <= x2; x += 0.01f)
	{
		y = (y1 + a * (x - x1));
		glVertex3f(x, y, -1.0f);
	}
	glEnd();
}
void inc_line(int x1, int y1, int x2, int y2)
{
	int dx, dy, incE, incNE, d, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	d = 2 * dy - dx; /* Valor inicial de d */
	incE = 2 * dy; /* Incremento de E */
	incNE = 2 * (dy - dx); /* Incremento de NE */
	x = x1;
	y = y1;
	glVertex3f(x, y, -1.0f);
	while (x < x2) {
		if (d <= 0) {
			/* Escolhe E */
			d = d + incE;
			x = x + 1;
		}
		else {
			/* Escolhe NE */
			d = d + incNE;
			x = x + 1;
			y = y + 1;
		}/* end if */
		glVertex3f(x, y, -1.0f);
	}/* end while */
}/* end inc_line */
void CirclePoint(float x, float y)
{
	glVertex3f(x, y, -1.0f);
	glVertex3f(x, -y, -1.0f);
	glVertex3f(-x, y, -1.0f);
	glVertex3f(-x, -y, -1.0f);
	glVertex3f(y, x, -1.0f);
	glVertex3f(y, -x, -1.0f);
	glVertex3f(-y, x, -1.0f);
	glVertex3f(-y, -x, -1.0f);

}

void circMidPoint(float r)
{
	glColor3f(0.0, 1.0, 0.0);
	//float re,g,b,a=1.0f;
	//float x, y;
	//float d;
	GLfloat x, y, d, x_inc, y_inc;
	/* Valores iniciais */
	x = 0.0f;
	y = r;
	d = 1 - r;

	int deltaE = 3;
	int deltaSE = -2 * r + 5;

	x_inc = 1.0f;
	y_inc = 1.0f;
	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(10.0f);
	glBegin(GL_POINTS);

	CirclePoint(x, y);
	while (y > x)
	{
		if (d < 0)
		{
			/* Selecione E */
			d += deltaE;
			deltaE += x_inc * 2;
			deltaSE += x_inc * 2;
			//x+=x_inc;
		}
		else
		{
			/* Selecione SE */
			d += deltaSE;
			deltaE += x_inc * 2;
			deltaSE += x_inc * 4;
			y -= y_inc;
		}/*end if*/
		x += x_inc;
		CirclePoint(x, y);
		//glVertex2f(x,y);
	}
	glEnd();
}

void MidPointCircleInt(int r) 
{	
	glColor3f(0.0, 0.0, 1.0);
	int x = 0;
	int y = r;
	int d = 1 - r;
	int deltaE = 3;
	int deltaSE = -2 * r + 5;
	CirclePoint(x, y);
	while (y > x) {
		if (d < 0) { /* Selecione E */
			d += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else { /* Selecione SE */
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
		CirclePoint(x, y);
	}
}
void ArrowKey(int key, int x, int y) {
	switch (key)
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
		if (escala > 5)
			escala = 5;
		cout << "Aumentando Escala" << endl;
		escala = escala + 1;
		break;
	case GLUT_KEY_PAGE_UP:
		if (escala <= 1)
			escala = 1;
		cout << "Reduciendo Escala" << endl;
		escala = escala - 1;
		break;

	case GLUT_KEY_PAGE_DOWN:
		cout << "Rotando positivamente" << endl;
		angulo += 5;


		break;

	case GLUT_KEY_END:
		cout << "Rotando negativamente" << endl;
		angulo -= 5;
		break;

	default:
		break;
	}


}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(xi, yi, 0);
	glScaled(escala, escala, 1.0);
	glRotated(angulo, 0.0, 0.0, 1.0);


	//Dibujar
	
	//lineMidPoint(0, 0, 10, 10);
	
	//circMidPoint(10);
	glPointSize(5);


	
	MidPointCircleInt(5);

	

	



	glPopMatrix(); // Cierra la matriz


	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Inicializa la matriz de proyeccion
	glOrtho(-10.0, 10.0, -10.00, 10.0, 0.1, 20.0); // WorkSpace
	glMatrixMode(GL_MODELVIEW); // cambiamos la matrix :D

}
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}





int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Grafica Tarea 1");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(ArrowKey);
	glutMainLoop();



	return 0;
}


