#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleValidator>

#include "vectordatawidget.h"

VectorDataWidget::VectorDataWidget(QWidget *parent) : QWidget(parent),
    x(new QLineEdit("0")), y(new QLineEdit("0")), z(new QLineEdit("0"))
{
    QDoubleValidator *val = new QDoubleValidator();
    x->setValidator(val);
    y->setValidator(val);
    z->setValidator(val);

    QHBoxLayout *lay = new QHBoxLayout();
    QGroupBox *box = new QGroupBox("Vector value: ");
    box->setLayout(lay);

    lay->addWidget(new QLabel("X: "));
    lay->addWidget(x);
    lay->addWidget(new QLabel("Y: "));
    lay->addWidget(y);
    lay->addWidget(new QLabel("Z: "));
    lay->addWidget(z);

    QVBoxLayout *generalLayout = new QVBoxLayout();
    generalLayout->addWidget(box);
    setLayout(generalLayout);

    connect(x, &QLineEdit::textEdited, [this](const QString &)
    {
       emit valueChanged(getValue());
    });

    connect(y, &QLineEdit::textEdited, [this](const QString &)
    {
       emit valueChanged(getValue());
    });

    connect(z, &QLineEdit::textEdited, [this](const QString &)
    {
       emit valueChanged(getValue());
    });
}

QVector3D VectorDataWidget::getValue() const
{
    return QVector3D(x->text().toDouble(), y->text().toDouble(), z->text().toDouble());
}

void VectorDataWidget::setX(double X)
{
    x->setText(QString::number(X));
}

void VectorDataWidget::setY(double Y)
{
    x->setText(QString::number(Y));
}

void VectorDataWidget::setZ(double Z)
{
    x->setText(QString::number(Z));
}

void VectorDataWidget::setValue(const QVector3D &value)
{
    setX(value.x());
    setY(value.y());
    setZ(value.z());
}
