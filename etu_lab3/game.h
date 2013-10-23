#ifndef GAME_H
#define GAME_H
#include "mesh.h"

class game : public QGLWidget
{
private:
     GLfloat xRot;
     GLfloat yRot;
     GLfloat zRot;
     GLfloat zTra;
     GLfloat nSca;


     QPoint ptrMousePosition;
public:
    std::vector<mesh*> drawlist;
    game(QWidget* parent = 0);
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void drawAxis();
    void keyPressEvent(QKeyEvent* pe);
    void mousePressEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void loadLandscape();
    void wheelEvent(QWheelEvent* pe);


    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();

};

#endif // GAME_H
