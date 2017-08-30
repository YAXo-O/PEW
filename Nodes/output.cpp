#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
#include "../WidgetUtilities/styleloader.h"
#include "output.h"
#include "BaseNode.h"
#include "pinproperties.h"

Output::Output(QString _outputName, QWidget *parent) : QWidget(parent), outputName(_outputName)
{
    setStyleSheet(StyleLoader::loadCSS(cssPath + "BaseNode.css"));
    resize(pinSize);
}

void Output::setName(const QString &name)
{
    outputName = name;
}

void Output::setName(const QString &&name)
{
    setName(name);
}

QString Output::getName() const
{
    return outputName;
}

void Output::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    setUpStyle(p);

    p.end();
}

void Output::mousePressEvent(QMouseEvent *me)
{
    if(me->button() & Qt::LeftButton)
        emit startConnection(qobject_cast<BaseNode *>(parentWidget()), signalName);

    QWidget::mousePressEvent(me);
}

void Output::setLab(QLabel *value)
{
    lab = value;
}

QLabel *Output::getLab() const
{
    return lab;
}

void Output::setSignalName(const QString &value)
{
    signalName = value;
}

void Output::setSignalName(const QString &&value)
{
    signalName = value;
}

QString Output::getSignalName() const
{
    return signalName;
}

void Output::setUpStyle(QPainter &p)
{
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
