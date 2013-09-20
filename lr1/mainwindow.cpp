#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtGui>
#include <math.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/gl.h>

#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    GLfloat light_col[] = {1,1,1};

   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);



   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
   //glEnable(GL_LIGHTING);




   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


    float posx=0.0;
    float posy=0.0;
    float posz=0.0;
    glBegin(GL_LINES);

    float sizex=0.2;
    float sizey=0.2;

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

    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
