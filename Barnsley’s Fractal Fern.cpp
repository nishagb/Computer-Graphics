/*
CSCI 272 Project 1: Barnsley’s Fractal Fern
Student name: Nisha Gurunath Bharathi
Student ID: 109896013
  
*/


/* Required Header files used */
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include <stdlib.h>
/* GLUT callback Handlers */

int limit=200000;         /* Declaration of a variable limit */
float a,b,c,d,e,f;	  /* Declaration of float type variables a,b,c,d,e*/
float x=0.5;		/* Initialisation of x variable */
float y=0.5;		/* Initialisation of y variable */
float tempx=x;		/* Store the value of x and y in temporary variables tempx and tempy */
float tempy=y;
int i;			/*  Declaration of int variables i and num*/
int num=0;


/* Method used for resizing the window size */
void resize(int width, int height)
{
    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);

    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

/* Initialisation method */
void init()
{
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-2.5,2.75,10.5,0, -1.0, 1.0); // adjusted for suitable viewport

}


/* The main display method where in the logic is embedded */
void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen
  // your code here

/* loop which runs from 0 to 200000 to generate random numbers and we restrict it by mod and we have included 3 cases to assign the values to a,b,c,d,e variables */
  for(i=0;i<200000;i++)
  {
    num = rand()%100;

    if(num<85) { a=0.85; b = -0.04; c =0.04; d =0.85; e =0; f=1.6;}
    else if(num<92) { a= 0.2; b =0.23; c =-0.26; d =0.22; e =0; f=1.6; }
    else if(num<99) { a= -0.15; b =0.26; c =0.28; d =0.24; e =0; f=0.44;}
    else {a= 0; b =0; c =0; d =0.16; e =0; f=0;  }

/* Calculation of x and y variable values by the equation */
    x= a*tempx+c*tempy+e;
    y= b*tempx+d*tempy+f;

/*Display color methods  */
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex3f(x,y,0);			/* specify the points */
    glEnd();

    tempx =x;
    tempy =y;

  }


  glFlush ();                           // clear the buffer
}


void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Program1");                //program title
   init();
   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutMainLoop();                               //loop

    return EXIT_SUCCESS;
}
