#ifndef OUTNODEWIDGET_H
#define OUTNODEWIDGET_H

#include <QWidget>

class QLineEdit;

class OutNodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutNodeWidget(QWidget *parent = nullptr);

    QString getPath() const;
    QSize getRes() const;

private:
    QLineEdit *path;
    QLineEdit *xRes;
    QLineEdit *yRes;

};

#endif // OUTNODEWIDGET_H
