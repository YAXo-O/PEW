#ifndef CREATEMESHWIDGET_H
#define CREATEMESHWIDGET_H

#include <QWidget>

class QLineEdit;

class CreateMeshWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreateMeshWidget(QWidget *parent = 0);

    QString getPath() const;

private:
    QLineEdit *filename;
};

#endif // CREATEMESHWIDGET_H
