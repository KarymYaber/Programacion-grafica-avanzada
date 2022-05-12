#include <windows.h> //the windows include file, required by all windows applications
#include <glut.h> //the glut file for windows operations
// it also includes gl.h and glu.h for the openGL library calls
#include <math.h>
#include <conio.h>


#define PI 3.1415926535898 

double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
double xsqpos = 50, xsq2pos;
double ysqpos = 60, ysq2pos;

double sx, sy, squash;          // xy scale factors
double rot, rdir;             // rotation 
float SPEED = 2.f;        // speed of timer call back in msecs
bool pongHit;
double windowX = 640, windowY = 480;
GLfloat T1[16] = { 1.,0.,0.,0.,\
				  0.,1.,0.,0.,\
				  0.,0.,1.,0.,\
				  0.,0.,0.,1. };
GLfloat S[16] = { 1.,0.,0.,0.,\
				 0.,1.,0.,0.,\
				 0.,0.,1.,0.,\
				 0.,0.,0.,1. };
GLfloat T[16] = { 1.,0.,0.,0.,\
				 0., 1., 0., 0.,\
				 0.,0.,1.,0.,\
				 0.,0.,0.,1. };



#define PI 3.1415926535898 
GLint circle_points = 100;
GLint square_points = 4;
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius) {
	GLint i;
	GLdouble angle;
	glBegin(GL_POLYGON);
	for (i = 0; i < circle_points; i++) {
		angle = 2 * PI * i / circle_points;
		glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));
	}
	glEnd();
}

void MySquare1f(GLfloat x1, GLfloat y1, GLfloat sidelength) {
	GLint a;
	sidelength = 20;

	glBegin(GL_POLYGON);
	for (a = 0; a < square_points; a++) {

		glVertex2f(x1 + sidelength / 4, y1 + sidelength);
		glVertex2f(x1 + sidelength / 4, y1 - sidelength);
		glVertex2f(x1 - sidelength / 4, y1 - sidelength);
		glVertex2f(x1 - sidelength / 4, y1 + sidelength);
	}
	glEnd();
}

void MyCircle1f(GLfloat centerx, GLfloat centery, GLfloat radius) {
	GLint a;
	GLdouble angle;
	glBegin(GL_POLYGON);
	for (a = 0; a < circle_points; a++) {
		angle = 4 * PI * a / circle_points / 2;
		glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));
	}
	glEnd();
}

GLfloat RadiusOfBall = 5.;
GLfloat RadiusOfBall2 = 20.;

// Draw the ball, centered at the origin
void draw_ball() {
	glColor3f(1, 1, 1.);
	MyCircle2f(0., 0., RadiusOfBall);

}

void draw_square1() {
	glColor3f(0., 0., 0.);
	MySquare1f(0., 0., 0.);

}

/*void draw_ball2() {
	glColor3f(0.4, 0.6, 0.);
	MyCircle1f(50, 50, RadiusOfBall2);
}*/void processKeys(int key, int x, int y) {
	if (key == '0')
		exit(0);

	if (key == GLUT_KEY_UP) {
		ysqpos = ysqpos + 5;

	}

	if (key == GLUT_KEY_DOWN) {
		ysqpos = ysqpos - 5;

	}

}
void ball()
{
	//Hit Left Pong
	if (xpos <= 30. && xpos >= 25. && ypos >= ysqpos && ypos <= (ysqpos + 60.) && xdir == -1.) {
		pongHit = true;

	}
	//Hit Right Pong
	if (xpos >= (windowX / 2.) - 30. && xpos <= (windowX / 2.) - 25. && ypos >= ysq2pos && ypos <= (ysq2pos + 60.) && xdir == 1.) {
		pongHit = true;
		
	}
	ypos = ypos + ydir * SPEED;
	xpos = xpos + xdir * SPEED;

	if (ypos >= 120. - RadiusOfBall) {
		ydir = -1;
		pongHit = false;



	}
	// If ball touches the bottom, change direction of ball upwards
	else if (ypos < RadiusOfBall) {
		ydir = 1;
		pongHit = false;
	}

	//x horizontal
	if (xpos >= 160. - RadiusOfBall) {
		xdir = -1;
		pongHit = false;


	}

	// If ball touches the bottom, change direction of ball upwards
	else if (xpos < RadiusOfBall) {
		xdir = 1;
		pongHit = false;
	}
	if (pongHit == true)
	{
		xdir = 1;
	}
	
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0.);
	draw_ball();
}
void PlayerIzq()
{
	

	// If ball touches the bottom, change direction of ball upwards
	/**/

	//x horizontal
	/*if (xpos >= xsqpos - RadiusOfBall) {
		xdir = -1;
		if (ypos >= ysqpos - RadiusOfBall) {
			ydir = -1;

		}
		else if (ysqpos < RadiusOfBall) {
			ydir = 1;

		}

	}
	else if (xsqpos < RadiusOfBall) {
		ydir = 1;

	}*/


	// If ball touches the bottom, change direction of ball upwards
	/*else if (xpos < RadiusOfBall) {
		xdir = 1;
	}*/
	glLoadIdentity();
	glTranslatef(xsqpos, ysqpos, 0.);
	draw_square1();
}
void Update()
{
	ball();
	PlayerIzq();
}

void Display(void)
{
	Update();
	processKeys;
	glutSwapBuffers();

	//clear all pixels with the specified clear color
	glClear(GL_COLOR_BUFFER_BIT);

	glutPostRedisplay();

}


void reshape(int w, int h)
{
	// on reshape and on startup, keep the viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// keep our logical coordinate system constant
	gluOrtho2D(0.0, 160.0, 0.0, 120.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void init(void) {
	//set the clear color to be white
	glClearColor(0.0, 0.8, 0.0, 1.0);
	// initial house position set to 0,0
	xpos = 60; ypos = RadiusOfBall; xdir = 1; ydir = 1;

	sx = 1.; sy = 1.;
	rot = 0;

}


void main(int argc, char* argv[])
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(320, 240);
	glutCreateWindow("Bouncing Ball");
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(processKeys);
	glutMainLoop();
}
