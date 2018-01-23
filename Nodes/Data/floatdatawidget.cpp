#include <QLineEdit>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLabel>

#include <QDebug>

#include "floatdatawidget.h"

FloatDataWidget::FloatDataWidget(QWidget *parent) : QWidget(parent), value(new QLineEdit("0"))
{
    QHBoxLayout *lout = new QHBoxLayout();
    setLayout(lout);

    value->setValidator(new QDoubleValidator());
    lout->addWidget(new QLabel("Value: "));
    lout->addWidget(value);

    connect(value, &QLineEdit::textEdited, [this](const QString &text)
    {
        emit valueChanged(text.toDouble());
    });
}

float FloatDataWidget::getValue() const
{
    qDebug() << value->text() << value->text().toDouble();
    return value->text().toDouble();
}

void FloatDataWidget::setValue(double val)
{
    value->setText(QString::number(val));
}
