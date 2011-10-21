#include "mainwindow.h"
#include "glcanvas.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Chopper 4!");

    QGLFormat fmt;
    fmt.setVersion(4,1);
    fmt.setAlpha(true);
    fmt.setProfile(QGLFormat::CompatibilityProfile);

    QWidget * centralWidget = new QWidget(this);
    ChopperControl * control = new ChopperControl(centralWidget);
    QHBoxLayout * layout = new QHBoxLayout();
    GLCanvas *can = new GLCanvas(fmt, centralWidget);
    layout->addWidget(can);
    layout->addWidget(control);
    centralWidget->setLayout(layout);

    this->setCentralWidget(centralWidget);

    //Connect all sliders on the GUI to the slots
    connect(control,SIGNAL(headingChanged(int)), can, SLOT(headingChanged(int)));
    connect(control,SIGNAL(pitchChanged(int)), can, SLOT(pitchChanged(int)));
    connect(control,SIGNAL(tailRotorSpeedChanged(int)), can, SLOT(tailRotorSpeedChanged(int)));
    connect(control,SIGNAL(topRotorSpeedChanged(int)), can, SLOT(topRotorSpeedChanged(int)));
}

MainWindow::~MainWindow()
{

}
