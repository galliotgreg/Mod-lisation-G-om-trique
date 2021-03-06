/*
 *	Tableau des points permettant de g�rer les points de controles
 * On s�lectionne le point en se d�pla�ant avec + et -, ...
 * On s�lectionne ensuite si on veut faire monter, descendre amener vers la gauche ou la droite le point.
 *   d : translation � droite
 *   q : � gauche
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

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

float tx=0.0;
float ty=0.0;

// Tableau des points de contr�les en global ...
point3 TabPC[10];
// Ordre de la courbre  : Ordre
// Degr� de la courbe = Ordre - 1
int const Ordre = 10;




// Point de controle selectionn�
int numPoint = 0;

// Fonction Factorielle fonctionne jusqu'� n=20, ne consid�re pas les overflow
int fact(int n)
{
	int res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;	 
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
		cout << "u doit �tre entre 0 et 1" << endl;
		return point3();
	}
	
}

float Bernstein(int i, int n, float t)
{
	int fact_n = fact(n);
	int fact_i = fact(i);
	int fact_NMoinsI = fact(n - i);
	float pow_T_I = pow(t, i);	
	
	float pow_final = pow(1 - t, n - i);

 return ((fact_n/(fact_i*fact_NMoinsI))*pow_T_I*pow_final);
}

// Fonction courbe de b�zier
point3 bezier(float t) {
	point3 res = point3(0, 0, 0);
	for (int i = 0; i < 4; i++) {
		res += TabPC[i] * Bernstein(i, 3, t);
	}
	return res;
}
point3 bezier1(float t) {
	point3 res = point3(0, 0, 0);
	for (int i = 0; i < 4; i++) {
		res += TabPC[i+4] * Bernstein(i, 3, t);
	}
	return res;
}

point3 produitVect(point3 u, point3 v) {
	point3 res = point3(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
	cout << "*********************************************" << endl;
	cout << res.x << " " << res.y << " " << res.z << endl;
	cout << "*********************************************" << endl;
	return res;
}

GLvoid initGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
	glEnable(GL_DEPTH_TEST);
}

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		
	glEnable(GL_DEPTH_TEST);

	// Initialisation des points de contr�les
	// On choisit de les intialiser selon une ligne
	//for (int i = 0; i < Ordre; i++)
	//{
     //TabPC[i] = point3(i,i,i);
    //}
	/*
	// Tableau pour la surface r�gl�
	TabPC[0] = point3(-2, -2, 0);
	TabPC[1] = point3(-1, 1, 0);
	TabPC[2] = point3(1, 1, 0);
	TabPC[3] = point3(2, 1, 0);	
	TabPC[4] = point3(-4, -4, 0);
	TabPC[5] = point3(-3, 3, 0);
	TabPC[6] = point3(3, 3, 0);
	TabPC[7] = point3(4,3,0);*/

	//Tableau pour la carreau param�trique
	TabPC[0] = point3(0, 0, 0);
	TabPC[1] = point3(1, 6, 0);
	TabPC[2] = point3(2, 3, 0);
	TabPC[3] = point3(3, 7, 0);
	TabPC[4] = point3(0, 0, 0);
	TabPC[5] = point3(3, 3, 0);
	TabPC[6] = point3(5, 3, 0);
	TabPC[7] = point3(7, 3, 0);	
}


/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
   
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	
	//glTranslatef(tx,ty,0.0);

	

	point3 Ptemp;
	point3 P0 = point3(5, 8, 0);
	point3 P1 = point3(10, 9, 0);
	point3 V0 = point3(7, -1, 0);
	point3 V1 = point3(4, -9, 0);
	

	/*if (numPoint == 2) {
		TabPC[numPoint] = TabPC[numPoint] + point3(tx, ty, 0);
		TabPC[4] = TabPC[4] + point3(-tx, -ty, 0);
	}
	else if (numPoint == 4) {
		TabPC[numPoint] = TabPC[numPoint] + point3(tx, ty, 0);
		TabPC[2] = TabPC[2] + point3(-tx, -ty, 0);
	}
	else if (numPoint == 3) {
		TabPC[2] = TabPC[2] + point3(tx, ty, 0);
		TabPC[numPoint] = TabPC[numPoint] + point3(tx, ty, 0);
		TabPC[4] = TabPC[4] + point3(tx, ty, 0);
	}
	else {*/
		TabPC[numPoint] = TabPC[numPoint] + point3(tx, ty, 0);
	//}
	
	//// Enveloppe des points de controles
	glColor3f (1.0, 0.0, 0.0);
	
	/*
	glBegin(GL_LINE_STRIP);
        for (int i =0; i <= 3; i++)
        {
		 glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
        }
    glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 4; i <= 7; i++)
	{
		glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
	}
	glEnd();*/

	//Enveloppe Pour Surface Param�trque
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 3; i++)
	{
		glVertex3f(TabPC[i].x, TabPC[i].y, TabPC[i].z);
	}
	glEnd();

	

	glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_POINTS);
	//	glVertex3f(P0.x, P0.y, P0.z);
	//	glVertex3f(P1.x, P1.y, P1.z);
	//	glVertex3f(V0.x, V0.y, V0.z);
	//	glVertex3f(V1.x, V1.y, V1.z);
	//glEnd();

	glColor3f(0.0, 1.0, 0.0);
	/*Hermite*/
	//double u = 0.0;
	//glBegin(GL_LINE_STRIP);
	//	for (int i = 0; i < Ordre; i++) 
	//	{
	//		point3 temp = hermite(P0, P1, V0, V1, u);
	//		glVertex3f(temp.x, temp.y, temp.z);
	//		u += 0.1;
	//	}
	//	glEnd();

	/*B�zier*/
	float u = 0.0;
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= Ordre; i++) 
		{
			point3 temp = bezier(u);
			glVertex3f(temp.x, temp.y, temp.z);
			u += 0.1;
		}
		glEnd();
	/*
	u = 0.0;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= Ordre; i++)
	{
		point3 temp = bezier1(u);
		glVertex3f(temp.x, temp.y, temp.z);
		u += 0.1;
	}
	glEnd();*/
	
	/*Surface reglee*/
	/*
	u = 0.0;	
	point3 temp1;
	point3 temp2;
	point3 temp3;
	for (int i = 0; i < Ordre; i++)
	{					
		temp1 = bezier(u);
		temp2 = bezier1(u);
		temp3 = bezier1(u+0.1);					
			
		glColor3f(0.0, 0.5, 0.5);
		glBegin(GL_TRIANGLES);
			glVertex3f(temp1.x, temp1.y, temp1.z);
			glVertex3f(temp2.x, temp2.y, temp2.z);
			glVertex3f(temp3.x, temp3.y, temp3.z);
		glEnd();

		temp1 = bezier(u);
		temp2 = bezier(u + 0.1);
		temp3 = bezier1(u + 0.1);
		
		glColor3f(0.5, 0.5, 0.0);
		glBegin(GL_TRIANGLES);
			glVertex3f(temp1.x, temp1.y, temp1.z);
			glVertex3f(temp2.x, temp2.y, temp2.z);
			glVertex3f(temp3.x, temp3.y, temp3.z);
		glEnd();

		u += 0.1;
	}*/
	
	//Carreau parametrique	
	/*
		u = 0.1;
	for (int i = 0; i < Ordre; i++) {
		point3 bezierU = bezier(u);
		double v = 0.0;
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= Ordre; j++)
		{
			point3 temp = bezier1(v);
			glVertex3f(temp.x + bezierU.x, temp.y + bezierU.y, temp.z + bezierU.z);
			v += 0.1;
		}
		glEnd();		

		point3 bezier1U = bezier1(u);
		v = 0.0;
		glColor3f(0.5, 0.5, 0.0);
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= Ordre; j++)
		{
			point3 temp = bezier(v);
			glVertex3f(temp.x + bezier1U.x, temp.y + bezier1U.y, temp.z + bezier1U.z);
			v += 0.1;
		}
		glEnd();
		u += 0.1;
	}
	*/

	// Carreau param�trique avec triangles	
	/*for (double u = 0.0; u < 1; u += 0.1) {
		for (double v = 0.0; v < 1; v += 0.1) {
			point3 bezierU = bezier(u);
			point3 bezierU_plus1 = bezier(u + 0.1);
			point3 bezier1U = bezier1(v);
			point3 bezier1U_plus1 = bezier1(v + 0.1);
			
			glColor3f(0.5, 0.0, 0.5);
			glBegin(GL_TRIANGLES);
			glVertex3f(bezierU.x, bezierU.y, bezierU.z);
			glVertex3f(bezierU_plus1.x, bezierU_plus1.y, bezierU_plus1.z);
			glVertex3f(bezier1U.x, bezier1U.y, bezier1U.z);
			glEnd;

			glColor3f(0.5, 0.5, 0.0);
			glBegin(GL_TRIANGLES);
			glVertex3f(bezier1U.x, bezier1U.y, bezier1U.z);
			glVertex3f(bezierU_plus1.x, bezierU_plus1.y, bezierU_plus1.z);
			glVertex3f(bezier1U.x + bezierU_plus1.x, bezier1U.y + bezierU_plus1.y, bezier1U.z + bezierU_plus1.z);
			glEnd;
		}				
	}*/
	
	//Surface balay�e
	u = 0.0;
	point3 pointes[Ordre+1];
	point3 baseDroite[Ordre+1];
	point3 baseGauche[Ordre+1];

	for (int i = 0; i <= Ordre; i++) {
		point3 bezierU = bezier(u);

		pointes[i] = point3(TabPC[0].x + bezierU.x, TabPC[0].y + bezierU.y, TabPC[0].z);
		baseDroite[i] = point3(TabPC[0].x + 2 + bezierU.x, TabPC[0].y + 2 + bezierU.y, TabPC[0].z);
		baseGauche[i] = point3(TabPC[0].x - 2 + bezierU.x, TabPC[0].y + 2 + bezierU.y, TabPC[0].z);
		
		/*glBegin(GL_POINT);
			glVertex3f(TabPC[0].x + bezierU.x, TabPC[0].y + bezierU.y, TabPC[0].z);
			glVertex3f(TabPC[0].x + 2 + bezierU.x, TabPC[0].y + 2 + bezierU.y, TabPC[0].z );
			glVertex3f(TabPC[0].x - 2 + bezierU.x, TabPC[0].y + 2 + bezierU.y, TabPC[0].z);
		glEnd();*/
		u += 0.1;
	}

	for (int i = 0; i < Ordre; i++) {
		//Draw triangle base
		glColor3f(0.25, 0.0, 0.5);
		glBegin(GL_TRIANGLES);
			glVertex3f(baseDroite[i].x , baseDroite[i].y, baseDroite[i].z);
			glVertex3f(baseDroite[i+1].x, baseDroite[i+1].y, baseDroite[i+1].z);
			glVertex3f(baseGauche[i].x, baseGauche[i].y, baseGauche[i].z);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3f(baseDroite[i + 1].x, baseDroite[i + 1].y, baseDroite[i + 1].z);
			glVertex3f(baseGauche[i + 1].x, baseGauche[i + 1].y, baseGauche[i + 1].z);
			glVertex3f(baseGauche[i].x, baseGauche[i].y, baseGauche[i].z);
		glEnd();

		//Draw right face
		glColor3f(0.5, 0.0, 0.25);
		glBegin(GL_TRIANGLES);
			glVertex3f(baseDroite[i].x, baseDroite[i].y, baseDroite[i].z);
			glVertex3f(baseDroite[i + 1].x, baseDroite[i + 1].y, baseDroite[i + 1].z);
			glVertex3f(pointes[i].x, pointes[i].y, pointes[i].z);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3f(baseDroite[i + 1].x, baseDroite[i + 1].y, baseDroite[i + 1].z);
			glVertex3f(pointes[i + 1].x, pointes[i + 1].y, pointes[i + 1].z);
			glVertex3f(pointes[i].x, pointes[i].y, pointes[i].z);
		glEnd();

		//Draw left face
		glColor3f(0.0, 0.25, 0.25);
		glBegin(GL_TRIANGLES);
			glVertex3f(baseGauche[i].x, baseGauche[i].y, baseGauche[i].z);
			glVertex3f(baseGauche[i + 1].x, baseGauche[i + 1].y, baseGauche[i + 1].z);
			glVertex3f(pointes[i].x, pointes[i].y, pointes[i].z);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex3f(baseGauche[i + 1].x, baseGauche[i + 1].y, baseGauche[i + 1].z);
			glVertex3f(pointes[i + 1].x, pointes[i + 1].y, pointes[i + 1].z);
			glVertex3f(pointes[i].x, pointes[i].y, pointes[i].z);
		glEnd();
	}

	// Affichage du point de controle courant
	// On se d�place ensuite avec + et - 
    // � d'un point de contr�le au suivant (+)
    // � d'un point de contr�le au pr�c�dent (-)
	glColor3f (0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
		glVertex3f(TabPC[numPoint].x+0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
		glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y-0.1, TabPC[numPoint].z);
		glVertex3f(TabPC[numPoint].x-0.1, TabPC[numPoint].y+0.1, TabPC[numPoint].z);
	glEnd(); 

	// Dessiner ici la courbe de B�zier.
	// Vous devez avoir impl�ment� Bernstein pr�c�demment.
	
	
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
   glutCreateWindow("Courbe de B�zier");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);   
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
