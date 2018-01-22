#ifndef COLORDATAWIDGET_H
#define COLORDATAWIDGET_H

#include <QWidget>
#include <QColor>

class QLabel;

class ColorDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorDataWidget(QWidget *parent = nullptr);

    QColor getValue() const;
    void setR(double r);
    void setG(double g);
    void setB(double b);
    void setValue(const QColor &value);

signals:
    void valueChanged(QColor value);

private:
    QLabel *colorPicker;
    QColor color;

protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // COLORDATAWIDGET_H
