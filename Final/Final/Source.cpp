#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h>

#include "Shapes.h"
#include "snowman.h"
#include "bmp.h"
#include "vrml.h"

#define MAXSHAPES 25
#define MAXCOORDS  3000
#define XMIN -0.6
#define XMAX 0.6
#define YMIN -.6
#define YMAX .6

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_Q 0x51
#define VK_E 0x45
#define VK_LBUTTON	0x01
#define VK_RBUTTON	0x02

//snowman
//GLfloat spin = 0;
boolean     USERCANCEL, FIRSTTIME;


BITMAPINFO *bginfo;       // Background Bitmap information 
GLubyte    *bgpixels;     // Actual background pixel data 

GLfloat sXforms[9] = { 0.,0.,0.,0.,45.,0.,1.,1.,1. };
GLfloat allXforms[9] = { 0.,0.,0.,0.,0.,0.,1.,1.,1. };
//

GLfloat   coords[MAXSHAPES][3 * MAXCOORDS];
GLint     indices[MAXSHAPES][3 * MAXCOORDS];
GLfloat   normals[MAXSHAPES][3 * MAXCOORDS];
GLint     nindices[MAXSHAPES][3 * MAXCOORDS];
GLint     noofpoly[MAXSHAPES];
GLint     noofshapes;
GLfloat xdir;
GLfloat ydir;
GLfloat ang, eyeX, eyeZ, eyeY, centerX, centerY, centerZ;
GLfloat RED = 1., BLUE = 1., GREEN = 1.;
GLfloat lightPos;

//camera
GLfloat eyez = 5., zmove = 1;

GLfloat eyZ = 5., eyX = 5.;

GLfloat camAng = 0.;
GLfloat camRotSpeed = 0.001;

GLfloat fang = 60.;
GLfloat lens = 3.;

GLfloat aspect;

GLubyte* bits1, *bits2, *bits3, *bits4, *bits5, *bits6;
BITMAPINFO* info1, *info2, *info3, *info4, *info5, *info6;
static GLuint texName[6];

void processKeys()
{
	if (GetAsyncKeyState(VK_RIGHT)) {
		//xdir = xdir + 0.2;
		eyX = 0 /*centerX*/ + 1 /*radius*/ * cos(camAng);
		eyZ = 0 /*centerZ*/ + 1 /*radius*/ * sin(camAng);

	}
	if (GetAsyncKeyState(VK_LEFT)) {
		//xdir = xdir - 0.2;
		eyX = 0 /*centerX*/ + 1 /*radius*/ * cos(-camAng);
		eyZ = 0 /*centerZ*/ + 1 /*radius*/ * sin(-camAng);
	}
	if (GetAsyncKeyState(VK_LBUTTON)) {
		lightPos = lightPos - .1
	}
	if (GetAsyncKeyState(VK_RBUTTON)) {
		lightPos = lightPos + .1
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		centerZ = centerZ - 0.01;
	}
	if (GetAsyncKeyState(VK_UP)) {
		centerZ = centerZ + 0.01;
	}
	if ((GetAsyncKeyState(VK_W)))
	{
		RED = RED + 0.1;
	}
	if ((GetAsyncKeyState(VK_S)))
	{
		RED = RED - 0.1;
	}

	if ((GetAsyncKeyState(VK_A)))
	{
		GREEN = GREEN + 0.1;
	}
	if ((GetAsyncKeyState(VK_D)))
	{
		GREEN = GREEN - 0.1;
	}

	if ((GetAsyncKeyState(VK_Q)))
	{
		BLUE = BLUE + 0.1;
	}
	if ((GetAsyncKeyState(VK_E)))
	{
		BLUE = BLUE - 0.1;
	}
}


void Display(void)
{
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	processKeys();
	// camera
	//glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	//GLfloat eyeX = (centerX * cos(ang));
	//GLfloat eyeZ = (centerY * sin(ang));
	//KeyBoard();
	//Keyboard(eyeX, eyeY, eyeZ);

	//gluPerspective(fang, aspect, 1., 20.0);
	//glMatrixMode(GL_MODELVIEW);
	
	if (camAng >= 360) camAng = 0; else camAng += camRotSpeed;
	//if (centerZ > 1.) centerZ = 1.;

	gluLookAt(eyX, centerZ, eyZ, 0., 0., 1., 0., 1., 0.);
	//gluLookAt(0, 0., -1., 0, -1, 0, 0., 1., 0.);

	//glRotatef(xdir, 0.0, 1.0, 0.0);
	//if (ang >= 360) ang = 0; else ang++;
	TexCube(20., 20., 20.);
	draw_SnowMan(sXforms, allXforms, allXforms, allXforms, allXforms, allXforms, allXforms, allXforms, allXforms);
	//glTranslatef(1., 1., 1.);

	GLfloat light_position[] = { lightPos, 0.0, 1.0, 0.0 };
	GLfloat light_ambient[] = { RED, GREEN, BLUE, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glFlush();

	glutPostRedisplay();
	
	
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadIdentity();
	glFrustum(-0.3 * (GLfloat)w / h, 0.3 * (GLfloat)w / h, -0.3, 0.3, 1., 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void SetTexParams() {

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
}


void init(void)
{

	glClearColor(1, 1, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(6, texName);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	SetTexParams();
	bits1 = ReadBitmap("top.bmp", &info1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info1->bmiHeader.biWidth,
		info1->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		bits1);


	glBindTexture(GL_TEXTURE_2D, texName[1]);
	SetTexParams();
	bits2 = ReadBitmap("bottom.bmp", &info2);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info2->bmiHeader.biWidth,
		info2->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		bits2);

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	SetTexParams();
	bits3 = ReadBitmap("front.bmp", &info3);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info3->bmiHeader.biWidth,
		info3->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		bits3);

	glBindTexture(GL_TEXTURE_2D, texName[3]);
	SetTexParams();
	bits4 = ReadBitmap("back.bmp", &info4);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info4->bmiHeader.biWidth,
		info4->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		bits4);

	glBindTexture(GL_TEXTURE_2D, texName[4]);
	SetTexParams();
	bits5 = ReadBitmap("right.bmp", &info5);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info5->bmiHeader.biWidth,
		info5->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		bits5);

	glBindTexture(GL_TEXTURE_2D, texName[5]);
	SetTexParams();
	bits6 = ReadBitmap("left.bmp", &info6);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info6->bmiHeader.biWidth,
		info6->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
		bits6);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	setTextures(texName);

	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
	GLfloat light_ambient[] = { RED, GREEN, BLUE, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position1[] = { 0.0, 1.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glEnable(GL_LIGHT1);
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
	GLfloat gray[] = { 0.8,0.8,0.5,1. };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);


	glShadeModel(GL_SMOOTH);
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	//noofshapes = ReadVRML("vase.wrl", &coords[0][0], &normals[0][0], &indices[0][0], &nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);
}

void main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(320, 200);
	glutCreateWindow("Planar Texture Mapping");
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
