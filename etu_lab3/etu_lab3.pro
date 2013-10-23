#-------------------------------------------------
#
# Project created by QtCreator 2013-10-23T20:37:25
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = etu_lab3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mesh.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    mesh.h \
    game.h

FORMS    += mainwindow.ui
