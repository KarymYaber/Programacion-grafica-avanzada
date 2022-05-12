#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <glut.h> //the glut file for windows operations
#include <cmath>     // it also includes gl.h and glu.h for the openGL library calls
#include <conio.h> 
#include <iostream>
using namespace std;

#define VK_W 0x57
#define VK_S 0x53

#define PI 3.1415926535898 
int p1 = 0, p2 = 0;
int deltaTime;
int oldTime;
double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
double xsqpos, ysqpos, ysqdir, xsq2pos, ysq2pos, ysq2dir;
float SPEED = .3f;        // speed of timer call back in msecs
bool pongHit, boolx, booly;
double windowX = 640, windowY = 480;

GLfloat RadiusOfBall = 5, ball_speed = 0.2;;


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

void DeltaTime() {

	int startTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = startTime - oldTime;
	oldTime = startTime;

}


void Hit() {
	if (xpos <= 30. && xpos >= 25. && ypos >= ysqpos && ypos <= (ysqpos + 60.) && xdir == -1.) {
		pongHit = true;

	}
	
	if (xpos >= (windowX / 2.) - 30. && xpos <= (windowX / 2.) - 25. && ypos >= ysq2pos && ypos <= (ysq2pos + 60.) && xdir == 1.) {
		pongHit = true;

	}
}
void ball()
{

	if (pongHit) {
		boolx = !boolx;
		pongHit = false;
	}
	else {
		if (xpos < RadiusOfBall) {
			p2++;
			system("cls");
			cout << "P1: " << p1 << "        " << "P2: " << p2 << endl;
			xpos = windowX / 4.;      xdir = -1.;
			ypos = windowX / 4.;      ydir = -1.;
		}
		else if (xpos > (windowX / 2.) - RadiusOfBall) {
			p1++;
			system("cls");
			cout << "P1: " << p1 << "        " << "P2: " << p2 << endl;
			xpos = windowX / 4.;      xdir = 1.;
			ypos = windowX / 4.;      ydir = 1.;
		}

		if (ypos < RadiusOfBall) {
			booly = true;
		}
		else if (ypos > (windowY / 2.) - RadiusOfBall) {
			booly = false;
		}
	}
}

void draw_ball() {
	glColor3f(0, 0, 0.);
	MyCircle2f(0., 0., RadiusOfBall);

}

void processKeys() {
	

	if (GetAsyncKeyState(VK_UP)) {
		if (ysqpos >= (windowY / 2) - 60.) {
			ysqdir = 0.;
		}
		else {
			ysqdir = 1.;
		}

	}

	if (GetAsyncKeyState(VK_DOWN)) {
		if (ysqpos <= 0.) {
			ysqdir = 0.;
		}
		else {
			ysqdir = -1.;
		}
	}
	if (GetAsyncKeyState(VK_W)) {
		if (ysq2pos >= (windowY / 2) - 60.) {
			ysq2dir = 0.;
		}
		else {
			ysq2dir = 1.;
		}
	}
	if (GetAsyncKeyState(VK_S)) {
		if (ysq2pos <= 0.) {
			ysq2dir = 0.;
		}
		else {
			ysq2dir = -1.;
		}
	}

}

// Draw the ball, centered at the origin

void DrawPlayer() {
	glColor3f(0., 0., 0.);
	glRectf(0, 0, 10, 60);
}


/*void draw_square1() {
	glColor3f(0., 0., 0.);
	MySquare1f(0., 0., 0.);

}*/
void PlayerIzq()
{
	ysqpos = ysqpos + (ysqdir * SPEED * deltaTime);
	processKeys();
	ysqdir = 0.;
	glTranslatef(20., ysqpos, 0.);
	DrawPlayer();
}
void PlayerDer() {
	ysq2pos = ysq2pos + (ysq2dir * SPEED * deltaTime);
	processKeys();
	ysq2dir = 0.;
	glTranslatef((windowX / 2.) - 30., ysq2pos, 0.);
	DrawPlayer();
}

void Circle() {
	xpos = xpos + (xdir * ball_speed * deltaTime);
	ypos = ypos + (ydir * ball_speed * deltaTime);
	Hit();
	ball();
	if (boolx) { xdir = 1; }
	else { xdir = -1; }
	if (booly) { ydir = 1; }
	else { ydir = -1; }
	glTranslatef(xpos, ypos, 0.); 
	draw_ball();
}
void Update() {
	PlayerIzq();
	glPopMatrix();
	glPushMatrix();
	PlayerDer();
	glPopMatrix();
	glPushMatrix();
	DeltaTime();
	glLoadIdentity();
	glPushMatrix();
	Circle();
	glPopMatrix();
	glPushMatrix();
	
}
void Display(void)
{
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	Update();                 
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	// on reshape and on startup, keep the viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// keep our logical coordinate system constant
	gluOrtho2D(0.0, windowX / 2, 0.0, windowY / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void init(void) {
	//set the clear color to be white
	glClearColor(1, 1, 1, 1.0);

	xpos = windowX / 4.;      xdir = 1.;
	ypos = windowX / 4.;      ydir = 1.;
	ysqpos = 0.; ysqdir = 0.;
	ysq2pos = 0.; ysq2dir = 0.;
	cout << "P1: " << p1 << "        " << "P2: " << p2 << endl;

	
}


void main(int argc, char* argv[])
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowX, windowY);
	glutCreateWindow("Pong");
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
