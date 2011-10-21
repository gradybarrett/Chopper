#include "glcanvas.h"

#include <cstdio>
#include <cmath>

#include<QKeyEvent>
#include<QMouseEvent>

GLCanvas::GLCanvas(const QGLFormat & fmt, QWidget * parent):
        QGLWidget(fmt,parent)
{
    this->setMinimumSize(800,800);
    this->setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void GLCanvas::initializeGL() {

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if( GLEW_OK != err) {
        printf("Error initializing GLEW: %s\n",
             glewGetErrorString(err));
    }
    printf("Using GLEW: %s\n",
           glewGetString(GLEW_VERSION));


    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

    //unsigned byte (array of characters)
    const GLubyte * renderer = glGetString( GL_RENDERER );
    const GLubyte * vendor = glGetString( GL_VENDOR );
    const GLubyte * version = glGetString( GL_VERSION );

    printf("Renderer: %s\n", renderer);
    printf("Vendor: %s\n", vendor);
    printf("Version: %s\n", version);

    QGLFormat fmt = this->format();
    printf("Buffersize: (%d, %d, %d, %d)\n",
           fmt.redBufferSize(), fmt.greenBufferSize(),
           fmt.blueBufferSize(), fmt.alphaBufferSize());

    timer->start(10);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
}

void GLCanvas::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    chop.drawGL();
}

void GLCanvas::resizeGL(int w, int h) {

    glViewport( 0, 0, w, h );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12,12,-12,12,-12,12);
}

void GLCanvas::timeout(){
    chop.update();
    updateGL();
}

//Get the updated information from the GUI sliders and update
//the chopper drawing based on those values

void GLCanvas::headingChanged(int rotation){
    chop.setHeading(rotation);
}

void GLCanvas::pitchChanged(int rotation){
    chop.setPitchAngle(rotation);
}

void GLCanvas::topRotorSpeedChanged(int speed){
    chop.setTopRotorSpeed(speed);
}

void GLCanvas::tailRotorSpeedChanged(int speed){
    chop.setTailRotorSpeed(speed);
}
