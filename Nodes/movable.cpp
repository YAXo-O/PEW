#include <QMouseEvent>
#include <QVBoxLayout>
#include "movable.h"
#include "../nodeview.h"
#include "../worldinfo.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif


Movable::Movable(QWidget *parent) : QWidget(parent), bDeletable(false), keyName("default"), paramPanel(new QScrollArea)
{
    setFocusPolicy(Qt::StrongFocus);
}

Movable::~Movable()
{
    if(paramPanel)
    {
        hidePropertiesPanel();
        delete paramPanel;
    }
    disconnectFromViewer();
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

void Movable::appendParamsWidget(QWidget *appendee)
{
    if(paramPanel->viewport()->layout())
        paramPanel->viewport()->layout()->addWidget(appendee);
    else
    {
        paramPanel->viewport()->setLayout(new QVBoxLayout());
        paramPanel->viewport()->layout()->addWidget(appendee);
    }
}

bool Movable::getDeletable() const
{
    return bDeletable;
}

void Movable::setDeletable(bool value)
{
    bDeletable = value;
}

void Movable::connectToViewer(const NodeView *viewer)
{
    connect(this, SIGNAL(becameActive(Movable *)), viewer, SLOT(movableSelected(Movable *)));
    connect(this, SIGNAL(killMe(Movable *)), viewer, SLOT(killMovable(Movable *)));
}

void Movable::disconnectFromViewer()
{
    disconnect(this, SIGNAL(becameActive(Movable *)));
}

void Movable::kill()
{
    disconnectFromViewer();

    emit killMe(this);
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
            parentWidget()->repaint();
        }
    }
    else
        repaint();

    QWidget::mouseMoveEvent(me);
}

void Movable::mousePressEvent(QMouseEvent *me)
{
    becomeActive();
    clickVector = me->pos();

    QWidget::mousePressEvent(me);
}

void Movable::enterEvent(QEvent *event)
{
    NodeView *view = WorldInfo::getInstance().getNodeView();
    if(view && (view->getCurrentDataConnection() || view->getCurrentConnection()))
        setMouseTracking(true);

    QWidget::enterEvent(event);
}

void Movable::leaveEvent(QEvent *event)
{
    setMouseTracking(false);

    QWidget::leaveEvent(event);
}

void Movable::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    if(event->key() == Qt::Key_Delete)
        kill();

}

QWidget *Movable::getParamPanel() const
{
    return paramPanel->viewport();
}

void Movable::setParamPanel(QWidget *value)
{
    delete paramPanel->viewport();

    paramPanel->setViewport(value);
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

void Movable::resetMovable()
{
}
