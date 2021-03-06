#include <math.h>
#include "snowman.h"

GLfloat mat_ambient[] = { 0.1, 0.1, 0.2, 1.0 };
GLfloat snow_diffuse[] = { 0.8,0.8,0.8,1. };
GLfloat eye_diffuse[] = { 0.0,0.0,0.0,1. };
GLfloat nose_diffuse[] = { 0.9,0.5,0.0,1. };
GLfloat hand_diffuse[] = { 0.5,0.3,0.1,1. };

GLfloat mat_emission[] = { 0.5, 0.0, 0.0, 0.0 };
GLfloat no_emission[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat low_shininess[] = { 50. };



void draw_LEye(GLfloat *lXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, eye_diffuse);
	glPushMatrix();
	glTranslatef(lXforms[0], lXforms[1], lXforms[2]);
	glTranslatef(-0.2, 0.1, 0.4);
	glRotatef(lXforms[3], 1, 0, 0);
	glRotatef(lXforms[4], 0, 1, 0);
	glRotatef(lXforms[5], 0, 0, 1);
	glScalef(lXforms[6], lXforms[7], lXforms[8]);

	{
		glutSolidSphere(0.1, 5, 5);
	}
	glPopMatrix();
}

void draw_REye(GLfloat *rXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, eye_diffuse);
	glPushMatrix();
	glTranslatef(rXforms[0], rXforms[1], rXforms[2]);
	glTranslatef(0.2, 0.1, 0.4);
	glRotatef(rXforms[3], 1, 0, 0);
	glRotatef(rXforms[4], 0, 1, 0);
	glRotatef(rXforms[5], 0, 0, 1);
	glScalef(rXforms[6], rXforms[7], rXforms[8]);

	{
		glutSolidSphere(0.1, 5, 5);
	}
	glPopMatrix();
}

void draw_Nose(GLfloat *noseXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, nose_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glPushMatrix();
	glTranslatef(noseXforms[0], noseXforms[1], noseXforms[2]);
	glTranslatef(0., -0.1, 0.4);
	glRotatef(noseXforms[3], 1, 0, 0);
	glRotatef(noseXforms[4], 0, 1, 0);
	glRotatef(noseXforms[5], 0, 0, 1);
	glScalef(noseXforms[6], noseXforms[7], noseXforms[8]);

	{
		glutSolidCone(0.1, 0.7, 5, 5);
	}
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
}

void draw_Head(GLfloat *headXforms, GLfloat *lXforms, GLfloat *rXforms, GLfloat *noseXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, snow_diffuse);
	glPushMatrix();
	glTranslatef(headXforms[0], headXforms[1], headXforms[2]);
	glTranslatef(0., 5.4, 0.);
	glRotatef(headXforms[3], 1, 0, 0);
	glRotatef(headXforms[4], 0, 1, 0);
	glRotatef(headXforms[5], 0, 0, 1);
	glScalef(headXforms[6], headXforms[7], headXforms[8]);

	{
		glutSolidSphere(0.5, 20, 20);

		draw_LEye(lXforms);
		draw_REye(rXforms);
		glColor3f(0.9, 0.5, 0);

		draw_Nose(noseXforms);

	}
	glPopMatrix();
}

void draw_LHand(GLfloat *lHandXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, hand_diffuse);
	glPushMatrix();
	glTranslatef(lHandXforms[0], lHandXforms[1], lHandXforms[2]);
	glTranslatef(-1., 0., 0.);
	glRotatef(lHandXforms[3], 1, 0, 0);
	glRotatef(lHandXforms[4], 0, 1, 0);
	glRotatef(lHandXforms[5], 0, 0, 1);
	glScalef(lHandXforms[6], lHandXforms[7], lHandXforms[8]);
	glRotatef(-90., 0, 1, 0);
	{
		glutSolidCone(0.1, 1.5, 5, 5);
	}
	glPopMatrix();
}

void draw_RHand(GLfloat *rHandXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, hand_diffuse);
	glPushMatrix();
	glTranslatef(rHandXforms[0], rHandXforms[1], rHandXforms[2]);
	glTranslatef(1., 0., 0.);
	glRotatef(rHandXforms[3], 1, 0, 0);
	glRotatef(rHandXforms[4], 0, 1, 0);
	glRotatef(rHandXforms[5], 0, 0, 1);
	glScalef(rHandXforms[6], rHandXforms[7], rHandXforms[8]);
	glRotatef(90., 0, 1, 0);
	{
		glutSolidCone(0.1, 1.5, 5, 5);
	}
	glPopMatrix();
}

void draw_Tummy(GLfloat *tumXforms, GLfloat *lHandXforms, GLfloat *rHandXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, snow_diffuse);
	glPushMatrix();
	glTranslatef(tumXforms[0], tumXforms[1], tumXforms[2]);
	glTranslatef(0., 3.9, 0.);
	glRotatef(tumXforms[3], 1, 0, 0);
	glRotatef(tumXforms[4], 0, 1, 0);
	glRotatef(tumXforms[5], 0, 0, 1);
	glScalef(tumXforms[6], tumXforms[7], tumXforms[8]);

	{
		glutSolidSphere(1, 20, 20);

		draw_LHand(lHandXforms);
		draw_RHand(rHandXforms);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, snow_diffuse);
	}
	glPopMatrix();
}

void draw_Bottom(GLfloat *botXforms) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, snow_diffuse);


	glPushMatrix();
	glTranslatef(botXforms[0], botXforms[1], botXforms[2]);
	glTranslatef(0., 1.5, 0.);
	glRotatef(botXforms[3], 1, 0, 0);
	glRotatef(botXforms[4], 0, 1, 0);
	glRotatef(botXforms[5], 0, 0, 1);
	glScalef(botXforms[6], botXforms[7], botXforms[8]);

	glutSolidSphere(1.5, 20, 20);
	glPopMatrix();
}




void draw_SnowMan(GLfloat *snomanXforms, GLfloat *botXforms, GLfloat *tumXforms, GLfloat *headXforms,
	GLfloat *lXforms, GLfloat *rXforms, GLfloat *noseXforms,
	GLfloat *lHandXforms, GLfloat *rHandXforms) {
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, snow_diffuse);

	glTranslatef(snomanXforms[0], snomanXforms[1], snomanXforms[2]);
	//glRotatef(snomanXforms[3], 1, 0, 0);
	//glRotatef(snomanXforms[4], 0, 1, 0);
	//glRotatef(snomanXforms[5], 0, 0, 1);
	glScalef(snomanXforms[6], snomanXforms[7], snomanXforms[8]);
	{
		draw_Bottom(botXforms);
		draw_Tummy(tumXforms, lHandXforms, rHandXforms);
		draw_Head(headXforms, lXforms, rXforms, noseXforms);
	}
	glPopMatrix();

}