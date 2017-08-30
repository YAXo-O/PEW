#include <QMouseEvent>
#include <QIntValidator>
#include <QPainter>
#include <limits>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pewwidget.h"
#include "worldinfo.h"
#include "Model/simpletestmodel.h"
#include "pointtransformations.h"
#include "UIManager/nodecolourmanager.h"
#include "WidgetUtilities/Parsers/colourfileparsing.h"
#include "UIManager/arrowdrawingmanager.h"
#include <QGraphicsBlurEffect>

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
    tline->setConnections(ui->timeline_slider, ui->current_frame_line);
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
    SimpleTestModel *sphere = new SimpleTestModel();
    WorldInfo::getInstance().registerObject(sphere);
    sphere = new SimpleTestModel({0, -100, 0}, 60);
    sphere->setCol(Qt::blue);
    WorldInfo::getInstance().registerObject(sphere);
}
