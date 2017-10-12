/*
 *  teapot.c
 *  affiche d'une theiere en rotation
 * d'apres torus.c du redbook
 */


#include <gl\GLU.h>
#include <gl\GL.h>
#include <gl\glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ESC 27

float angle=0.1;


/* initialisation d'OpenGL*/
static void init(void)
{
   glShadeModel(GL_SMOOTH);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   
    // Z Buffer pour la suppression des parties cachées
   glEnable(GL_DEPTH_TEST);
  
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   
   GLfloat ambient[] = {0.0, 0.0, 1.0, 1.0};
   GLfloat diffuse[] = {0.9,0.9, 0.2, 1.0};
   GLfloat position[] = {0.0, 3.0, 3.0, 0.0};
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
}

/* Vide la fenetre et dessine la theiere */
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f (0.1, 0.1, 1.0);
   GLfloat specular [] = { 1.0, 1.0, 0.5, 1.0 };
   GLfloat shininess [] = { 100.0 };

  // Definit les propriétés matérielles de la couleur spéculaire et du
  // degré de brillance. 
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(angle,0,1,0); 
  
  glutSolidTeapot(1.0);
  glFlush();
  
  glutSwapBuffers();
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2, 2, -2, 2, -2, 2);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void idle(void)
{
    angle+=0.3;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case ESC:
      exit(0);
      break;
   }
}

int main(int argc, char **argv)
{
   glutInitWindowSize(400, 400);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("1er programme OpenGL");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
