#include <GL/glut.h>
#include <math.h>
#include "enumObjects.h"

#define P0	0.45,	0.0,	0.65
#define P1	-0.45,	0.0,	0.65
#define P2	-0.45,	0.0,	-0.65
#define P3	0.45,	0.0,	-0.65
#define P4	0.5,	0.2,	0.75
#define P5	-0.5,	0.2,	0.75
#define P6	-0.5,	0.2,	-0.75
#define P7	0.5,	0.2,	-0.75
#define P8	0.0,	0.2,	-0.75

#define PI	3.14159265358979

extern nVertices[];

void generateVertices (GLfloat *verticesLines, GLfloat *verticesTankFace, GLfloat *verticesTankLines, GLfloat *verticesTankTriangle) {
	int i;
	for (i= 0; i < 21; i++) {
		verticesLines[3*(2*i) + 0] = -10.0 + 1.0*i;
		verticesLines[3*(2*i) + 1] = 0.0;
		verticesLines[3*(2*i) + 2] = 10.0;
		verticesLines[3*(2*i+1) + 0] = -10.0 +  1.0*i;
		verticesLines[3*(2*i+1) + 1] = 0.0;
		verticesLines[3*(2*i+1) + 2] = -10.0;

		verticesLines[126 + 3*(2*i) + 0] = -10.0;
		verticesLines[126 + 3*(2*i) + 1] = 0.0;
		verticesLines[126 + 3*(2*i) + 2] = -10.0 +  1.0*i;
		verticesLines[126 + 3*(2*i+1) + 0] = 10.0;
		verticesLines[126 + 3*(2*i+1) + 1] = 0.0;
		verticesLines[126 + 3*(2*i+1) + 2] = -10.0 +  1.0*i;
	}

	GLfloat _verticesTankFace [] = {
#include "tank.txt"
};
	GLfloat _verticesTankLines [] = {P0, P1, P2, P3, P4, P5, P6, P7, P0, P3, P1, P2, P4, P7, P5, P6, P0, P4, P1, P5, P2, P6, P3, P7};
	GLfloat _verticesTankTriangle [] = {P4, P5, P8};
	for (i=0; i<3*nVertices[tankFace]; i++) verticesTankFace[i] = _verticesTankFace[i];
	for (i=0; i<3*nVertices[tankLines]; i++) verticesTankLines[i] = _verticesTankLines[i];
	for (i=0; i<3*nVertices[tankTriangle]; i++) verticesTankTriangle[i] = _verticesTankTriangle[i];
	
	return;
}

