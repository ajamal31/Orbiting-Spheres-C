#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <math.h>

// Handles different screen sizes.
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

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

// Global Variables used to store x and y values of the spheres.
float bigAngle = 0.0f;
float xBig = 3.0f;
float yBig = 0.0f;

float smallAngle = 0.0f;
float xSmall = -2.0f;
float ySmall = 0.0f;

// Renders scene
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	// Draw the big sphere, set colour to red and translate it.
	glPushMatrix();
	glTranslatef(xBig, yBig, 0); 
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.7, 100, 100);
	glEnd();
	glPopMatrix();

	// Draw the small sphere, set colour to green and translate it.
	glPushMatrix();
	glTranslatef(xSmall, ySmall, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(0, 1, 0);
	glutSolidSphere(0.3, 100, 100);
	glEnd();
	glPopMatrix();

	// Calculate the x and y values of the spheres.
	xBig = 1.0 * cosf(bigAngle);
	yBig = 1.0 * sinf(bigAngle);
	xSmall = 3.0 * cosf(smallAngle);
	ySmall = 3.0 * sinf(smallAngle);
	bigAngle += 0.001f;
	smallAngle -= 0.003f;

	glutSwapBuffers();
}

// Runs the main graphics program.
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Orbiting Spheres");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}