#include <GL/glut.h>
#include "vertices.h"
#include "enumObjects.h"

#define R	0.8
#define H	1.5

// VERTEX ARRAY OBJECTS
extern GLuint program[];
extern GLuint vao[];

extern GLuint nVertices[];

// BUFFERS
extern GLuint buffer[];


void loadData () {
	int i, j;

	GLfloat verticesLines[3*nVertices[floorLines]];
	GLfloat verticesTankFace[3*nVertices[tankFace]];
	GLfloat verticesTankLines[3*nVertices[tankLines]];

	generateVertices (verticesLines, verticesTankFace, verticesTankLines);


	glBindVertexArray (vao[floorLines]);
	glBindBuffer (GL_ARRAY_BUFFER, buffer[floorLines]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (verticesLines), verticesLines, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
	glEnableVertexAttribArray (0);


	glBindVertexArray (vao[tankFace]);
	glBindBuffer (GL_ARRAY_BUFFER, buffer[tankFace]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (verticesTankFace), verticesTankFace, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
	glEnableVertexAttribArray (0);


	glBindVertexArray (vao[tankLines]);
	glBindBuffer (GL_ARRAY_BUFFER, buffer[tankLines]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (verticesTankLines), verticesTankLines, GL_STATIC_DRAW);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
	glEnableVertexAttribArray (0);

	return;
}
