#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include<GL/glut.h>
#include <QuadTree.h>
#define KEY_ESC 27

using namespace std;

//Crear quad tree
QuadTree qt(-300,300,-300,300,3);
vector<Line> lines;
vector<Point> points;
//dibuja un simple gizmo
void displayGizmo()
{
	/*glBegin(GL_LINES);
	lines=qt.getLines();
	for(unsigned int i=0;i<lines.size();++i){
        glColor3d(255,255,255);
        glVertex2d(lines[i].u.getX(), lines[i].u.getY());
        glVertex2d(lines[i].v.getX(), lines[i].v.getY());
	}
	glEnd();*/
	glBegin(GL_POINTS);
	glPointSize(5.20);
	for(unsigned int i=0;i<points.size();++i){
        glColor3d(0,0,0);
        glVertex2d(points[i].getX(), points[i].getY());
	}
	glEnd();
}


void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    //convertir x,y
    x-=300;
    y-=300;
    y*=-1;
    Point p(x,y);
    qt.insertPoint(p);
    points.push_back(p);
	//insertar un nuevo punto en el quadtree
  }
}

void OnMouseMotion(int x, int y)
{
     //opcional
	 //hacer algo x,z cuando se mueve el mouse
}



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);

	//dibujar quadTree (qt->draw())

	//dibuja el gizmo
	displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.180f, 0.193f, 0.227f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP2 bis OpenGL : Bresenham"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);

	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}
