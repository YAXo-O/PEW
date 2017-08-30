#ifndef TIMELINE_H
#define TIMELINE_H

#include <QObject>
#include <QSlider>
#include <QLineEdit>

class Timeline : public QObject
{
    Q_OBJECT
public:
    explicit Timeline(QObject *parent = 0);
    ~Timeline() = default;

    void setConnections(QSlider *slide, QLineEdit *edit);
    void breakConnections(QSlider *slide, QLineEdit *edit);

signals:
    void frameChanged(unsigned newFrame);

    void changeSlider(int value);
    void changeText(QString value);

private slots:
    void sliderChanged(int value);
    void textChanged(QString value);

};

#endif // TIMELINE_H
