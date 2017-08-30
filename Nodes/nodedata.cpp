#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QVector2D>
#include <QAbstractScrollArea>
#include <QVBoxLayout>
#include "nodedata.h"
#include "../UIManager/nodecolourmanager.h"
#include "../WidgetUtilities/Parsers/colourfileparsing.h"

#include <QDebug>

NodeData::NodeData(QWidget *parent) : Movable(parent),
    borderColor(Qt::green), radius(40), offset(5),
    varName("Unnamed"), varDescription(""), basicDataProps(new DataProperties)
{
    int size = radius*2 + offset*2;
    resize(size, size);

    setParamPanel(new QAbstractScrollArea);
    getParamPanel()->setLayout(new QVBoxLayout);
    getParamPanel()->layout()->addWidget(basicDataProps);

    basicDataProps->setNameInput("Unnamed");
    basicDataProps->setNameLabel("Variable name");
    basicDataProps->setDescriptionLabel("Variable description");
    basicDataProps->setGroupName("Basic variable properties");

    setConnections();
}

NodeData::~NodeData()
{
}

void NodeData::setConnections()
{
    connect(basicDataProps, SIGNAL(nameChanged(QString)), this, SLOT(changeName(QString)));
    connect(basicDataProps, SIGNAL(descriptionChanged(QString)), this, SLOT(changeDescriprion(QString)));
}

const void *NodeData::getData() const
{
    return nullptr;
}

void NodeData::setData(const void *)
{
}

const char *NodeData::dataType() const
{
    return "NodeData";
}

const char *NodeData::dataType_s()
{
    return "NodeData";
}

void NodeData::setBorderColour(QColor &colour)
{
    borderColor = colour;
}

void NodeData::setBorderColour(QColor &&colour)
{
    borderColor = colour;
}

QColor NodeData::getBorderColour() const
{
    return borderColor;
}

int NodeData::type()
{
    return movableData;
}

// Visual stuff goes here
void NodeData::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);

    p.setPen(borderColor);
    p.setBrush(QBrush(Qt::darkGray, Qt::SolidPattern));
    p.drawEllipse(offset, offset, radius*2, radius*2);
    p.drawText(rect(), Qt::AlignCenter ,varName);

    p.end();

    Movable::paintEvent(pe);
}

void NodeData::mouseMoveEvent(QMouseEvent *me)
{
    // Check if we are inside a circle
    if(QVector2D(me->pos() - QPoint(width()/2, height()/2)).length() >= radius)
        QWidget::mouseMoveEvent(me);
    else
        Movable::mouseMoveEvent(me);
}

void NodeData::setRadius(int newRadius)
{
    radius = newRadius;
}

void NodeData::setOffset(int newOffset)
{
    offset = newOffset;
}

int NodeData::getRadius() const
{
    return radius;
}

int NodeData::getOffset() const
{
    return offset;
}

void NodeData::setVarName(const QString &newName)
{
    varName = newName;
}

void NodeData::setVarName(const QString &&newName)
{
    varName = newName;
}

void NodeData::setVarDescription(const QString &newDescription)
{
    varDescription = newDescription;
}

void NodeData::setVarDescription(const QString &&newDescription)
{
    varDescription = newDescription;
}

const QString &NodeData::getVarName() const
{
    return varName;
}

const QString &NodeData::getVarDescription() const
{
    return varDescription;
}

void NodeData::setUpBorder()
{
    NodeColourManager *man = nullptr;
    ColourFileParsing parser(configPath + "dataColour.ds");
    NodeColourManager::getInstance(man, &parser);
    man->setColour(this);
}

void NodeData::setRealKeyName(const QString &name)
{
    realKeyName = name;
}

void NodeData::setRealKeyName(const QString &&name)
{
    realKeyName = name;
}

QString NodeData::getRealKeyName()
{
    return realKeyName;
}

void NodeData::visualPrepare(const QString &name)
{
    setRealKeyName(name);
    setKeyName(getRealKeyName());
    setUpBorder();
}

void NodeData::visualPrepare(const QString &&name)
{
    visualPrepare(name);
}

void NodeData::becomeInactive()
{
    Movable::becomeInactive();

    setKeyName(getRealKeyName());
    setUpBorder();
    repaint();
}

void NodeData::becomeActive()
{
    Movable::becomeActive();

    setKeyName("selected");
    setUpBorder();
    repaint();
}

void NodeData::changeName(const QString &name)
{
    varName = name;
    repaint();
}

void NodeData::changeDescriprion(const QString &description)
{
    varDescription = description;
}
