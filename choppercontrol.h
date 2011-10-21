#ifndef CHOPPERCONTROL_H
#define CHOPPERCONTROL_H

#include <QWidget>

/**
  * This class provides all information for interacting with
  * the GUI sliders.
  */
class ChopperControl : public QWidget
{
    Q_OBJECT

signals:
    /*
     *Signals to be connected to the sliders in the chopper GUI.
     */
    void headingChanged(int);
    void pitchChanged(int);
    void topRotorSpeedChanged(int);
    void tailRotorSpeedChanged(int);

public:
    ChopperControl( QWidget * parent = 0);

};

#endif // CHOPPERCONTROL_H
