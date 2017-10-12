
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <GL/glut.h>
#include "struct.h"

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

float angleX=0.0f; //angle de rotation en Y de la scene
float angleY=0.0f; //angle de rotation en X de la scene

float pasDeplacement=1.25;


//position lumiere
float xLitePos=0;
float yLitePos=10;
float zLitePos=-100;

float tx=0.0;
float ty=0.0;
float tz=0.0;

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	// Si vous avez des choses à initialiser, c est ici.	
}

vector<point3> circle(point3 centre, float r, int num_segments)
{
	vector<point3> tabPointCercle = vector<point3>(num_segments);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = centre.x + r * cosf(theta);//calculate the x component 
		float y = centre.y + r * sinf(theta);//calculate the y component 
		float z = centre.z;
		
		point3 pointAAjouter = point3(x, y, z);
		tabPointCercle[ii] = pointAAjouter;

		glVertex3f(x , y, z);//output vertex 

	}
	glEnd();	
	return tabPointCercle;
}


/*for (stack = 0; stack < STACKS; ++stack) {
  for (slice = 0; slice < SLICES; ++slice) {
    y = 2.0 * stack / STACKS - 1.0;
    // for better distribution, use y = -cos(PI * stack / STACKS) 
r = sqrt(1 - y ^ 2);
x = r * sin(2.0 * PI * slice / SLICES);
z = r * cos(2.0 * PI * slice / SLICES);

vertex = radius * (x, y, z);
  }*/
void sphere(float rayon, int nombreParalleles, int nombreMeridiens) {
	point3 poleNord = point3(0, 0, rayon);
	point3 polesud = point3(0, 0, -rayon);
	
	for (int m = 0; m < nombreMeridiens; m++) {
		for (int p = 0; p < nombreParalleles; p++) {
			float y = 2 * m / p - 1;
			//float y = -cos(M_PI * m / p);
			float r = sqrt(1 - (y*y));
			float x = r * sin(2.0 * M_PI * p / nombreParalleles);
			float z = r * cos(2.0 * M_PI * p / nombreParalleles);

			point3 point = point3(x, y, x);
		}		
	}
}

void cone(float rayon, float hauteur, int nombreMeridiens) {
	point3 centreBaseCone = point3(0, 0, -hauteur / 2);
	point3 topCone = point3(0, 0, hauteur / 2);

	vector<point3>tabPointBaseCone = circle(centreBaseCone, rayon, nombreMeridiens);

	for (int i = 0; i < nombreMeridiens - 1; i++)
	{		
		glBegin(GL_TRIANGLES);
			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(tabPointBaseCone[i].x, tabPointBaseCone[i].y, tabPointBaseCone[i].z);
			glVertex3f(tabPointBaseCone[i+1].x, tabPointBaseCone[i+1].y, tabPointBaseCone[i+1].z);
			glVertex3f(topCone.x, topCone.y, topCone.z);
		glEnd();
	}
	//cas particulier du dernier triangle
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(tabPointBaseCone[tabPointBaseCone.size() - 1].x, tabPointBaseCone[tabPointBaseCone.size() - 1].y, tabPointBaseCone[tabPointBaseCone.size() - 1].z);
		glVertex3f(tabPointBaseCone[0].x, tabPointBaseCone[0].y, tabPointBaseCone[0].z);
		glVertex3f(topCone.x, topCone.y, topCone.z);
	glEnd();

	//BaseCircle :
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glBegin(GL_TRIANGLES);
			glColor3f(0.7, 0.7, 0.7);
			glVertex3f(tabPointBaseCone[i].x, tabPointBaseCone[i].y, tabPointBaseCone[i].z);
			glVertex3f(tabPointBaseCone[i + 1].x, tabPointBaseCone[i + 1].y, tabPointBaseCone[i + 1].z);
			glVertex3f(topCone.x, topCone.y, topCone.z);
		glEnd();
	}

	glBegin(GL_TRIANGLES);
		glColor3f(0.7, 0.7, 0.7);
		glVertex3f(tabPointBaseCone[tabPointBaseCone.size() - 1].x, tabPointBaseCone[tabPointBaseCone.size() - 1].y, tabPointBaseCone[tabPointBaseCone.size() - 1].z);
		glVertex3f(tabPointBaseCone[0].x, tabPointBaseCone[0].y, tabPointBaseCone[0].z);
		glVertex3f(topCone.x, topCone.y, topCone.z);
	glEnd();
}

void coneTronque(float rayon, float hauteur, float hauteurTronquage, int nombreMeridiens) {
	float coef = hauteurTronquage / hauteur;
	float rayonTronquagePoucentage = (hauteurTronquage/hauteur);
	float rayonTronquage = ((rayon)*coef)/2;
	cout << rayonTronquagePoucentage << endl;
	cout << rayonTronquage << endl;
	point3 centreCircleTop = point3(0, 0, (hauteur / 2)- (hauteurTronquage/2));
	point3 centreCircleDown = point3(0, 0, -hauteur / 2);

	vector<point3>tabPointCercle1 = circle(centreCircleTop, rayonTronquage, nombreMeridiens);
	vector<point3>tabPointCercle2 = circle(centreCircleDown, rayon, nombreMeridiens);



	//Triangles avec la base en bas
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
		glVertex3f(tabPointCercle2[i].x, tabPointCercle2[i].y, tabPointCercle2[i].z);
		glVertex3f(tabPointCercle2[i + 1].x, tabPointCercle2[i + 1].y, tabPointCercle2[i + 1].z);
		glEnd();
	}
	//cas particulier du dernier triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[tabPointCercle1.size() - 1].x, tabPointCercle1[tabPointCercle1.size() - 1].y, tabPointCercle1[tabPointCercle1.size() - 1].z);
		glVertex3f(tabPointCercle2[tabPointCercle1.size() - 1].x, tabPointCercle2[tabPointCercle1.size() - 1].y, tabPointCercle2[tabPointCercle1.size() - 1].z);
		glVertex3f(tabPointCercle2[0].x, tabPointCercle2[0].y, tabPointCercle2[0].z);
	glEnd();



	// Triangles avec la base en haut
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.0, 0.7, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
		glVertex3f(tabPointCercle1[i + 1].x, tabPointCercle1[i + 1].y, tabPointCercle1[i + 1].z);
		glVertex3f(tabPointCercle2[i + 1].x, tabPointCercle2[i + 1].y, tabPointCercle2[i + 1].z);
		glEnd();
	}
	// Cas pariculier du dernier triangle
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.7, 0.0);
		glVertex3f(tabPointCercle1[tabPointCercle1.size() - 1].x, tabPointCercle1[tabPointCercle1.size() - 1].y, tabPointCercle1[tabPointCercle1.size() - 1].z);
		glVertex3f(tabPointCercle1[0].x, tabPointCercle1[0].y, tabPointCercle1[0].z);
		glVertex3f(tabPointCercle2[0].x, tabPointCercle2[0].y, tabPointCercle2[0].z);
	glEnd();

	//TopCircle :
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.0, 0.7, 0.0);
		glBegin(GL_TRIANGLES);
			glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
			glVertex3f(tabPointCercle1[i + 1].x, tabPointCercle1[i + 1].y, tabPointCercle1[i + 1].z);		
			glVertex3f(centreCircleTop.x, centreCircleTop.y, centreCircleTop.z);
		glEnd();
	}
	glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[tabPointCercle1.size() - 1].x, tabPointCercle1[tabPointCercle1.size() - 1].y, tabPointCercle1[tabPointCercle1.size() - 1].z);
		glVertex3f(tabPointCercle1[0].x, tabPointCercle1[0].y, tabPointCercle1[0].z);		
		glVertex3f(centreCircleTop.x, centreCircleTop.y, centreCircleTop.z);
	glEnd();

	//DownCircle :
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.7, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle2[i].x, tabPointCercle2[i].y, tabPointCercle2[i].z);
		glVertex3f(tabPointCercle2[i + 1].x, tabPointCercle2[i + 1].y, tabPointCercle2[i + 1].z);
		glVertex3f(0, 0, -hauteur / 2);
		glEnd();
	}
	glBegin(GL_TRIANGLES);
	glVertex3f(tabPointCercle2[tabPointCercle2.size() - 1].x, tabPointCercle2[tabPointCercle2.size() - 1].y, tabPointCercle2[tabPointCercle2.size() - 1].z);
	glVertex3f(tabPointCercle2[0].x, tabPointCercle2[0].y, tabPointCercle2[0].z);
	glVertex3f(0, 0, -hauteur / 2);
	glEnd();

}

void cylindre(float rayon, float hauteur, int nombreMeridiens) {
	point3 centreCircleTop = point3(0, 0, hauteur/2);
	point3 centreCircleDown = point3(0, 0, -hauteur/2);

	vector<point3>tabPointCercle1 = circle(centreCircleTop, rayon, nombreMeridiens);
	vector<point3>tabPointCercle2 = circle(centreCircleDown, rayon, nombreMeridiens);


	
	//Triangles avec la base en bas
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_TRIANGLES);			
			glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
			glVertex3f(tabPointCercle2[i].x, tabPointCercle2[i].y, tabPointCercle2[i].z);
			glVertex3f(tabPointCercle2[i+1].x, tabPointCercle2[i+1].y, tabPointCercle2[i+1].z);
		glEnd();
	}
	//cas particulier du dernier triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[tabPointCercle1.size()-1].x, tabPointCercle1[tabPointCercle1.size()-1].y, tabPointCercle1[tabPointCercle1.size()-1].z);
		glVertex3f(tabPointCercle2[tabPointCercle1.size()-1].x, tabPointCercle2[tabPointCercle1.size()-1].y, tabPointCercle2[tabPointCercle1.size()-1].z);
		glVertex3f(tabPointCercle2[0].x, tabPointCercle2[0].y, tabPointCercle2[0].z);
	glEnd();
	

	
	// Triangles avec la base en haut
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
		glVertex3f(tabPointCercle1[i + 1].x, tabPointCercle1[i + 1].y, tabPointCercle1[i + 1].z);
		glVertex3f(tabPointCercle2[i+1].x, tabPointCercle2[i+1].y, tabPointCercle2[i+1].z);
		glEnd();
	}
	// Cas pariculier du dernier triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(tabPointCercle1[tabPointCercle1.size() - 1].x, tabPointCercle1[tabPointCercle1.size() - 1].y, tabPointCercle1[tabPointCercle1.size() - 1].z);
	glVertex3f(tabPointCercle1[0].x, tabPointCercle1[0].y, tabPointCercle1[0].z);
	glVertex3f(tabPointCercle2[0].x, tabPointCercle2[0].y, tabPointCercle2[0].z);
	glEnd();

	//TopCircle :
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.0, 0.7, 0.0);
		glBegin(GL_TRIANGLES);
			glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
			glVertex3f(tabPointCercle1[i+1].x, tabPointCercle1[i+1].y, tabPointCercle1[i+1].z);
			glVertex3f(0, 0, hauteur/2);
		glEnd();
	}
	glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle1[tabPointCercle1.size()-1].x, tabPointCercle1[tabPointCercle1.size() - 1].y, tabPointCercle1[tabPointCercle1.size() - 1].z);
		glVertex3f(tabPointCercle1[0].x, tabPointCercle1[0].y, tabPointCercle1[0].z);
		glVertex3f(0, 0, hauteur / 2);
	glEnd();

	//DownCircle :
	for (int i = 0; i < nombreMeridiens - 1; i++)
	{
		glColor3f(0.7, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(tabPointCercle2[i].x, tabPointCercle2[i].y, tabPointCercle2[i].z);
		glVertex3f(tabPointCercle2[i + 1].x, tabPointCercle2[i + 1].y, tabPointCercle2[i + 1].z);
		glVertex3f(0, 0, - hauteur / 2);
		glEnd();
	}
	glBegin(GL_TRIANGLES);
	glVertex3f(tabPointCercle2[tabPointCercle2.size() - 1].x, tabPointCercle2[tabPointCercle2.size() - 1].y, tabPointCercle2[tabPointCercle2.size() - 1].z);
	glVertex3f(tabPointCercle2[0].x, tabPointCercle2[0].y, tabPointCercle2[0].z);
	glVertex3f(0, 0, - hauteur / 2);
	glEnd();

	//Version avec ligne
	/*for (int i = 0; i < nombreMeridiens; i++) {
		glBegin(GL_LINES);
			glVertex3f(tabPointCercle1[i].x, tabPointCercle1[i].y, tabPointCercle1[i].z);
			glVertex3f(tabPointCercle2[i].x, tabPointCercle2[i].y, tabPointCercle2[i].z);
		glEnd();
	}*/
}


/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //effacement du buffer

	//Description de la scene
	glLoadIdentity();
	//rotation de la scene suivant les mouvements de la souris
	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);
	glTranslatef(tx,ty,tz);

	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);

	// Voir plus tard les push et Pop
	glPushMatrix();			
			
			//glRotatef(-90,1.0f,0.0f,0.0f);
			// C'est ici que l'on dessine notre cylindre
			// Il n'y a pour l'instant qu'un triangle gris ...
			coneTronque(10, 8, 6, 20);
			cone(10, 8, 20);

			// Exemple d'appel à Point3
			point3 p1 = point3(-1.0,1.0,0.0);
			point3 p2 = point3(1,1,0);
			point3 p3 = point3(1,2,0);
			//tableau de points
			point3 tab[2];

			tab[0]=p1;
			tab[1]=p2;

			/*glColor3f(0.7,0.7,0.7);
			glBegin(GL_TRIANGLES);	
				glVertex3f(tab[0].x,tab[0].y, tab[0].z);
				glVertex3f(tab[1].x,tab[1].y, tab[1].z);
				glVertex3f(p3.x,p3.y,p3.z);
			glEnd();*/
	glPopMatrix();			



	//affiche les axes du repere
		glColor3f(0.0,1.0,0.0); //Y vert
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,20,0);
		glEnd();

		glColor3f(0.0,0.0,1.0); //Z bleu
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,20);
		glEnd();
		
		glColor3f(1.0,0.0,0.0); //X rouge
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(20,0,0);
		glEnd();

	glutSwapBuffers();// echange des buffers
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

GLvoid gestionSouris(int x, int y)
{
	angleX=x*720/WIDTH; //gere l'axe Oy
	angleY=-(y*180/HEIGHT-90)*4; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y) 
{
	switch (key) {
		case GLUT_KEY_UP :
			tz+=int(pasDeplacement);glutPostRedisplay();
		break;

		case GLUT_KEY_DOWN :
			tz-=int(pasDeplacement);glutPostRedisplay();
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
		ty+=int(pasDeplacement);glutPostRedisplay();
	break;

	case 's':
		ty-=int(pasDeplacement);glutPostRedisplay();
	break;

	case 'q':
		tx-=int(pasDeplacement);glutPostRedisplay();
	break;

	case 'd':
		tx+=int(pasDeplacement);glutPostRedisplay();
	break;

//sortie
	case KEY_ESC:
		exit(0);
		break;

	default:
		printf ("La touche %d non active.\n", key);
	break;
	}
glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInitWindowSize(400, 400);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutCreateWindow("Mon cylindre");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(&window_key_down);
   glutDisplayFunc(display);
   glutPassiveMotionFunc(gestionSouris);
   glutSpecialFunc(&gestionFleche);
   glutMainLoop();
   return 0;
}
