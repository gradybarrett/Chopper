#include "chopper.h"
#include <iostream>
using std::cout;
using std::endl;

chopper::chopper(): topRotorAngle(0), tailRotorAngle(0),
heading(-90), topRotorSpeed(0), tailRotorSpeed(0), pitchAngle(0),
cockpitAndTail(3.0, 150, 150), tail(1.3, .4, 7, 150, 150),
rotorBlade(.3, .3, 6, 150, 150), rotorBladeHousing(.32, .32, .5, 150, 150),
tailRotorBlade(.1, .1, 1.8, 150, 150)
{
}

void chopper::update(){
    //update angles
    clock.update();

    topRotorAngle = topRotorAngle+(clock.deltaT())*topRotorSpeed;
    tailRotorAngle = tailRotorAngle+(clock.deltaT())*tailRotorSpeed;

    if(topRotorAngle>=360)
        topRotorAngle = topRotorAngle-360;
    if(tailRotorAngle>=360)
        tailRotorAngle = topRotorAngle-360;
}

/*
 * Draw the cockpit, tail and rotor blade housings
 */
void chopper::drawGL(){
    glColor3f(1.0f,1.0f,0.0f);

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    cockpitAndTail.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(0,0,2);
    glScaled(.7,1,1);
    tail.drawGL();
    glPopMatrix();

    glColor3f(0.0f,0.0f,1.0f);
    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(0,0,9.6);
    glScaled(.07,.3,.3);
    cockpitAndTail.drawGL();
    glPopMatrix();

    glColor3f(.2f,0.2f,0.2f);

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(0,3.38,0);
    glRotated(90,1,0,0);
    rotorBladeHousing.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(.2,0,9.6);
    glRotated(90,0,1,0);
    glScaled(.3,.3,.7);
    rotorBladeHousing.drawGL();
    glPopMatrix();

    drawRotorsGL();
}

/*
 * Draw the rotors
 */
void chopper::drawRotorsGL(){

    glColor3f(1.0f,0.0f,0.0f);

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(.5,0,9.6);
    glRotated(tailRotorAngle,1,0,0);
    glScaled(.5,1,1);
    tailRotorBlade.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(.5,0,9.6);
    glRotated(tailRotorAngle+120,1,0,0);
    glScaled(.5,1,1);
    tailRotorBlade.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(.5,0,9.6);
    glRotated(tailRotorAngle+240,1,0,0);
    glScaled(.5,1,1);
    tailRotorBlade.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(0,3.3,0);
    glRotated(topRotorAngle,0,1,0);
    glScaled(1,.5,1);
    rotorBlade.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(0,3.3,0);
    glRotated(topRotorAngle+120,0,1,0);
    glScaled(1,.5,1);
    rotorBlade.drawGL();
    glPopMatrix();

    glPushMatrix();
    glRotated(heading,0,1,0);
    glRotated(pitchAngle,1,0,0);
    glTranslated(0,3.3,0);
    glRotated(topRotorAngle+240,0,1,0);
    glScaled(1,.5,1);
    rotorBlade.drawGL();
    glPopMatrix();
}

void chopper::setHeading(double newHeading){
    heading = newHeading;
}

void chopper::setTopRotorSpeed(double newSpeed){
    topRotorSpeed = newSpeed;
}

void chopper::setTailRotorSpeed(double newSpeed){
    tailRotorSpeed = newSpeed;
}

void chopper::setPitchAngle(double newAngle){
    pitchAngle = newAngle;
}
