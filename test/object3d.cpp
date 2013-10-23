#include "object3d.h"

object3D::object3D(float x,float y,float z)
{
    posx=x;
    posy=y;
    posz=z;
    draw();
}

void object3D::draw()
{

    float sizex=0.2;
    float sizey=0.2;

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.1, 0.9);

    glVertex3f(posx-sizex, posy+sizey, posz);
    glVertex3f(posx-sizex, posy-sizey, posz);
    glVertex3f(posx+sizex, posy-sizey, posz);
    glVertex3f(posx+sizex, posy+sizey, posz);

    glVertex3f(posx+sizex, posy+sizey, posz);
    glVertex3f(posx+sizex, posy-sizey, posz);
    glVertex3f(posx+sizex, posy-sizey, 0);
    glVertex3f(posx+sizex, posy+sizey, 0);

    glVertex3f(posx-sizex, posy-sizey, posz);
    glVertex3f(posx-sizex, posy-sizey, 0);
    glVertex3f(posx+sizex, posy-sizey, 0);
    glVertex3f(posx+sizex, posy-sizey, posz);

    glVertex3f(posx-sizex, posy-sizey, posz);
    glVertex3f(posx-sizex, posy+sizey, posz);
    glVertex3f(posx-sizex, posy+sizey, 0);
    glVertex3f(posx-sizex, posy-sizey, 0);

    glVertex3f(posx-sizex, posy+sizey, posz);
    glVertex3f(posx+sizex, posy+sizey, posz);
    glVertex3f(posx+sizex, posy+sizey, 0);
    glVertex3f(posx-sizex, posy+sizey, 0);

    glEnd();
}

void object3D::moveto(float x,float y,float z)
{
    posx=x;
    posy=y;
    posz=z;
}
