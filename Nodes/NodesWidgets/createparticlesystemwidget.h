#ifndef CREATEPARTICLESYSTEMWIDGET_H
#define CREATEPARTICLESYSTEMWIDGET_H

#include <QGroupBox>

class QLineEdit;

class CreateParticleSystemWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit CreateParticleSystemWidget(QWidget *parent = 0);

    QVector3D getPos() const;
    double getRadius() const;
    unsigned getCount() const;

private:
    QLineEdit *x;
    QLineEdit *y;
    QLineEdit *z;
    QLineEdit *radius;
    QLineEdit *count;
};

#endif // CREATEPARTICLESYSTEMWIDGET_H
