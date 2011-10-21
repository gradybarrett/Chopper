#-------------------------------------------------
#
# Project created by QtCreator 2011-02-23T08:38:56
#
#-------------------------------------------------
#Have to configure this when using opengl

QT       += core gui opengl #add opengl manually
CONFIG   += console #not ability to print to terminal but want to be able to do that,
                    #this allows printing debug messages out to console

TARGET = chopper
TEMPLATE = app

INCLUDEPATH += C:/OpenGL/include #Adding GLEW, this also includes GLM
LIBS += -LC:/OpenGL/lib -lglew32

SOURCES += main.cpp\
        mainwindow.cpp \
    glcanvas.cpp \
    animationclock.cpp \
    choppercontrol.cpp \
    cylinder.cpp \
    sphere.cpp \
    chopper.cpp


HEADERS  += mainwindow.h \
    glcanvas.h \
    animationclock.h \
    choppercontrol.h \
    cylinder.h \
    sphere.h \
    chopper.h
