/*
Name: Nisha Gurunath Bharathi
ID: 109896013

Project name: CSCI 272 Program Assignment5: WaveFront obj Modal Loader

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
#include<String.h>

#define PI 3.14159

using namespace std;

bool WireFrame= false;
int i =0;
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    float xpos =0;
    float ypos =0;
    float Wwidth,Wheight;
    double zoom=0;
    double up=0;
    double rot=0;

    //structure for vertex
struct vertex{
float x;  // x coordinate
float y;  // y coordinate
float z;  // z coordinate
float w;  // optional component
};

    //structure for normal
struct normal{
float x; // x component of normal
float y; // y component of normal
float z; // z component of normal
float w;  // optional component
};

 //structure for texture
struct texture{
float x; // x component of texture
float y; // y component of texture
float z;
float w;  // optional component
};

 //structure for faces
struct faces{
int v;  // store vertex index
int n;  // store normal index
int t;  // store texture index
};


//------------ struct part------------
    //declare pointers for structs
    vertex *structvertex;  normal *structnormal; texture *structtexture; faces *structfaces;


    int num=0,num2=0,num3=0,num4=0; int temp[4];int factor=200;

    char *splitvertexToken;

    double temporaryvertexArray[3],temporaryVNArray[3],temporaryVTArray[3];int temporaryIndexArray[18];
    int y=0;

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


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(15.0,15.0,60.0,0.0,0.0,0.0,0.0,1.0,0.0);
   //gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here
    glTranslatef(0.0,0.0,zoom);
    glRotated(up,1,0,0);
    glRotated(rot,0,1,0);


        int i;
        glPointSize(2.0);
        glBegin(GL_TRIANGLES);


		for(i=0;i<num4;i=i+3)
		{

        glNormal3f(structnormal[structfaces[i].n].x,structnormal[structfaces[i].n].y,structnormal[structfaces[i].n].z);
		glVertex3f(structvertex[structfaces[i].v].x,structvertex[structfaces[i].v].y,structvertex[structfaces[i].v].z);

		glNormal3f(structnormal[structfaces[i+1].n].x,structnormal[structfaces[i+1].n].y,structnormal[structfaces[i+1].n].z);
		glVertex3f(structvertex[structfaces[i+1].v].x,structvertex[structfaces[i+1].v].y,structvertex[structfaces[i+1].v].z);

		glNormal3f(structnormal[structfaces[i+2].n].x,structnormal[structfaces[i+2].n].y,structnormal[structfaces[i+2].n].z);
		glVertex3f(structvertex[structfaces[i+2].v].x,structvertex[structfaces[i+2].v].y,structvertex[structfaces[i+2].v].z);

		}
		glEnd();


    glutSwapBuffers();
}
void testGetFile() {

    //initial allocation of memory using malloc for the 4 structs
    structvertex=(vertex *) malloc(sizeof(vertex) );
    structnormal=(normal *) malloc(sizeof(normal) );
    structtexture=(texture *) malloc(sizeof(texture) );
    structfaces=(faces *) malloc(sizeof(faces) );

    //--------------------------------------------------------------------------------
    // open file
    FILE *fp = fopen("ateneam.obj", "r");
    size_t len = 255;
    //malloc memory for line, if not, segmentation fault
    char *line = (char*)malloc(sizeof(char) * len);

    // check if file exist (and you can open it) or not
    if (fp == NULL) {
        printf("can open file !");
        return;
    }

    //array starting
    while(fgets(line, len, fp) != NULL)
    {
        splitvertexToken=NULL;
        splitvertexToken=strtok(line," ");

        //case1: only vertex rows
       if(strcmp(splitvertexToken,"v")==0)
        {
                while (splitvertexToken != NULL)
                {   //the x y z coordinates of each vertex is stored in array temporary vertexArray
                    temporaryvertexArray[y]=atof(splitvertexToken);
                    y++;
                    splitvertexToken = strtok (NULL, " \n");
                }

               structvertex[num].x=temporaryvertexArray[1]/200;
               structvertex[num].y=temporaryvertexArray[2]/200;
               structvertex[num].z=temporaryvertexArray[3]/200;
               structvertex[num].w=1.0;


                num++;//very important coz vertexarray[0] has x y z w, vertexarray[1] has x y z w and so on..

                //very important step: reinitialise y=0 after every line reading of vertex
                y=0;

                //reallocate memory for struct vertex
                structvertex=(vertex *)realloc(structvertex,(num+1)*sizeof(vertex));

        }

        //case2: only vn rows
        else if(strcmp(splitvertexToken,"vn")==0)
        {
             while (splitvertexToken != NULL)
                {   //the x y z coordinates of each vertex is stored in array temporaryvertexArray
                    temporaryVNArray[y]=atof(splitvertexToken);
                    y++;
                    splitvertexToken = strtok (NULL, " \n");
                }


                structnormal[num2].x=temporaryVNArray[1];
                structnormal[num2].y=temporaryVNArray[2];
                structnormal[num2].z=temporaryVNArray[3];
                structnormal[num2].w=1.0;

                num2++;

                //very important step: reinitialise y=0 after every line reading of VN
                y=0;

                //reallocate the memory for structnormal
                structnormal=(normal *)realloc(structnormal,(num2+1)*sizeof(normal));

        }

        //case3: only vt rows
        else if(strcmp(splitvertexToken,"vt")==0)
        {
           while (splitvertexToken != NULL)
                {   //the x y z coordinates of each vertex is stored in array temporaryvertexArray
                    temporaryVTArray[y]=atof(splitvertexToken);
                    y++;
                    splitvertexToken = strtok (NULL, " \n");
                }

                 structtexture[num3].x=temporaryVTArray[1];
                 structtexture[num3].y=temporaryVTArray[2];
                 structtexture[num3].z=temporaryVTArray[3];
                 structtexture[num3].w=1.0;

                num3++;

                //very important step: reinitialise y=0 after every line reading of vT
                y=0;

                //reallocate the memory for structtexture
                structtexture=(texture *)realloc(structtexture,(num3+1)*sizeof(texture));

        }


        //case4: only f rows
        else if(strcmp(splitvertexToken,"f")==0)
        {

          while (splitvertexToken != NULL)
                {   //the x y z coordinates of each vertex is stored in array temporaryvertexArray
                    temporaryIndexArray[y]=atoi(splitvertexToken);
                    y++;
                    splitvertexToken = strtok (NULL, " /");
                }

         /*very important to reallocate in the begining for faces only before storing because i am accessing 3 next blocks
          of struct in 1st iteration itself so make sure that 3 blocks are there and not 1 block*/
        /*reallocate memory for faces and its num4+3 because faces have 9 values to be read(3 at a time 3*3)*/
        structfaces=(faces *)realloc(structfaces,(num4+3)*sizeof(faces));


        //store values to structfaces
        structfaces[num4].v =temporaryIndexArray[1]-1;
        structfaces[num4].t=temporaryIndexArray[2]-1;
        structfaces[num4].n=temporaryIndexArray[3]-1;

		structfaces[num4+1].v=temporaryIndexArray[4]-1;
		structfaces[num4+1].t=temporaryIndexArray[5]-1;
		structfaces[num4+1].n=temporaryIndexArray[6]-1;

		structfaces[num4+2].v=temporaryIndexArray[7]-1;
		structfaces[num4+2].t=temporaryIndexArray[8]-1;
		structfaces[num4+2].n=temporaryIndexArray[9]-1;

        num4+=3;

        y=0;
        }

    }//while ends

     free(line);
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
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
         case GLUT_KEY_LEFT:
                rot=rot+1;
                break;
        case GLUT_KEY_RIGHT:
                rot=rot-1;
                break;
        case GLUT_KEY_END:
                zoom=zoom+1;
                break;
        case GLUT_KEY_HOME:
                zoom=zoom-1;
                break;
        case GLUT_KEY_UP:
                up=up+1;
                break;
        case GLUT_KEY_DOWN:
                up=up-1;
                break;

   }
  glutPostRedisplay();
}


static void idle(void)
{

    // Don't need a loop
    glutPostRedisplay();
}



void mouse(int btn, int state, int x, int y){

    float scale = 54*(Wwidth/Wheight);

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){

               // get new mouse coordinates for x,y
               // use scale to match right
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
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 5");
    init();
    glutReshapeFunc(resize);

    testGetFile();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}