#-------------------------------------------------
#
# Project created by QtCreator 2013-09-20T14:22:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamewindow.cpp

HEADERS  += mainwindow.h \
    gamewindow.h

FORMS    += mainwindow.ui

QT += opengl
