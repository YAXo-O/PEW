#ifndef INTDATAWIDGET_H
#define INTDATAWIDGET_H

#include <QWidget>

class QLineEdit;

class IntDataWidget: public QWidget
{
    Q_OBJECT
public:
    explicit IntDataWidget(QWidget *parent = 0);

    int32_t getValue() const;

public slots:
    void setValue(int32_t val);

signals:
    void valueChanged(int32_t val);

private:
    QLineEdit *value;
};

#endif // INTDATAWIDGET_H
