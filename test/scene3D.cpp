
#include <QtGui>
#include <math.h>
#include "scene3D.h"
#include <vector>
#include "glm/glm/glm.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/gl.h>



using namespace std;

const static float pi=3.141593, k=pi/180;

GLfloat VertexArray[12][3];
GLfloat ColorArray[12][3];
GLubyte IndexArray[20][3];

GLfloat HeightMap[5][5];

Scene3D::Scene3D(QWidget* parent) : QGLWidget(parent)
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::initializeGL()
{
    GLfloat light_col[] = {1,1,1};
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);



   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

glEnable(GL_COLOR_MATERIAL);
   //glEnable(GL_LIGHTING);


   setHeightMap();

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
}

void Scene3D::resizeGL(int nWidth, int nHeight)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

   if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void Scene3D::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glScalef(nSca, nSca, nSca);
   glTranslatef(0.0f, zTra, 0.0f);
   glRotatef(xRot, 1.0f, 0.0f, 0.0f);
   glRotatef(yRot, 0.0f, 1.0f, 0.0f);
   glRotatef(zRot, 0.0f, 0.0f, 1.0f);

   drawAxis();
   drawFigure();
   //drawRect();
}

void Scene3D::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void Scene3D::mouseReleaseEvent(QMouseEvent* pe)
{

}

void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL();
}

void Scene3D::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL();
}

void Scene3D::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();
      break;

      case Qt::Key_Equal:
         scale_plus();
      break;

      case Qt::Key_Minus:
         scale_minus();
      break;

      case Qt::Key_Up:
         rotate_up();
      break;

      case Qt::Key_Down:
         rotate_down();
      break;

      case Qt::Key_Left:
        rotate_left();
      break;

      case Qt::Key_Right:
         rotate_right();
      break;

      case Qt::Key_Z:
         translate_down();
      break;

      case Qt::Key_X:
         translate_up();
      break;

      case Qt::Key_Space:
         defaultScene();
      break;

      case Qt::Key_Escape:
         this->close();
      break;
   }

   updateGL();
}

void Scene3D::scale_plus()
{
   nSca = nSca*1.1;
}

void Scene3D::scale_minus()
{
   nSca = nSca/1.1;
}

void Scene3D::rotate_up()
{
   xRot += 1.0;
}

void Scene3D::rotate_down()
{
   xRot -= 1.0;
}

void Scene3D::rotate_left()
{
   zRot += 1.0;
}

void Scene3D::rotate_right()
{
   zRot -= 1.0;
}

void Scene3D::translate_down()
{
   zTra -= 0.05;
}

void Scene3D::translate_up()
{
   zTra += 0.05;
}

void Scene3D::defaultScene()
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::drawAxis()
{
   glLineWidth(3.0f);

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);
      glVertex3f( 1.0f,  0.0f,  0.0f);
      glVertex3f(-1.0f,  0.0f,  0.0f);
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}


void Scene3D::getColorArray()
{
   for (int i=0; i<12; i++)
   {
      ColorArray[i][0]=0.1f*(qrand()%11);
      ColorArray[i][1]=0.1f*(qrand()%11);
      ColorArray[i][2]=0.1f*(qrand()%11);
   }
}
void Scene3D::setHeightMap()
{
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        {
            HeightMap[i][j]=(rand()%10)*0.05f;

        }
}




void Scene3D::drawFigure()
{
    float R=1;

    glBegin(GL_QUADS);  // draw a cube with 12 triangles

    glColor3f(0.5*R, 0.5*R, 0.0*R);

    glVertex3f(-1.0*R, 1.0*R, 0.0*R);
    glVertex3f(-1.0*R, -1.0*R, 0.0*R);


    glVertex3f(1.0*R, -1.0*R, 0.0*R);
    glVertex3f(1.0*R, 1.0*R, 0.0*R);









    glEnd();

    drawCube(0.0,0.0,0.3);



}

void Scene3D::drawCube(float x,float y,float h)
{


    float sizex=0.1;
    float sizey=0.1;

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.1, 0.9);

    glVertex3f(x-sizex, y+sizey, h);
    glVertex3f(x-sizex, y-sizey, h);
    glVertex3f(x+sizex, y-sizey, h);
    glVertex3f(x+sizex, y+sizey, h);

    glVertex3f(x+sizex, y+sizey, h);
    glVertex3f(x+sizex, y-sizey, h);
    glVertex3f(x+sizex, y-sizey, 0);
    glVertex3f(x+sizex, y+sizey, 0);

    glVertex3f(x-sizex, y-sizey, h);
    glVertex3f(x-sizex, y-sizey, 0);
    glVertex3f(x+sizex, y-sizey, 0);
    glVertex3f(x+sizex, y-sizey, h);

    glVertex3f(x-sizex, y-sizey, h);
    glVertex3f(x-sizex, y+sizey, h);
    glVertex3f(x-sizex, y+sizey, 0);
    glVertex3f(x-sizex, y-sizey, 0);

    glVertex3f(x-sizex, y+sizey, h);
    glVertex3f(x+sizex, y+sizey, h);
    glVertex3f(x+sizex, y+sizey, 0);
    glVertex3f(x-sizex, y+sizey, 0);









    glEnd();
}

