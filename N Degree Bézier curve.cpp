/*
Name: Nisha Gurunath Bharathi
ID: 109896013

Project name: CSCI 272 Program Assignment4: N Degree Bézier curve
*/

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include<stdio.h>

#define PI 3.14159
#define MAX_CLICKS 50

using namespace std;

bool WireFrame= false;
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
    int nn;
    float xpos =0;
    float ypos =0;
    float Wwidth,Wheight;
    long double fact=1;int j=0;
    float i =0;
    float dstx,dsty,t;
    int numofclicks=0;
    int flag=0;int k=0;

    int click_array[MAX_CLICKS][2];
/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

     Wwidth = (float)width;
     Wheight = (float)height;

     Ratio= (double)width /(double)height;

    glViewport(0,0,(GLsizei) width,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective (45.0f,Ratio,0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

 }
long double factorial(int n)
{
    fact=1;
    for(int i=1;i<=n;i++)
    {
      fact=fact*i;
    }
    return fact;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here

    //reset on clicking space bar key in keyboard
    if(flag==5)
    {
        numofclicks=0;
    }
    //keep drawing until numofclicks/ points=50
    if(numofclicks>50){numofclicks=0;}

    //create number of points as many number of mouse clicks
    glPointSize(5.0);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    if(flag==2)//if left clicked only then display points
    {
        for(int i=0;i<numofclicks;i++)
        {
            //draw points clicked i.e x and y mouse click points stored in array
            glVertex3f(click_array[i][0],click_array[i][1],0);
        }
    }
    glEnd();

    //if numclicks>2 start drawing the curve
    if(numofclicks>2)
    {
        for(double t=0.0;t<=1.0;t+=0.001)
        {
            for(int i=0;i<=nn;i++)
            {
                xpos+= (factorial(nn)/(factorial(i)*factorial(nn-i)))*pow(t,i)*pow(1-t,nn-i)*click_array[i][0];
                ypos+= (factorial(nn)/(factorial(i)*factorial(nn-i)))*pow(t,i)*pow(1-t,nn-i)*click_array[i][1];
            }
            glColor3f(1.0,0.0,1.0);
            glPointSize(2.0);
            glBegin(GL_POINTS);
            glVertex3f(xpos,ypos,0);
            glEnd();

            xpos=0;ypos=0;//initialise xpos and ypos as 0
         }
    }
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 32:
              printf("reset");
              flag=5;
            break;

	  case 'w':
		WireFrame =!WireFrame;
	       break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    break;

   }
  glutPostRedisplay();
}


static void idle(void)
{
    // Use parametric equation with t increment for xpos and y pos
    // Don't need a loop
    glutPostRedisplay();
}



void mouse(int btn, int state, int x, int y){

    float scale = 54*(Wwidth/Wheight);

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){
            flag=2;
            //keep track of the number of mouse clicks
            numofclicks++;
            nn=numofclicks-1;

            //initialise t every time we run the loop
            t=0.0;

            //assign x and y mouse click coordinates to temporary variables dstx, dsty
            dstx=x; dsty=y;

            //bring the points to the center i.e Wwidth/2, Wheight/2
            dstx=x-(Wwidth/2);
            dsty=(Wheight/2)-y;

            //scale to match the window
            dstx=dstx/scale;
            dsty=dsty/scale;


            click_array[j][0]=dstx;
            click_array[j][1]=dsty;
            j++;
            }
             printf("dstx is %f, dsty is %f\n",dstx,dsty);
             printf("xpos is %f, ypos is %f\n",xpos,ypos);

            break;

          case GLUT_RIGHT_BUTTON:

            if(state==GLUT_DOWN)
            {
                printf("right click");
                flag=1;

            }
            break;
    }
     glutPostRedisplay();
};



static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);                 // assign a color you like

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 4");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
