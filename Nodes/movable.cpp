#include <QMouseEvent>
#include <QLayout>
#include "movable.h"
#include "../nodeview.h"
#include "../worldinfo.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif


Movable::Movable(QWidget *parent) : QWidget(parent), paramPanel(nullptr)
{
}

void Movable::setKeyName(const QString &_keyName)
{
    keyName = _keyName;
}

void Movable::setKeyName(const QString &&_keyName)
{
    keyName = _keyName;
}

QString Movable::getKeyName()
{
    return keyName;
}

void Movable::connectToViewer(const NodeView *viewer)
{
    connect(this, SIGNAL(becameActive(Movable *)), viewer, SLOT(movableSelected(Movable *)));
}

void Movable::disconnectFromViewer()
{
    disconnect(this, SIGNAL(becameActive(Movable *)));
}

int Movable::type()
{
    return movableBase;
}

void Movable::mouseMoveEvent(QMouseEvent *me)
{
    if(me->buttons() & Qt::LeftButton)
    {
        if(me->modifiers() & Qt::ControlModifier && parent())
        {
            // Moving current node
            move(mapToParent(me->pos()) - clickVector);
        }
    }

    QWidget::mouseMoveEvent(me);
}

void Movable::mousePressEvent(QMouseEvent *me)
{
    becomeActive();
    clickVector = me->pos();

    QWidget::mousePressEvent(me);
}

QWidget *Movable::getParamPanel() const
{
    return paramPanel;
}

void Movable::setParamPanel(QWidget *value)
{
    paramPanel = value;
}

void Movable::displayPropertiesPanel() const
{
    if(paramPanel)
    {
        PEWWidget *paramsView = WorldInfo::getInstance().getNodeParams();
        if(paramsView)
        {
            paramsView->layout()->addWidget(paramPanel);
            paramPanel->show();
        }
    }
}

void Movable::hidePropertiesPanel()
{
    if(paramPanel)
    {
        PEWWidget *paramsView = WorldInfo::getInstance().getNodeParams();
        if(paramsView)
        {
            paramPanel->hide();
            paramsView->layout()->removeWidget(paramPanel);
        }
    }
}

void Movable::becomeInactive()
{
    hidePropertiesPanel();
}

void Movable::becomeActive()
{
    emit becameActive(this);
    raise();

    displayPropertiesPanel();
}
