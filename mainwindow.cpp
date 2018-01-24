#include <QMouseEvent>
#include <QIntValidator>
#include <QPainter>
#include <limits>
#include <QGraphicsBlurEffect>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pewwidget.h"
#include "worldinfo.h"
#include "pointtransformations.h"
#include "UIManager/nodecolourmanager.h"
#include "WidgetUtilities/Parsers/colourfileparsing.h"
#include "UIManager/arrowdrawingmanager.h"

#include "CompulsorySceneObjects/baselight.h"
#include "Model/wireframemesh.h"
#include "Model/wireframemeshinstance.h"
#include "WidgetUtilities/Parsers/objfileparser.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), tline(new Timeline)
{
    ui->setupUi(this);

    setConnections();
    setValidators();

    WorldInfo::getInstance().setNodeView(ui->node_view_peww);
    WorldInfo::getInstance().setViewport(ui->viewport_peww);
    WorldInfo::getInstance().setNodeParams(ui->node_params_peww);
    prepareScene();

    ui->node_view_peww->setGraphicsEffect(new ArrowDrawingManager(ui->node_view_peww));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tline;

    NodeColourManager *man;
    NodeColourManager::getInstance(man, nullptr);
    if(man)
        delete man;
}

void MainWindow::receivedActivated(PEWWidget *wid)
{
    emit becameActiveSignal(wid);
}

void MainWindow::mousePressEvent(QMouseEvent *pe)
{
    emit becameActiveSignal(nullptr);

    QMainWindow::mousePressEvent(pe);
}

void MainWindow::setConnections()
{
    connectWidgets();
    WorldInfo &info = WorldInfo::getInstance();
    tline->setConnections(ui->timeline_slider, ui->current_frame_line, ui->simulate_pb);
    connect(tline, SIGNAL(frameChanged(uint)), &info, SLOT(changeCurrentFrame(uint)));
    connect(&info, SIGNAL(currentFrameChanged(uint)), tline, SLOT(setCurrentFrame(uint)));
}

void MainWindow::connectWidgets()
{
    // Many-to-many connection

    // Subscribing to change focus
    connect(ui->node_view_peww, SIGNAL(becameActive(PEWWidget*)), this, SLOT(receivedActivated(PEWWidget*)));
    connect(ui->node_params_peww, SIGNAL(becameActive(PEWWidget*)), this, SLOT(receivedActivated(PEWWidget*)));
    connect(ui->viewport_peww, SIGNAL(becameActive(PEWWidget*)), this, SLOT(receivedActivated(PEWWidget*)));

    // Subscribing widgets to me(retranslating signal)
    connect(this, SIGNAL(becameActiveSignal(PEWWidget*)), ui->node_view_peww, SLOT(receiveActive(PEWWidget*)));
    connect(this, SIGNAL(becameActiveSignal(PEWWidget*)), ui->node_params_peww, SLOT(receiveActive(PEWWidget*)));
    connect(this, SIGNAL(becameActiveSignal(PEWWidget*)), ui->viewport_peww, SLOT(receiveActive(PEWWidget*)));
}

void MainWindow::setValidators()
{
    ui->current_frame_line->setValidator(new QIntValidator(0, INT_MAX));
}

void MainWindow::prepareScene()
{
    WorldInfo &wifo = WorldInfo::getInstance();

    /*
    OBJFileParser parser;
    WireframeMesh *mesh = parser.load("./planes.obj");
    Material *mat = new Material();
    WireframeMeshInstance *m = new WireframeMeshInstance(mesh);
    m->changeMaterial(mat);
    wifo.registerObject(m);
    */


    wifo.changeEndFrame(2);
}
