#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    gamewindow g;
    g.setWindowTitle("Game");
    g.resize(300, 300);
    g.move(20,20);
    g.show();

    
    return a.exec();
}
