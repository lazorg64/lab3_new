#include "game.h"

using namespace std;


game::game(QWidget* parent) : QGLWidget(parent)
{
    xRot=-45; yRot=0; zRot=30; zTra=0; nSca=0.3;
    mesh * a;

    a=new mesh(0.0,0,0);
    a->loadModel("C:\\Users\\lazorg\\Documents\\GitHub\\game\\game\\iPhone5.obj");
    a->LoadGLTextures();
    drawlist.push_back(a);


}

void game::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.1f);
    glClearDepth(20.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    GLfloat light_col[] = {1,1,1};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void game::resizeGL(int nWidth, int nHeight)
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

void game::paintGL()
{
    glShadeModel(GL_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(nSca, nSca, nSca);
    glTranslatef(0.0f, zTra, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    std::vector<mesh*>::iterator it=drawlist.begin();
    while(it!=drawlist.end())
    {
        it.operator *()->textureID[0]=this->bindTexture(it.operator *()->pixmap1, GL_TEXTURE_2D );
        it.operator *()->textureID[1]=this->bindTexture(it.operator *()->pixmap2, GL_TEXTURE_2D );
        it.operator *()->draw(this);
        it++;
    }
}


void game::drawAxis()
{
    glBindTexture(GL_TEXTURE_2D,NULL);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glVertex3f( 1.0f,  0.0f,  0.0f);
    glVertex3f(-1.0f,  0.0f,  0.0f);
    glColor4f(0.00f, 1.00f, 0.00f, 1.0f);
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 0.0f, -1.0f,  0.0f);
    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    glVertex3f( 0.0f,  0.0f,  1.0f);
    glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void game::keyPressEvent(QKeyEvent* pe)
{
   switch (pe->key())
   {
      case Qt::Key_W:
      break;
   }
   updateGL();
}


void game::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void game::mouseReleaseEvent(QMouseEvent* pe)
{

}

void game::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL();
}


void game::wheelEvent(QWheelEvent* pe)
{
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL();
}

void game::loadLandscape()
{
    glBegin(GL_QUADS);
    glTexCoord2d(1.0,-1.0);
    glVertex3f(1.0,-1.0,0);

    glTexCoord2d(1.0,1.0);
    glVertex3f(1.0,1.0,0);

    glTexCoord2d(-1.0,1.0);
    glVertex3f(-1.0,1.0,0);

    glTexCoord2d(-1.0,-1.0);
    glVertex3f(-1.0,-1.0,0);




    glEnd();

}
void game::scale_plus()
{
   nSca = nSca*1.1;
}
void game::scale_minus()
{
   nSca = nSca/1.1;
}
void game::rotate_up()
{
   xRot += 1.0;
}
void game::rotate_down()
{
   xRot -= 1.0;
}
void game::rotate_left()
{
   zRot += 1.0;
}
void game::rotate_right()
{
   zRot -= 1.0;
}
void game::translate_down()
{
   zTra -= 0.05;
}
void game::translate_up()
{
   zTra += 0.05;

}
