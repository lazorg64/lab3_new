#ifndef MESH_H
#define MESH_H
#include <vector>
#include "glm/glm/glm.hpp"
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>
#include <gl/GLU.h>
#include <math.h>
#include <QString>
#include <QImage>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class mesh
{

public:



    float x;
    float y;
    float z;
    float scale;
    QPixmap pixmap1;
    QPixmap pixmap2;
    GLuint	textureID[2];
    std::vector< glm::vec3> model;
    std::vector< glm::vec3> normals;
    std::vector < glm::vec2 > uvs;
    std::vector< unsigned int > vertexIndices, normalIndices;
    std::vector< unsigned int> uvIndices;
    std::vector< string> materials;

    mesh(float inx,float iny,float inz);
    void loadModel(const char * path);
     void LoadGLTextures();
    void draw(QGLWidget * parent);
};

#endif // MESH_H
