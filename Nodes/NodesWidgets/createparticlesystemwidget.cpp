#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector3D>

#include "createparticlesystemwidget.h"


CreateParticleSystemWidget::CreateParticleSystemWidget(QWidget *parent) : QGroupBox(parent),
    x(new QLineEdit("0")), y(new QLineEdit("0")), z(new QLineEdit("0")), radius(new QLineEdit("100")),
    count(new QLineEdit("10"))
{
    QVBoxLayout *gen = new QVBoxLayout();
    setTitle("Emitter options");
    setLayout(gen);

    QHBoxLayout *pos = new QHBoxLayout();
    pos->addWidget(new QLabel("X: "));
    pos->addWidget(x);
    pos->addWidget(new QLabel("Y: "));
    pos->addWidget(y);
    pos->addWidget(new QLabel("Z: "));
    pos->addWidget(z);
    gen->addLayout(pos);

    QHBoxLayout *rLayout = new QHBoxLayout();
    rLayout->addWidget(new QLabel("Radius: "));
    rLayout->addWidget(radius);
    gen->addLayout(rLayout);

    QHBoxLayout *cLayout = new QHBoxLayout();
    cLayout->addWidget(new QLabel("Count: "));
    cLayout->addWidget(count);
    gen->addLayout(cLayout);
}

QVector3D CreateParticleSystemWidget::getPos() const
{
    return QVector3D(x->text().toDouble(), y->text().toDouble(), z->text().toDouble());
}

double CreateParticleSystemWidget::getRadius() const
{
    return radius->text().toDouble();
}

unsigned CreateParticleSystemWidget::getCount() const
{
    return radius->text().toUInt();
}
