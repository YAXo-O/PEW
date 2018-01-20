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
    tline->setConnections(ui->timeline_slider, ui->current_frame_line, ui->simulate_pb);
    connect(tline, SIGNAL(frameChanged(uint)), &(WorldInfo::getInstance()), SLOT(changeCurrentFrame(uint)));
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
    TextureManager &manager = wifo.textureManager();
    QImage &texture = manager.getTexture("./checker.jpg");

    OBJFileParser parser;
    WireframeMesh *mesh = parser.load("./planes.obj");
    WireframeMeshInstance *instance = new WireframeMeshInstance(mesh);
    instance->material().getDiffuse().setTexture(&texture);
    instance->material().getAmbient().setTexture(&texture);
    instance->material().getAmbient().setIndex(.05);
    wifo.registerObject(instance);

    BaseLight *light = new BaseLight({QVector3D(40, -100, 100), Qt::red, 6800}, nullptr);
    //BaseLight *backLight = new BaseLight({QVector3D(40, 100, 100), Qt::blue, 6800}, nullptr);
    wifo.registerObject(light);
    //wifo.registerObject(backLight);
}
