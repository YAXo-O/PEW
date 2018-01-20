#ifndef OUTNODEWIDGET_H
#define OUTNODEWIDGET_H

#include <QWidget>

class QLineEdit;
class QCheckBox;

class OutNodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutNodeWidget(QWidget *parent = nullptr);

    QString getPath() const;
    QSize getRes() const;
    bool getRender() const;

private:
    QLineEdit *path;
    QLineEdit *xRes;
    QLineEdit *yRes;
    QCheckBox *renderToFile;
};

#endif // OUTNODEWIDGET_H
