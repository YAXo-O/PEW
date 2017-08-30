#include "timeline.h"

Timeline::Timeline(QObject *parent) : QObject(parent)
{
}

void Timeline::setConnections(QSlider *slide, QLineEdit *edit)
{
    connect(slide, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));
    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(this, SIGNAL(changeSlider(int)), slide, SLOT(setValue(int)));
    connect(this, SIGNAL(changeText(QString)), edit, SLOT(setText(QString)));
}

void Timeline::breakConnections(QSlider *slide, QLineEdit *edit)
{
    disconnect(slide, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));
    disconnect(edit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    disconnect(this, SIGNAL(changeSlider(int)), slide, SLOT(setValue(int)));
    disconnect(this, SIGNAL(changeText(QString)), edit, SLOT(setText(QString)));
}

void Timeline::sliderChanged(int value)
{
    emit changeText(QString::number(value));
    emit frameChanged(value);
}

void Timeline::textChanged(QString value)
{
    unsigned frame = value.toUInt();

    emit changeSlider(frame);
    emit frameChanged(frame);
}
