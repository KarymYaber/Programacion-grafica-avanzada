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
double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
double xsqpos, ysqpos, ysqdir, xsq2pos, ysq2pos, ysq2dir;
float SPEED = 3.f;        // speed of timer call back in msecs
bool Hit, boolx, booly;

GLfloat RadiusOfBall = 5, ball_speed = 2.2f;


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

void draw_ball() {
	glColor3f(0, 0, 0.);
	MyCircle2f(0., 0., RadiusOfBall);

}

	
void ball()
{
	if (xpos <= 30. && xpos >= 25. && ypos >= ysqpos && ypos <= (ysqpos + 60.) && xdir == -1.) {
		Hit = true;

	}

	if (xpos >= 290. && xpos <= 295. && ypos >= ysq2pos && ypos <= (ysq2pos + 60.) && xdir == 1.) {
		Hit = true;

	}

	if (Hit) {
		boolx = !boolx;
		Hit = false;
	}
	else {
		if (xpos < RadiusOfBall) {
			p2++;
			system("cls");
			cout << "P1: " << p1 << "        " << "P2: " << p2 << endl;
			xpos = 160.;      xdir = -1.;
			ypos = 160.;      ydir = -1.;
		}
		else if (xpos > 320. - RadiusOfBall) {
			p1++;
			system("cls");
			cout << "P1: " << p1 << "        " << "P2: " << p2 << endl;
			xpos = 160.;      xdir = 1.;
			ypos = 160.;      ydir = 1.;
		}

		if (ypos < RadiusOfBall) {
			booly = true;
		}
		else if (ypos > 240. - RadiusOfBall) {
			booly = false;
		}
	}
	xpos = xpos + (xdir * ball_speed);
	ypos = ypos + (ydir * ball_speed);
	if (boolx) { xdir = 1; }
	else { xdir = -1; }
	if (booly) { ydir = 1; }
	else { ydir = -1; }
	glTranslatef(xpos, ypos, 0.);
	draw_ball();
}



void processKeys() {
	

	if (GetAsyncKeyState(VK_UP)) {
		ysqdir = 1.;

	}

	if (GetAsyncKeyState(VK_DOWN)) {
		
			ysqdir = -1.;
		
	}
	if (GetAsyncKeyState(VK_W)) {
		
			ysq2dir = 1.;
		
	}
	if (GetAsyncKeyState(VK_S)) {
		
		
			ysq2dir = -1.;
		
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
void Player_IZQ()
{
	ysqpos = ysqpos + (ysqdir * SPEED);
	processKeys();
	ysqdir = 0.;
	glTranslatef(20., ysqpos, 0.);
	DrawPlayer();
	
}
void Player_DER()
{
	
	ysq2pos = ysq2pos + (ysq2dir * SPEED);
	processKeys();
	ysq2dir = 0.;
	glTranslatef(270, ysq2pos, 0.);
	DrawPlayer();
}


void Update() {
	Player_IZQ();
	glPopMatrix();
	glPushMatrix();
	Player_DER();
	glLoadIdentity();
	glPushMatrix();
	ball();
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
	gluOrtho2D(0.0, 640 / 2, 0.0, 480 / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void init(void) {
	//set the clear color to be white
	glClearColor(1, 1, 1, 1.0);

	xpos = 160.;      xdir = 1.;
	ypos = 160.;      ydir = 1.;
	ysqpos = 0.; ysqdir = 0.;
	ysq2pos = 0.; ysq2dir = 0.;
	cout << "P1: " << p1 << "        " << "P2: " << p2 << endl;

	
}


void main(int argc, char* argv[])
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Pong");
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}