#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "LoadShaders.h"
#include "matrix.h"
#include "vertices.h"
#include "enumObjects.h"

#define WIDTH 	1600
#define HEIGHT 	1200
#define FPS	100
#define PI	3.14159265358979
#define R	0.8
#define H	1.5

#define SIGN(a)	(((a)>0)? 1.0 : (((a)<0)? -1.0: 0))
#define MIN(a,b) (((a)<(b))? (a) : (b))
#define MAX(a,b) (((a)>(b))? (a) : (b))


// VERTEX ARRAY OBJECTS
GLuint program[nPrograms];
GLuint vao[nVao];

GLuint nVertices[] = {84, 14, 24,3};

// BUFFERS
GLuint buffer[nVao];


// UNIFORM DATA
GLfloat modelMatrix[16];
GLfloat viewMatrix[16];
GLfloat projectionMatrix[16];
GLfloat greenColor[] = {0.19922, 0.48438, 0.18359, 1.0};
GLfloat blackColor[] = {0.0, 0.0, 0.0, 1.0};
GLfloat darkGreenColor[] = {0.04922, 0.30438, 0.03359, 1.0};



static int notInit = 0;

GLfloat viewPhi = PI/12.0;

GLfloat tankPhi = PI/6.0;
GLfloat x = 0.0;
GLfloat y = 0.0;
GLfloat z = 0.0;
enum {reverse=-1, neutral=0, drive=1};
enum {brake, throttle, none};
GLint gear = neutral;
GLuint pedal = none;
GLfloat v = 0.0;

void init () {

	glGenVertexArrays (nVao, vao);
	glGenBuffers (nVao, buffer);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "line.vs.glsl"},
		{GL_FRAGMENT_SHADER, "line.fs.glsl"},
		{GL_NONE, NULL},		
		{GL_VERTEX_SHADER, "tank.vs.glsl"},
		{GL_FRAGMENT_SHADER, "tank.fs.glsl"},
		{GL_NONE, NULL}};

	program[floorProgram] = LoadShaders (shaders);
	program[tankProgram] = LoadShaders (&shaders[3]);
	loadData ();
}

void display () {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);

	// GLOBAL VIEW
	matrixID (viewMatrix);
	matrixID (projectionMatrix);
	translate (viewMatrix, -x, 0.0, -z);
	rotateY (viewMatrix, viewPhi);
	rotateX (viewMatrix, PI/8.0);
	translate (viewMatrix, 0.0, 0.0, -15.0);
	frustum (projectionMatrix, -1.5, 1.5, -1.0, 1.0, -1.0, -50.0);


	// MODEL TRANSFORMS FOR LINES
	matrixID (modelMatrix);
	glUseProgram (program[floorProgram]);
	glUniformMatrix4fv (glGetUniformLocation (program[floorProgram], "model"), 
			1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv (glGetUniformLocation (program[floorProgram], "view"), 
			1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv (glGetUniformLocation (program[floorProgram], "projection"), 
			1, GL_FALSE, projectionMatrix);
	// DRAW FLOOR LINES
	glBindVertexArray (vao[floorLines]);
	glDrawArrays (GL_LINES, 0, nVertices[floorLines]);



	// MODEL TRANSFORMS FOR TANK FACES
	matrixID (modelMatrix);
	rotateY (modelMatrix, tankPhi);
	translate (modelMatrix, x, y, z);

	glUseProgram (program[tankProgram]);
	glUniformMatrix4fv (glGetUniformLocation (program[tankProgram], "model"), 
			1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv (glGetUniformLocation (program[tankProgram], "view"), 
			1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv (glGetUniformLocation (program[tankProgram], "projection"), 
			1, GL_FALSE, projectionMatrix);

	glUniform4fv (glGetUniformLocation (program[tankProgram], "vColor"), 1, greenColor);
	// DRAW TANK FACES
	glBindVertexArray (vao[tankFace]);
	glDrawArrays (GL_TRIANGLE_STRIP, 0, nVertices[tankFace]);



	// MODEL TRANSFORMS FOR TANK LINES
	matrixID (modelMatrix);
	scale (modelMatrix, 1.01);
	rotateY (modelMatrix, tankPhi);
	translate (modelMatrix, x, y, z);

	glUniformMatrix4fv (glGetUniformLocation (program[tankProgram], "model"), 
			1, GL_FALSE, modelMatrix);

	glUniform4fv (glGetUniformLocation (program[tankProgram], "vColor"), 1, blackColor);
	// DRAW TANK FACES
	glBindVertexArray (vao[tankLines]);
	glDrawArrays (GL_LINES, 0, nVertices[tankLines]);



	// MODEL TRANSFORMS FOR TANK TRIANGLE
	matrixID (modelMatrix);
	scale (modelMatrix, 1.02);
	rotateY (modelMatrix, tankPhi);
	translate (modelMatrix, x, y, z);

	glUniformMatrix4fv (glGetUniformLocation (program[tankProgram], "model"), 
			1, GL_FALSE, modelMatrix);

	glUniform4fv (glGetUniformLocation (program[tankProgram], "vColor"), 1, darkGreenColor);
	// DRAW TANK FACES
	glBindVertexArray (vao[tankTriangle]);
	glDrawArrays (GL_TRIANGLES, 0, nVertices[tankTriangle]);


	glFlush ();
}


void timer (int i) {
	GLuint udelay = 1000 / FPS;
	GLfloat delay = udelay / 1000.0;
	x += v*sin (tankPhi)*delay;
	z -= v*cos (tankPhi)*delay;
	GLfloat a;
	switch (pedal) {
		case brake: 	a = SIGN (-v)*10.0;
				break;
		case throttle:	a = 2.0*gear - 0.5*v;
				break;
		case none:	a = -1.0*v;
				if (a>0) a = MAX (a, 0.05);
				if (a<0) a = MIN (a, -0.05);
				break;
	}
	GLfloat oldV = v;
	v += a*delay;
	if (oldV*v < 0.0) v = 0.0;

	glutTimerFunc (udelay, timer, 0);
	glutPostRedisplay ();
}


void mouseMotion(int x, int y) {
	static int xOld;
	static int yOld;
	if(notInit) {
		viewPhi -= ((float) (x - xOld))/400.0;
		xOld = x;
		yOld = y;
	} else {
		xOld = x;
		yOld = y;
		notInit = 1;
	} /* end if/else */
} 

void mouse (int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		notInit = 0;
	}
}




void arrowKey (int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: if (v<0.0) tankPhi += 0.05;
				else tankPhi -= 0.05;
				break;
		case GLUT_KEY_RIGHT: if (v<0.0) tankPhi -= 0.05;
				else tankPhi += 0.05;
				break;
		case GLUT_KEY_UP: pedal = throttle;
				break;
		case GLUT_KEY_DOWN: pedal = brake;
				break;
	}
}

void upArrowKey (int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: pedal = none;
				break;
		case GLUT_KEY_DOWN: pedal = none;
				break;
	}
}

void key(unsigned char key, int x, int y) {
	if (key == 27) exit (0);
	switch (key) {
		case '+': 
		case 'a':
			gear++;
			gear = MIN (gear, 1);
			break;
		case '-':
		case 'z':
			gear--;
			gear = MAX (gear, -1);
			break;
	}
	printf ("gear = %i\n", gear);

}

void main (int argc, char** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitContextVersion (3, 1);
	glutCreateWindow ("tank");

	glewInit ();
	init ();

	glutKeyboardFunc (key);
	glutMotionFunc (mouseMotion);
	glutMouseFunc (mouse);
	glutSpecialFunc (arrowKey);
	glutSpecialUpFunc (upArrowKey);

	glutDisplayFunc (display);

	glutTimerFunc (0, timer, 0); 
	glutMainLoop ();

}

