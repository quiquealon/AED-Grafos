#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T18:04:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Grafos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    edge.cpp \
    graphwidget.cpp \
    node.cpp

HEADERS  += mainwindow.h \
    edge.h \
    graphwidget.h \
    node.h

FORMS    += mainwindow.ui
