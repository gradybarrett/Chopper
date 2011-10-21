/*
 *Name: Grady Barrett
 *Assignment: Lab #2
 *Title: Chopper 4!
 *Course: CSCE 412
 *Semester: Spring 2011
 *Instructor: David Wolff
 *Date: 3/30/11
 *Sources consulted: Dr. Wolff
 *Program description: Draws a chopper with animated rotors
 *                     and allows the user to change the
 *                     heading, pitch, tail rotor speed,
 *                     and main rotor speed.
 *Known Bugs: none
 *Creativity: none
 */

#ifndef CHOPPER_H
#define CHOPPER_H

#include <GL/glew.h>
#include <QGLWidget>
#include <glm/glm.hpp>
#include <GL/gl.h>

#include "animationclock.h"
#include "sphere.h"
#include "cylinder.h"

/**
  * This class draws the chopper, provides animation for
  * the rotor blades and provides set methods to
  * allow access to chopper information updated by the sliders
  * on the GUI.
  */
class chopper
{

private:
    /*
     *Clock object for rotor blade animation
     */
    AnimationClock clock;

    /*
     *Data for interaction with/animation of chopper
     */
    double topRotorAngle;
    double tailRotorAngle;
    double heading;
    double topRotorSpeed;
    double tailRotorSpeed;
    double pitchAngle;

    /*
     *Graphical object for drawing chopper
     */
    Sphere cockpitAndTail;
    Cylinder tail;
    Cylinder rotorBlade;
    Cylinder rotorBladeHousing;
    Cylinder tailRotorBlade;

    /**
     *Method to draw the rotor blades
     */
    void drawRotorsGL();

public:

    /**
     *Zero argument constructor for chopper class
     */
    chopper();

    /**
     *Method to update topRotorAngle and tailRotorAngle
     *and reset these angles if they are equal to or greater
     *that 360 degrees
     */
    void update();

    /**
     *Draws the cockpit, tail and rotor/chopper blade housings
     */
    void drawGL();

    /**
     *Set methods for private data fields
     */
    void setHeading(double);
    void setTopRotorSpeed(double);
    void setTailRotorSpeed(double);
    void setPitchAngle(double);

};

#endif // CHOPPER_H
