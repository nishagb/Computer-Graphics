/*
Name: Nisha Gurunath Bharathi
ID: 109896013

Project name: CSCI 272 Program Assignment3: 3D Model Loading
*/


#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<stdio.h>
#include <iostream>
#include <math.h>
#define PI 3.14159

using namespace std;

bool WireFrame= false;

GLfloat matrixX[16];
GLfloat matrixY[16];
GLfloat matrixZ[16];
GLfloat x, y, z, w;
int flag=0,i=0;

static GLint RotateY=0; /* model rotation Y index*/
static GLint RotateX=0; /* model rotation X index*/
static GLint RotateZ=0; /* model rotation Z index*/


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

double zoom=0;
float Vertices[8][3]= {
0.0, 0.0, 0.0,
0.0, 0.0, 1.0,
0.0, 1.0, 0.0,
0.0, 1.0, 1.0,
1.0, 0.0, 0.0,
1.0, 0.0, 1.0,
1.0, 1.0, 0.0,
1.0, 1.0, 1.0
};
float Normals[6][3] = {
0.0, 0.0, 1.0,
0.0, 0.0, -1.0,
0.0, 1.0, 0.0,
0.0, -1.0, 0.0,
1.0, 0.0, 0.0,
-1.0, 0.0, 0.0
};
int ind[12][6] ={ // vertices/normals
1,2, 7,2, 5,2,
1,2, 3,2, 7,2,
1,6, 4,6, 3,6,
1,6, 2,6, 4,6,
3,3, 8,3, 7,3,
3,3, 4,3, 8,3,
5,5, 7,5, 8,5,
5,5, 8,5, 6,5,
1,4, 5,4, 6,4,
1,4, 6,4, 2,4,
2,1, 6,1, 8,1,
2,1, 8,1, 4,1
 };

/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
     {
         glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
         Ratio =  height/width;
      }
    else
      {
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
        Ratio = width /height;
      }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,Ratio,0.1f, 100.0f); //to change the size of cube change 1st parameter to 80.0f or etc
 }


void CreateFromAxisAngle(GLfloat X, GLfloat Y, GLfloat Z, GLfloat degree)
{
 /* First we want to convert the degrees to radians since the angle is assumed to be in radians*/
GLfloat angle = (GLfloat)((degree / 180.0f) * PI);
 /* Here we calculate the sin( theta / 2) once for optimization */
GLfloat result = (GLfloat)sin( angle / 2.0f );
 /* Calculate the w value by cos( theta / 2 ) */
w = (GLfloat)cos( angle / 2.0f );
 /* Calculate the x, y and z of the quaternion */
x = (GLfloat)(X * result);
y = (GLfloat)(Y * result);
z = (GLfloat)(Z * result);
}


void CreateMatrix(GLfloat *pMatrix)
{
    //quaternion rotation matrix
// First row
pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z );
pMatrix[ 1] = 2.0f * (x * y + z * w);
pMatrix[ 2] = 2.0f * (x * z - y * w);
pMatrix[ 3] = 0.0f;
// Second row
pMatrix[ 4] = 2.0f * ( x * y - z * w );
pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z );
pMatrix[ 6] = 2.0f * (z * y + x * w );
pMatrix[ 7] = 0.0f;
// Third row
pMatrix[ 8]=2.0f * ( x * z + y * w );
pMatrix[ 9]=2.0f * ( y * z - x * w );
pMatrix[ 10] = 1.0f - 2.0f * ( x * x + y * y );
pMatrix[ 11] = 0.0f;
//fourth
pMatrix[ 12] = 0.0f;
pMatrix[ 13] = 0.0f;
pMatrix[ 14] = 0.0f;
pMatrix[ 15] = 1.0f;

}


static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

       //in glulookat change it to 0,1,10.... and so on  because we want to view it from particular angle for zoom in and zoom out
    gluLookAt(0,1,5,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

              if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME


  // your code here
    CreateMatrix(matrixX); // initial quaternion X
    CreateFromAxisAngle(1, 0, 0,RotateX);
    glMultMatrixf(matrixX);


    CreateMatrix(matrixY); // initial quaternion Y
    CreateFromAxisAngle(0, 1, 0,RotateY);
    glMultMatrixf(matrixY);

    CreateMatrix(matrixZ); // initial quaternion Z
    CreateFromAxisAngle(0, 0, 1,RotateZ);
    glMultMatrixf(matrixZ);


 glPushMatrix();
    //condition to check if flag=4, zoom in or zoom out
    if(flag==4)
    {
       glTranslated(-0.50,-0.50,zoom);
    }
    else
    {   //make it rotate at the centroid of cube which is (side/2) from all 3 directions
       glTranslated(-0.50,-0.50,-0.50);
    }

    glBegin(GL_TRIANGLES);

    //for loop to plot 12 points as in indices matrix
    for(int i=0;i<12;i++)
    {
                //draw 3 vertices of triangle
                //1 vertex
                 glColor3f(Vertices[(ind[i][0])-1][0],Vertices[(ind[i][0])-1][1],Vertices[(ind[i][0])-1][2]);
                 glNormal3f(Normals[(ind[i][1])-1][0],Normals[(ind[i][1])-1][1],Normals[(ind[i][1])-1][2]);
                 glVertex3f(Vertices[(ind[i][0])-1][0],Vertices[(ind[i][0])-1][1],Vertices[(ind[i][0])-1][2]);

                 //2d vertex
                 glColor3f(Vertices[(ind[i][2])-1][0],Vertices[(ind[i][2])-1][1],Vertices[(ind[i][2])-1][2]);
                 glNormal3f(Normals[(ind[i][3])-1][0],Normals[(ind[i][3])-1][1],Normals[(ind[i][3])-1][2]);
                 glVertex3f(Vertices[(ind[i][2])-1][0],Vertices[(ind[i][2])-1][1],Vertices[(ind[i][2])-1][2]);

                 //3rd vertex of triangle
                 glColor3f(Vertices[(ind[i][4])-1][0],Vertices[(ind[i][4])-1][1],Vertices[(ind[i][4])-1][2]);
                 glNormal3f(Normals[(ind[i][5])-1][0],Normals[(ind[i][5])-1][1],Normals[(ind[i][5])-1][2]);
                 glVertex3f(Vertices[(ind[i][4])-1][0],Vertices[(ind[i][4])-1][1],Vertices[(ind[i][4])-1][2]);
    }
    glEnd();


    glutSwapBuffers();
}

//method to execute when special keys are pressed
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'd':
              //flag=3;
              printf("z axis clkwise");
              RotateZ = (RotateZ -5)%360;
            break;
        case 'a':
           // flag=3;
            printf("z axis anti clkwise");
            RotateZ = (RotateZ +5)%360;
            break;

	  case 'w':
		WireFrame =!WireFrame;
	       break;
    }
}

//method to execute when keys are pressed
void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            printf("up");
        RotateX = (RotateX +5)%360; //rotate up
    break;
    case GLUT_KEY_DOWN:
         printf("down");
        RotateX = (RotateX -5)%360; //rotate down

    break;
    case GLUT_KEY_LEFT:
       printf("left");
        RotateY = (RotateY -5)%360;  //rotate left

    break;
    case GLUT_KEY_RIGHT:
       printf("right");
        RotateY = (RotateY +5)%360;  //rotate right

    break;
    case GLUT_KEY_END:
        flag=4;
        zoom=zoom+0.50; //zoom in
        printf("zoom in %f",zoom);
        break;

    case GLUT_KEY_HOME:
        flag=4;
        zoom=zoom-0.50; //zoom out
        printf("zoom out %f",zoom);
        break;

   }
  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}