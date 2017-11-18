/*
 *	Tableau des points permettant de gérer les points de controles
 * On sélectionne le point en se déplaçant avec + et -, ...
 * On sélectionne ensuite si on veut faire monter, descendre amener vers la gauche ou la droite le point.
 *   d : translation à droite
 *   q : à gauche
 *   z : en haut
 *   s : en bas
 *   
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "GL/glut.h"
#include "struct.h"

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ESC 27

float tx=-5.0;
float ty=-5.0;

// Tableau des points de contrôles en global ...
point3 TabPC[10];
// Ordre de la courbre  : Ordre
// Degré de la courbe = Ordre - 1
int Ordre = 10;




// Point de controle selectionné
int numPoint = 0;

// Fonction Factorielle
float fact(int n)
{
 // A développer
 return 0;
}

double F1(double u) {
	return 2 * std::pow(u, 3) - 3 * std::pow(u, 2) + 1;
}

float F2(float u) {
	return -2 * std::pow(u, 3) + 3 * std::pow(u, 2);
}

float F3(float u) {
	return std::pow(u, 3) - 2 * std::pow(u, 2) + u;

}
float F4(float u) {
	return std::pow(u, 3) - std::pow(u, 2);
}

// Fonction cubique d'hermite
point3 hermite(point3 P0, point3 P1, point3 V0, point3 V1, double u) {
	
	if (u >= 0 && u <= 1) {
		return P0 * F1(u) + P1 * F2(u) + V0 * F3(u) + V1 * F4(u);
	}
	else {
		cout << "u doit être entre 0 et 1" << endl;
		return point3();
	}
	
}

float Bernstein(int i, int n, float t)
{
 // A developper
 return 0;
}


/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	// Initialisation des points de contrôles
	// On choisit de les intialiser selon une ligne
	for (int i = 0; i < Ordre; i++)
	{
     TabPC[i] = point3(i,i,i);
    }
 
}


/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
   
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	
	//glTranslatef(tx,ty,0.0);

	

	point3 Ptemp;
	point3 P0 = point3(5, 8, 0);
	point3 P1 = point3(10, 9, 0);
	point3 V0 = point3(7, -1, 0);
	point3 V1 = point3(4, -9, 0);
	
	TabPC[numPoint]=TabPC[numPoint]+point3(tx,ty,0);

	//// Enveloppe des points de controles
	//glColor3f (1.0, 0.0, 0.0);
	//glBegin(GL_LINE_STRIP);
 //       for (int i =0; i < Ordre; i++)
 //       {
	//	 glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
 //       }
 //   glEnd();

	double u = 0.0;

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex3f(P0.x, P0.y, P0.z);
		glVertex3f(P1.x, P1.y, P1.z);
		glVertex3f(V0.x, V0.y, V0.z);
		glVertex3f(V1.x, V1.y, V1.z);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < Ordre; i++) 
		{
			point3 temp = hermite(P0, P1, V0, V1, u);
			glVertex3f(temp.x, temp.y, temp.z);
			u += 0.1;
		}
		glEnd();


	

	// Affichage du point de controle courant
	// On se déplace ensuite avec + et - 
    // ° d'un point de contrôle au suivant (+)
    // ° d'un point de contrôle au précédent (-)
	glColor3f (0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
		glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
		glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
		glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
	glEnd(); 

	// Dessiner ici la courbe de Bézier.
	// Vous devez avoir implémenté Bernstein précédemment.
	
	
	glFlush();
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-20, 20, -20, 20, -10, 10);
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
   glutInitWindowSize(400, 400);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow("Courbe de Bézier");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
