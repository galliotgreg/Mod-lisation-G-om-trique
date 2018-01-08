
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "GL/glut.h"
#include "struct.h"
#include <vector>

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

float angleX = 0.0f; //angle de rotation en Y de la scene
float angleY = 0.0f; //angle de rotation en X de la scene

float pasDeplacement = 1.25;


//position lumiere
float xLitePos = 0;
float yLitePos = 10;
float zLitePos = -100;

float tx = 0.0;
float ty = 0.0;
float tz = 0.0;

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Si vous avez des choses � initialiser, c est ici.  
	glEnable(GL_DEPTH_TEST);
}


bool pointAppartientSphere(point3 p, point3 centreSphere, int rayon) {
	return ((p.x - centreSphere.x) * (p.x - centreSphere.x) + (p.y - centreSphere.y) * (p.y - centreSphere.y) + (p.z - centreSphere.z) * (p.z - centreSphere.z) <= rayon);
}

void render_scene()
{
	point3 centreSphere = point3(0.0, 0.0, 0.0);
	int rayon = 150;

	//c'est ici qu'on dessine

	point3 A = point3(0, 0, 0);
	point3 B = point3(0, 0, 1);
	point3 C = point3(0, 1, 0);
	point3 D = point3(0, 1, 1);
	point3 E = point3(1, 0, 0);
	point3 F = point3(1, 0, 1);
	point3 G = point3(1, 1, 0);
	point3 H = point3(1, 1, 1);

	glColor3f(0.0, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(C.x, C.y, C.z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glColor3f(0.5, 0.0, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex3f(D.x, D.y, D.z);
	glVertex3f(H.x, H.y, H.z);
	glVertex3f(G.x, G.y, G.z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(G.x, G.y, G.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	glColor3f(0.5, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(E.x, E.y, E.z);
	glVertex3f(F.x, F.y, F.z);
	glVertex3f(G.x, G.y, G.z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(F.x, F.y, F.z);
	glVertex3f(G.x, G.y, G.z);
	glVertex3f(H.x, H.y, H.z);
	glEnd();

	glColor3f(0.5, 0.25, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(G.x, G.y, G.z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(E.x, E.y, E.z);
	glVertex3f(G.x, G.y, G.z);
	glEnd();

	glColor3f(0.25, 0.5, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex3f(D.x, D.y, D.z);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(F.x, F.y, F.z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(D.x, D.y, D.z);
	glVertex3f(F.x, F.y, F.z);
	glVertex3f(H.x, H.y, H.z);
	glEnd();

	glColor3f(0.25, 0.25, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(E.x, E.y, E.z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(E.x, E.y, E.z);
	glVertex3f(F.x, F.y, F.z);
	glEnd();


	//Left
	//ABCD
	point3 TabLeft[5];
	TabLeft[0] = A;
	TabLeft[1] = B;
	TabLeft[2] = D;
	TabLeft[3] = C;
	TabLeft[4] = A;

	//Right
	//EFGH
	point3 TabRight[5];
	TabRight[0] = E;
	TabRight[1] = F;
	TabRight[2] = H;
	TabRight[3] = G;
	TabRight[4] = E;


	//Top
	//CDGH
	point3 TabTop[5];
	TabTop[0] = C;
	TabTop[1] = D;
	TabTop[2] = H;
	TabTop[3] = G;
	TabTop[4] = C;

	//Down
	//ABEF
	point3 TabDown[5];
	TabDown[0] = A;
	TabDown[1] = B;
	TabDown[2] = F;
	TabDown[3] = E;
	TabDown[4] = A;

	glBegin(GL_LINE_STRIP);
	for (point3 point : TabLeft) {
		//ABCD
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (point3 point : TabRight) {
		//EFGH
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (point3 point : TabTop) {
		//CDGH
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (point3 point : TabDown) {
		//ABEF
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();

	//Draw the grid	
	glColor3f(0.25, 0.25, 0.25);
	for (int i = -100; i < 100; i++) {
		for (int j = -100; j < 100; j++) {
			for (int k = -100; k < 100; k++) {
				if (pointAppartientSphere(point3(i, j, k), centreSphere, rayon)) {
					glColor3f(0.25, 0.25, 0.0);
					glBegin(GL_LINE_STRIP);
					for (point3 point : TabLeft) {
						//ABCD
						glVertex3f(i + point.x, j + point.y, k + point.z);
					}
					glEnd();
					glColor3f(0.0, 0.25, 0.25);
					glBegin(GL_LINE_STRIP);
					for (point3 point : TabRight) {
						//EFGH
						glVertex3f(i + point.x, j + point.y, k + point.z);
					}
					glEnd();
					glColor3f(0.25, 0.0, 0.25);
					glBegin(GL_LINE_STRIP);
					for (point3 point : TabTop) {
						//CDGH
						glVertex3f(i + point.x, j + point.y, k + point.z);
					}
					glEnd();
					glColor3f(0.25, 0.25, 0.25);
					glBegin(GL_LINE_STRIP);
					for (point3 point : TabDown) {
						//ABEF
						glVertex3f(i + point.x, j + point.y, k + point.z);
					}
					glEnd();
				}
			}
		}
	}
}

/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-angleY, 0.0f, 0.0f, 1.0f);
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glTranslatef(tx, ty, tz);

	glRotatef(-angleY, 0.0f, 0.0f, 1.0f);
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);

	render_scene();
	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	glColor3f(0.8, 0.8, 0.8);

	glPopMatrix();

	//affiche les axes du repere
	glColor3f(0.0, 1.0, 0.0); //Y vert
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0); //Z bleu
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); //X rouge
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);
	glEnd();

	glutSwapBuffers();// echange des buffers
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid gestionSouris(int x, int y)
{
	angleX = x * 720 / WIDTH; //gere l'axe Oy
	angleY = -(y * 180 / HEIGHT - 90) * 4; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		tz += int(pasDeplacement); glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		tz -= int(pasDeplacement); glutPostRedisplay();
		break;
		glutPostRedisplay();
	}

}

GLvoid window_key_down(unsigned char key, int x, int y)  //appuie des touches
{
	switch (key)
	{

		//deplacement de la camera
	case 'z':
		ty += int(pasDeplacement); glutPostRedisplay();
		break;

	case 's':
		ty -= int(pasDeplacement); glutPostRedisplay();
		break;

	case 'q':
		tx -= int(pasDeplacement); glutPostRedisplay();
		break;

	case 'd':
		tx += int(pasDeplacement); glutPostRedisplay();
		break;

		//sortie
	case KEY_ESC:
		exit(0);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInitWindowSize(400, 400);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Volumes param�triques");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(&window_key_down);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(gestionSouris);
	glutSpecialFunc(&gestionFleche);
	glutMainLoop();
	return 0;
}