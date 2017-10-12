#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>
#include "C:\Users\greg\source\repos\TP3\TP3\glut.h"
#include "C:\Users\greg\source\repos\TP3\TP3\struct.h"


#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define PI 3.14159

#define KEY_ESC 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_idle();
int zRotated;


int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // définition et création de la fenêtre graphique
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Primitives graphiques");

  // initialisation de OpenGL et de la scène
  initGL();  
  init_scene();

  // choix des procédures de callback pour 
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);
  glutIdleFunc(&window_idle);
  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
    	glShadeModel(GL_SMOOTH);
	glClearColor(RED, GREEN, BLUE, ALPHA);
    	glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  


  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
  glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
	
  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }     
}

GLvoid window_idle() 
{  
	zRotated++;
	glutPostRedisplay();
}


void render_scene()
{
//c'est ici qu'on dessine
	glLoadIdentity();
	int posInit = 0;
	int nbTeapots = 4;

	for (int i = 0; i< nbTeapots; i++) {
		glRotatef(zRotated/10, 0, 1, 0);	
		glTranslatef(0, posInit +i-nbTeapots*1.75, 0);		
		
		glPushMatrix();
			glTranslatef(0, 0, posInit + i - nbTeapots*1.75);
			glPushMatrix();
				glColor3f(0, 0, 1);
				glRotatef(zRotated, 0, 1, 0);
				glutWireTeapot(nbTeapots-i);						
				glPushMatrix();
					glColor3f(1, 0, 0);
					glRotatef(zRotated, 0, 1, 0);
					glTranslatef(posInit + i - nbTeapots*2, 0, 0);
					glutWireSphere(((nbTeapots-i)/2)+0.5,10,10);
					glPopMatrix();	
				glPopMatrix();
			glPopMatrix();
			}
 }