#include "matrix.h"
#include <math.h>
#include <GL/glut.h>


void matrixID (GLfloat *rop) {
	int i, j;
	for (i=0; i<4; i++) for (j=0; j<4; j++)
		rop[4*i+j] = (i==j)? 1.0 : 0.0;

	return;
}

void matrixMul (GLfloat *rop, GLfloat *op1, GLfloat *op2) {
	GLfloat aux[16];
	int i, j, k;
	for (j=0; j<4; j++) for (i=0; i<4; i++) {
		aux[4*j+i] = 0.0;
		for (k=0; k<4; k++)
			aux[4*j+i] += op1[4*k+i] * op2[4*j+k];
	}
	for (i=0; i<16; i++) rop[i] = aux[i];
	return;
}

void rotateX(GLfloat *matrix, GLfloat phi) {
	GLfloat rot[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, cos(phi), sin(phi), 0.0,
				0.0, -sin(phi), cos(phi), 0.0,
				0.0, 0.0, 0.0, 1.0};
	matrixMul (matrix, rot, matrix);
	return;
}

void rotateY(GLfloat *matrix, GLfloat phi) {
	GLfloat rot[] = {	cos(phi), 0.0, sin(phi), 0.0,
				0.0, 1.0, 0.0, 0.0,
				-sin(phi), 0.0, cos(phi), 0.0,
				0.0, 0.0, 0.0, 1.0};

	matrixMul (matrix, rot, matrix);
	return;
}

void rotateZ(GLfloat *matrix, GLfloat phi) {
	GLfloat rot[16] = {	cos(phi), sin(phi), 0.0, 0.0,
				-sin(phi), cos(phi), 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0};
	matrixMul (matrix, rot, matrix);
	return;
}

void translate (GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z) {
	GLfloat trans[16] = {	1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				  x,   y,   z, 1.0};
	matrixMul (matrix, trans, matrix);
	return;
}

void scale (GLfloat *matrix, GLfloat s) {
	GLfloat scale[16] = {	s, 0.0, 0.0, 0.0,
				0.0, s, 0.0, 0.0,
				0.0, 0.0, s, 0.0,
				0.0, 0.0, 0.0, 1.0};
	matrixMul (matrix, scale, matrix);
}

void frustum (GLfloat *matrix, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
	GLfloat width = (right - left) / 2.0;
		width = (width > 0)? -width : width;
	GLfloat height = (top - bottom) / 2.0;
		height = (height > 0)? -height : height;

	GLfloat frustum[16] = {	near*2.0/width, 0.0, 0.0, 0.0,
				0.0, near*2.0/height, 0.0, 0.0,
				0.0, 0.0, -(far + near) / (far - near), -1.0,
				0.0, 0.0, 2.0*far*near/(far - near), 0.0};

	matrixMul (matrix, frustum, matrix);
}


