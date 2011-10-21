#include "choppercontrol.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>

ChopperControl::ChopperControl(QWidget *parent ) :
        QWidget(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout();

    QGroupBox * groupBox = new QGroupBox("Chopper Controls");
    mainLayout->addWidget(groupBox);

    QVBoxLayout * layout = new QVBoxLayout();

    layout->addWidget(new QLabel("Chopper Heading (Degrees)"));
    QSlider * slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(-180);
    slider->setMaximum(180);
    slider->setTickInterval(30);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setValue(-90);
    layout->addWidget(slider);
    connect(slider,SIGNAL(sliderMoved(int)),this,SIGNAL(headingChanged(int)));

    layout->addWidget(new QLabel("Pitch (Degrees)"));
    slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(-45);
    slider->setMaximum(45);
    slider->setTickInterval(5);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setValue(0);
    layout->addWidget(slider);
    connect(slider,SIGNAL(sliderMoved(int)),this,SIGNAL(pitchChanged(int)));

    layout->addWidget(new QLabel("Top Rotor Speed (degrees/sec)"));
    slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(0);
    slider->setMaximum(1000);
    slider->setTickInterval(100);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setValue(10);
    layout->addWidget(slider);
    connect(slider,SIGNAL(sliderMoved(int)),this,SIGNAL(topRotorSpeedChanged(int)));

    layout->addWidget(new QLabel("Tail Rotor Speed (degrees/sec)"));
    slider = new QSlider(Qt::Horizontal,this);
    slider->setMinimum(0);
    slider->setMaximum(1000);
    slider->setTickInterval(100);
    slider->setValue(10);
    slider->setTickPosition(QSlider::TicksBelow);
    layout->addWidget(slider);
    connect(slider,SIGNAL(sliderMoved(int)),this,SIGNAL(tailRotorSpeedChanged(int)));

    layout->addStretch();

    groupBox->setLayout(layout);

    this->setLayout(mainLayout);
}
