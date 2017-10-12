#include <GL/glut.h>    

#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>

#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

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

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
}

void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  render_scene();

  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);

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

// le tracé graphique (le rectangle blanc)

void render_scene()
{
  // définit la couleur de tracé
  glColor3f(1.0, 1.0, 1.0);

  // initialise la matrice de modélisation
  glLoadIdentity();
  // Translate l'objet
  glTranslatef(-5.0, 5.0, 0.0);
  // dessine les sommets selon la primitive GL_LINES 
  glBegin(GL_LINES);

    // Sommet 1
    glVertex2f(-1.0, 1.0);

    // Sommet 2
    glVertex2f(1.0, 2.0);

    // Sommet 3
    glVertex2f(2.0, 0.0);

    // Sommet 4
    glVertex2f(1.0, -1.0);

    // Sommet 5
    glVertex2f(-2.0, -2.0);

  glEnd();

  glLoadIdentity();
  glTranslatef(0.0, 5.0, 0.0);

  glBegin(GL_LINE_STRIP);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(5.0, 5.0, 0.0);

  glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(-5.0, 0.0, 0.0);

  glBegin(GL_POLYGON);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(0.0, 0.0, 0.0);

  glBegin(GL_QUADS);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(5.0, 0.0, 0.0);

  glBegin(GL_QUAD_STRIP);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(-5.0, -5.0, 0.0);

  glBegin(GL_TRIANGLES);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(0.0, -5.0, 0.0);

  glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  glLoadIdentity();
  glTranslatef(5.0, -5.0, 0.0);

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-2.0, -2.0);
  glEnd();
}

