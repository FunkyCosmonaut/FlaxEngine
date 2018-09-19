
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include "physics.h"

#define OY1  -2
#define OY2   1

struct object square; //initialize square
struct object square = {.5, .5, 0, 0, {-1,1,-2, 1}};
float ground = -3;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);
	glPushMatrix();
	//	glRotatef(angle, 0.0f, 1.0f, 0.0f);

		square.out.xpos1 += square.xvec;
		square.out.xpos2 += square.xvec;
		square.out.ypos1 += square.yvec;
		square.out.ypos2 += square.yvec;
//++++++++++++++++++++++++MOMENTUM FUNCTIONS
		if(square.out.ypos1 <= ground ){	
			square.yvec = 0;
			square.out.ypos1 = ground;
			square.out.ypos2 = OY2;

		}
		else{
			square.yvec += sin(-0.091);
		}


		glTranslatef(square.xvec,square.yvec, 0.0);

		glBegin(GL_QUADS);
			glColor3d(1,0,0);
	        	glVertex3f(square.out.xpos1,square.out.ypos1,-10);
	        	glColor3d(1,1,0);
	        	glVertex3f(square.out.xpos2,square.out.ypos1,-10);
			glColor3d(1,1,1);
	        	glVertex3f(square.out.xpos2,square.out.ypos2,-10);
	        	glColor3d(0,1,1);
	        	glVertex3f(square.out.xpos1,square.out.ypos2,-10);
		glEnd();
	glPopMatrix();

	glBegin(GL_QUADS);
		glBegin(GL_QUADS);
                glColor3d(1,0,0);
		glVertex3f(-100,-4,-10);
		glColor3d(1,1,0);
		glVertex3f(100,-4,-10);
		glColor3d(1,1,1);
		glVertex3f(100,-3,-10);
		glColor3d(0,1,1);
		glVertex3f(-100,-3,-10);
	glEnd();

	angle+=0.9f;

	glutSwapBuffers();
}
void keyboard(int key, int x, int y)
{

	switch(key){
		case GLUT_KEY_LEFT:
			square.xvec -= 0.1;
			break;
		case GLUT_KEY_RIGHT:
			square.xvec += 0.1;
			break;
		case GLUT_KEY_UP:
			square.yvec += 1.4;
			break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("TESTING");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutSpecialFunc(keyboard);

	// enter GLUT event processing cycle
	glutMainLoop();
	printf("%f\n", 3.0);

	return 1;
}
