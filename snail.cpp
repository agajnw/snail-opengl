/*
 * GKOM Lab. 3: OpenGL
 * Slimak
 */

#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <iostream>
#include "glut.h"

#define ILUT_USE_OPENGL
#include "il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#define PI 3.14

double camera_angle_h = 0.0;
double camera_angle_v = 0.0;
double angle = 45.0, shift = 0.0, zoom = -40.0;
bool mouseLeftDown = false, mouseMiddleDown = false, mouseRightDown = false;
float cameraAngleX = 20.0, cameraAngleY = 20.0;
float mouseX = 0.0, mouseY = 0.0;
float cameraDistance = 0.0, light = 0.0;

GLuint textures[10];
GLuint bg_texture[6];


void init()
{
    GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

    bg_texture[0] = ilutGLLoadImage((wchar_t*)"textures/down.jpg");
    bg_texture[1] = ilutGLLoadImage((wchar_t*)"textures/sky.jpg");
    bg_texture[2] = ilutGLLoadImage((wchar_t*)"textures/side1.jpg");
    bg_texture[3] = ilutGLLoadImage((wchar_t*)"textures/side2.jpg");
    bg_texture[4] = ilutGLLoadImage((wchar_t*)"textures/side3.jpg");
    bg_texture[5] = ilutGLLoadImage((wchar_t*)"textures/side4.jpg");

    textures[0] = ilutGLLoadImage((wchar_t*)"textures/wood.jpg");
    textures[1] = ilutGLLoadImage((wchar_t*)"textures/snail.jpg");
    textures[2] = ilutGLLoadImage((wchar_t*)"textures/buckHead.jpg");
    textures[3] = ilutGLLoadImage((wchar_t*)"textures/bodyFront.jpg");
    textures[4] = ilutGLLoadImage((wchar_t*)"textures/wing.jpg");

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable( GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void displayLight()
{
    GLfloat ambient[] = {0.2+light, 0.2+light, 0.2+light, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    GLfloat diffuse[]= {0.7+light, 0.7+light,0.7+light, 1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    GLfloat light_pos[] = {0.0, 200.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION,light_pos);

}

void background()
{
    int size = 60;

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);

    glColor4f(1, 1, 1, 1);

    //Bottom bg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, bg_texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(-size, -size, -size);

    glTexCoord2f(0, 1);
    glVertex3f(size, -size, -size);

    glTexCoord2f(0, 0);
    glVertex3f(size, -size, size);

    glTexCoord2f(1, 0);
    glVertex3f(-size, -size, size);
    glEnd();
    glPopMatrix();

    //Top bg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, bg_texture[1]);
    glBegin(GL_QUADS);//LD, PD, PG, LG
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, -size);

    glTexCoord2f(0, 0);
    glVertex3f(size, size, -size);

    glTexCoord2f(0, 1);
    glVertex3f(size, size, size);

    glTexCoord2f(1, 1);
    glVertex3f(-size, size, size);
    glEnd();
    glPopMatrix();

    //Side1 bg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, bg_texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(size, size, size);

    glTexCoord2f(0, 0);
    glVertex3f(size, -size, size);

    glTexCoord2f(1, 0);
    glVertex3f(size, -size, -size);

    glTexCoord2f(1, 1);
    glVertex3f(size, size, -size);
    glEnd();
    glPopMatrix();

    //Side2 bg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, bg_texture[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-size, size, -size);

    glTexCoord2f(0, 0);
    glVertex3f(-size, -size, -size);

    glTexCoord2f(1, 0);
    glVertex3f(-size, -size, size);

    glTexCoord2f(1,1);
    glVertex3f(-size, size, size);
    glEnd();
    glPopMatrix();

    //Side3 bg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, bg_texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(-size, size, -size);

    glTexCoord2f(0, 1);
    glVertex3f(size, size, -size);

    glTexCoord2f(0, 0);
    glVertex3f(size, -size, -size);

    glTexCoord2f(1, 0);
    glVertex3f(-size, -size, -size);
    glEnd();
    glPopMatrix();

    //Side4 bg
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, bg_texture[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-size, size, size);

    glTexCoord2f(0, 0);
    glVertex3f(-size, -size, size);

    glTexCoord2f(1,0);
    glVertex3f(size, -size, size);

    glTexCoord2f(1,1);
    glVertex3f(size, size, size);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void displayRods(int frame)
{
    GLfloat x = 0, y = 0, z = 0;

    glPushMatrix();
    glScalef(0.2f, 0.2f, 0.2f);
    glTranslatef(60.0, -270.0, 5.0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    for(int i=0; i<70; i++)
    {
        glPushMatrix();
        glTranslatef(-x, y, z);
        glColor3f(0, 1, 0);
        glutSolidSphere(-0.01f*i+3, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(10+x, y, z);
        glColor3f(0,1,0);
        glutSolidSphere(-0.01f*i+3, 10, 10);
        glPopMatrix();

        y += 0.5f;
        x += 0.3f;
        z -= 0.1f-(float)frame/1000;
    }

    glPushMatrix();
    glTranslatef(-x, y, z);
    glColor3f(0,1,0);
    glutSolidSphere(-0.01f*i+1, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10+x, y, z);
    glColor3f(0,1,0);
    glutSolidSphere(-0.01f*i+1, 10, 10);
    glPopMatrix();

    glPopMatrix();
}


void displayBody(int puff)
{
    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricTexture(sphere, GL_TRUE);
    glPushMatrix();
    glTranslatef(-10.0, -55.5, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glScalef(4.7+(float)puff/500, 1.3, 0.8);
    gluSphere(sphere, 5.5, 50, 50);
    glPopMatrix();
}

void displayShell(int frame)
{
    GLfloat x,y,z,angle;

    glPushMatrix();
    glTranslatef(-14.0, -42.0, -5.0 );
    glRotatef(-50-(float)frame/20, 0.0f, 0.0f, 1.0f);
    glRotatef(185, 1.0f, 0.0f, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);
    z = -50.0f;

    for(angle = 0.0f; angle <= 2*(PI)*3.0f; angle += 0.08f)
    {
        x = angle*2.0f*sin(angle);
        y = angle*2.0f*cos(angle);

        glPushMatrix();
        glTranslatef(x,y,z);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glutSolidSphere(1.0f*angle+20, 10, 10);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x,y,-50-z);
        glColor3f(1, 0, 0);
        glutSolidSphere(1.0f*angle+20, 10, 10);
        glPopMatrix();
        z += 0.1f;
    }
    glPopMatrix();

}
void displayObjects(int frame)
{
    int puff = frame % 100;
    if(puff>50)
        puff = 100-puff;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    displayBody(puff);
    displayShell(puff);
    displayRods(puff);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void reshape(GLsizei w, GLsizei h)
{
    if(h>0 && w>0)
    {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 200.0);

        glTranslatef(shift, angle, zoom);
        glMatrixMode(GL_MODELVIEW);
    }
}

void Keyboard( int key, int x, int y )
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
        light -= 0.1;
        break;
    case GLUT_KEY_UP:
        light += 0.1;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
            mouseLeftDown = true;
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
            mouseRightDown = true;
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}

void motion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }

    if(mouseRightDown)
    {
        cameraDistance -= (y - mouseY) * 0.2f;
        mouseY = y;
    }
}

void display()
{
    static float frame_no = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(frame_no<500)
      frame_no++;
    else
      frame_no = 0;

    glRotated(camera_angle_v/100, 1.0, 0.0, 0.0);
    glRotated(camera_angle_h/100, 0.0, 1.0, 0.0);

    displayLight();

    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
    glTranslatef(0, 0, -cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);
    glRotatef(cameraAngleY, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    background();
    displayObjects(frame_no);

    glMatrixMode(GL_PROJECTION);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(1920/6, 1080/6);
    glutInitWindowSize(1920/2, 1080/2);

    glutCreateWindow("GKOM - Snail");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc(Keyboard);

    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);

    init();

    glutMainLoop();

    return 0;
}
