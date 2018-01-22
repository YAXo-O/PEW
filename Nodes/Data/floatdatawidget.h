#ifndef FLOATDATAWIDGET_H
#define FLOATDATAWIDGET_H

#include <QWidget>
class QLineEdit;

class FloatDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloatDataWidget(QWidget *parent = 0);

    float getValue() const;

public slots:
    void setValue(double val);

signals:
    void valueChanged(double val);

private:
    QLineEdit *value;
};

#endif // FLOATDATAWIDGET_H
