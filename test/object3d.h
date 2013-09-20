#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <QtOpenGL/QGLWidget>
#include "object3d.h"

class object3D
{
protected:
    float posx;
    float posy;
    float posz;
public:
    void draw();
    void moveto(float x,float y,float z);
    object3D(float x,float y,float z);
};

#endif // OBJECT3D_H
