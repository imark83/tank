#ifndef __MATRIX_H_
#define __MATRIX_H_

#include "matrix.h"
#include <GL/glut.h>

void matrixID	(GLfloat *rop);
void matrixMul	(GLfloat *rop, GLfloat *op1, GLfloat *op2);
void rotateX	(GLfloat *matrix, GLfloat phi);
void rotateY	(GLfloat *matrix, GLfloat phi);
void rotateZ	(GLfloat *matrix, GLfloat phi);
void translate	(GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z);

void scale	(GLfloat *matrix, GLfloat s);
void frustum (GLfloat *matrix, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
#endif
