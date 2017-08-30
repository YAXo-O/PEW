#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
#include "../WidgetUtilities/styleloader.h"
#include "input.h"
#include "basenode.h"
#include "pinproperties.h"

Input::Input(QString _inputName, QWidget *parent) : QWidget(parent), inputName(_inputName),
    lab(nullptr)
{
    setStyleSheet(StyleLoader::loadCSS(cssPath + "BaseNode.css"));
    resize(pinSize);
}

void Input::setName(const QString &name)
{
    inputName = name;
}

void Input::setName(const QString &&name)
{
    setName(name);
}

QString Input::getName() const
{
    return inputName;
}

void Input::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    setUpStyle(p);

    p.end();
}

void Input::mouseReleaseEvent(QMouseEvent *me)
{
    if(me->button() & Qt::LeftButton)
        emit receiveConnection(qobject_cast<BaseNode *>(parentWidget()), slotName);

    QWidget::mouseReleaseEvent(me);
}

QLabel *Input::getLab() const
{
    return lab;
}

void Input::setLab(QLabel *value)
{
    lab = value;
}

void Input::setSlotName(const QString &value)
{
    slotName = value;
}

void Input::setSlotName(const QString &&value)
{
    slotName = value;
}

QString Input::getSlotName() const
{
    return slotName;
}


void Input::setUpStyle(QPainter &p)
{
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
