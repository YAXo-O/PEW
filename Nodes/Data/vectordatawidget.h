#ifndef VECTORDATAWIDGET_H
#define VECTORDATAWIDGET_H

#include <QWidget>
#include <QVector3D>

class QLineEdit;

class VectorDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VectorDataWidget(QWidget *parent = nullptr);

    QVector3D getValue() const;
    void setX(double X);
    void setY(double Y);
    void setZ(double Z);
    void setValue(const QVector3D &value);

signals:
    void valueChanged(QVector3D value);

private:
    QLineEdit *x;
    QLineEdit *y;
    QLineEdit *z;
};

#endif // VECTORDATAWIDGET_H
