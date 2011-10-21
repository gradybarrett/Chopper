#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <GL/glew.h> //include GLEW
#include <QGLWidget>
#include <glm/glm.hpp>
#include <QTimer>
#include "animationclock.h"
#include "chopper.h"
#include "choppercontrol.h"

/**
  * This class handles primary interactions with the OpenGL
  * pipeline.
  */
class GLCanvas : public QGLWidget
{
    Q_OBJECT
private:
    /*
     *Chopper control object for user interactions with the GUI sliders
     */
    ChopperControl control;

    /*
     * Timer for use in animating the rotors
     */
    QTimer *timer;

    /*
     * Chopper object for acessing chopper data
     */
    chopper chop;

public slots:
    /*
     * Slots to recieve the signals from the sliders on the GUI
     */
    void headingChanged(int);
    void pitchChanged(int);
    void topRotorSpeedChanged(int);
    void tailRotorSpeedChanged(int);
    /*
     * Slot to recieve the signal from the clock for animation
     */
    void timeout();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

public:
    GLCanvas(const QGLFormat &, QWidget * parent = 0);
};

#endif // GLCANVAS_H
