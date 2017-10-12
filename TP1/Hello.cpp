/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * hello.c
 * This is a simple, introductory OpenGL program.
 */
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>


void circle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}

void carre(void) {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();
}

void triangles(void)
{
   glBegin(GL_LINE_LOOP);
   glColor3f (1.0, 1.0, 1.0);
	  glVertex3f (0.05, 0.90, 0.0);
	  glVertex3f (0.05, 0.50, 0.0);
      glVertex3f (0.45, 0.50, 0.0);
   glEnd();
   
   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 0.0, 1.0);
	   glVertex3f(0.50, 0.70, 0.0);
	   glVertex3f(0.50, 0.50, 0.0);
	   glVertex3f(0.70, 0.50, 0.0);
   glEnd();
   
   glBegin(GL_LINE_LOOP);
   glColor3f(0.0, 1.0, 0.0);
	   glVertex3f(0.75, 0.60, 0.0);
	   glVertex3f(0.75, 0.50, 0.0);
	   glVertex3f(0.95, 0.50, 0.0);
   glEnd();
}
void cercles(int numCercle, float rayonParam) {
	
	float rayon = 0.10;
	float x = 0.50;
	for (int i = 0; i <= numCercle - 1; i++) {
		circle(x, 0.50, rayon, 30);
		rayon += rayonParam;
		x += rayonParam;
	}
}

void cercles2(int numCercle, float x) {

	float rayon = 0.2;
	float rayonParam = 0.75;

	for (int i = 0; i <= numCercle-1; i++) {
		circle(x, 0.50, rayon, 30);
		x = x + rayon + (rayon*rayonParam);				
		rayon = rayon * rayonParam;		
	}
}

void display(void)
{	
	/* clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	/* draw white polygon (rectangle) with corners at
	* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
	*/
	
	//circle(0.25, 0.25, 0.25, 15);
	//cercles(20, 0.01);
	cercles2(3, 0.2);

	/* Swap the buffers to show the one
	* on which we writed
	*/
	glutSwapBuffers();
}

void init (void)
{
/* select clearing color     */
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*
 * Declare initial window size, position, and display mode
 * (double buffer and RGB).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv){
//int test(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (300, 300);
   glutCreateWindow ("hello");
   init ();
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
