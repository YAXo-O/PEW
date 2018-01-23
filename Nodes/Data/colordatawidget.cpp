#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QColorDialog>

#include "colordatawidget.h"

ColorDataWidget::ColorDataWidget(QWidget *parent) : QWidget(parent),
    colorPicker(new QLabel("<div style=\"background-color: #FFFFFF\"></div>")), color(Qt::white)
{
    QVBoxLayout *general = new QVBoxLayout();
    setLayout(general);

    QGroupBox *group = new QGroupBox("Color value: ");
    QHBoxLayout *colorLayout = new QHBoxLayout();
    group->setLayout(colorLayout);
    colorLayout->addWidget(new QLabel("Color: "));
    colorLayout->addWidget(colorPicker);

    general->addWidget(group);

    colorPicker->installEventFilter(this);
}

QColor ColorDataWidget::getValue() const
{
    return color;
}

void ColorDataWidget::setR(double r)
{
    color.setRedF(r);
    colorPicker->setText(QString("<div style=\"background-color: ") + color.name() + QString(";\"></div>"));
}

void ColorDataWidget::setG(double g)
{
    color.setGreenF(g);
    colorPicker->setText(QString("<div style=\"background-color: ") + color.name() + QString(";\"></div>"));
}

void ColorDataWidget::setB(double b)
{
    color.setBlueF(b);
    colorPicker->setText(QString("<div style=\"background-color: ") + color.name() + QString(";\"></div>"));
}

void ColorDataWidget::setValue(const QColor &value)
{
    color = value;
    colorPicker->setText(QString("<div style=\"background-color: ") + color.name() + QString(";\"></div>"));

    emit valueChanged(value);
}

bool ColorDataWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == colorPicker && event->type() == QEvent::MouseButtonPress)
    {
        color = QColorDialog::getColor(color, this, "Light color");
        colorPicker->setText(QString("<div style=\"background-color: ") + color.name() + QString(";\"></div>"));
        emit(valueChanged(color));

        return true;
    }

    return false;
}
