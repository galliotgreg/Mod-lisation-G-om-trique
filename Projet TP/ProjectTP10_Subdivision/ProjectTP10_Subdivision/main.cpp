/*
 *	Tableau des points permettant de gérer les points de controles
 * On sélectionne le point en se déplaçant avec + et -, ...
 * On sélectionne ensuite si on veut faire monter, descendre amener vers la gauche ou la droite le point.
 *   d : translation à droite
 *   q : à gauche
 *   z : en haut
 *   s : en bas

	 c : chaikin subdivision
 *   
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <vector> 
#include "GL/glut.h"
#include "struct.h"

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ESC 27

float tx=0.0;
float ty=0.0;

// Tableau des points de contrôles en global ...
point3 TabPC[10];
int Ordre = 10;
int numPoint = 0;

vector<point3> chaikinVecInit;
vector<vector<point3>> chaikinVecVec;

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	// Initialisation des points de contrôles
	// On choisit de les intialiser selon une ligne
	//for (int i = 0; i < Ordre; i++)
	//{
     //TabPC[i] = point3(i,i,i);
    //}
	chaikinVecInit.push_back(point3(-20, -20, 0));
	chaikinVecInit.push_back(point3(-10, 10, 0));
	chaikinVecInit.push_back(point3(10, 10, 0));
	chaikinVecInit.push_back(point3(20, 10, 0));
	chaikinVecInit.push_back(point3(30, 20, 0));
	chaikinVecInit.push_back(point3(50, 30, 0));
	chaikinVecInit.push_back(point3(60, -20, 0));
	chaikinVecInit.push_back(point3(-20, -20, 0));

	chaikinVecVec.push_back(chaikinVecInit);
}

void chaikin() {

	cout << "chaikin" << endl;

	std::vector<point3> chaikinVecRes;
	
	std::vector<point3> chaikinVec = chaikinVecVec.at((int)chaikinVecVec.size()-1);

	for (int i = 0; i < (int)chaikinVec.size(); i++) {				
		point3 p1 = chaikinVec.at(i);
		point3 p2 = chaikinVec.at(1);

		if(i!=(chaikinVec.size()-1))
			p2 = chaikinVec.at(i+1);

		cout << "************************************" << endl;
		cout << p1 << endl;
		cout << p2 << endl;
		cout << "************************************" << endl;

		
		point3 pointSub1 = point3((float) ((3 / 4.0) * p1.x + (1 / 4.0) * p2.x), (float) ((3 / 4.0) * p1.y + (1 / 4.0) * p2.y), (float) ((3 / 4.0) * p1.z + (1 / 4.0) * p2.z));
		point3 pointSub2 = point3((float)((1 / 4.0) * p1.x + (3 / 4.0) * p2.x), (float)((1 / 4.0) * p1.y + (3 / 4.0) * p2.y), (float)((1 / 4.0) * p1.z + (3 / 4.0) * p2.z));

		chaikinVecRes.push_back(pointSub1);
		chaikinVecRes.push_back(pointSub2);
	}
	chaikinVecVec.push_back(chaikinVecRes);
}

/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float r = 0.0, g = 0.0, b = 0.0;

	//glTranslatef(tx,ty,0.0);
	
	for (int i = 0; i < (int)chaikinVecVec.size(); i++) {
		std::vector<point3> chaikinVecTmp = chaikinVecVec.at(i);

		if (i % 3 == 0) {
			r = 1.0;
			g = 0.0;
			b = 0.0;
		}
		else if (i % 3 == 1) {
			r = 0.0;
			g = 1.0;
			b = 0.0;
		}
		else if (i % 3 == 2) {
			r = 0.0;
			g = 0.0;
			b = 1.0;
		}

		glColor3f(r, g, b);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < (int)chaikinVecTmp.size(); i++) {
			point3 point = chaikinVecTmp.at(i);
			glVertex3f(point.x, point.y, point.z);
		}
		glEnd();
	}	
	glFlush();
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-60, 60, -60, 60, -60, 60);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case '+':
		if (numPoint < Ordre-1)
		   numPoint = numPoint + 1;
        else
            numPoint = 0;
		tx=0;
		ty=0;
		break;
   case '-':
		if (numPoint > 0) 
		   numPoint = numPoint - 1;
        else
            numPoint = Ordre-1;
		tx=0;
		ty=0;
		break;

   case 'd':
         tx=0.1;
		 ty=0;
      break;
   case 'q':
         tx=-0.1;
		 ty=0;
      break;
   case 'z':
         ty=0.1;
		 tx=0;
      break;
   case 's':
         ty=-0.1;
		 tx=0;
      break;
   case 'c':	   
	   chaikin();
	   break;
   case ESC:
      exit(0);
      break;
   default :
	   tx=0;
	   ty=0;
   }
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInitWindowSize(800, 800);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow("Subdivision");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
