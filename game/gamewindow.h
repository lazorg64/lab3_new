#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H


#include <QtOpenGL/QGLWidget>


class gamewindow : public QGLWidget
{
protected:
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;

public:
    gamewindow(QWidget* parent=0);
    void initGL();
    void paintGL();
    void drawAxis();
    void resizeGL(int nWidth, int nHeight);
};

#endif // GAMEWINDOW_H
