#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QGroupBox>

#include "outnodewidget.h"

OutNodeWidget::OutNodeWidget(QWidget *parent) : QWidget(parent), path(new QLineEdit("./Out/")),
    xRes(new QLineEdit("1280")), yRes(new QLineEdit("720"))
{
    QLabel *pathLab = new QLabel("Directory for render: ");
    QLabel *xResLab = new QLabel("X resolution: ");
    QLabel *yResLab = new QLabel("Y resolution: ");

    QIntValidator *val = new QIntValidator();
    xRes->setValidator(val);
    yRes->setValidator(val);

    QGroupBox *group = new QGroupBox();
    group->setTitle("Render to file options");
    QVBoxLayout *groupLayout = new QVBoxLayout();
    group->setLayout(groupLayout);
    QVBoxLayout *general = new QVBoxLayout();
    setLayout(general);

    // Path
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathLab);
    pathLayout->addWidget(path);
    groupLayout->addLayout(pathLayout);

    QHBoxLayout *resLayout = new QHBoxLayout();

    // XRes
    resLayout->addWidget(xResLab);
    resLayout->addWidget(xRes);

    // YRes
    resLayout->addWidget(yResLab);
    resLayout->addWidget(yRes);

    groupLayout->addLayout(resLayout);
    general->addWidget(group);
    setLayout(general);
}

QString OutNodeWidget::getPath() const
{
    return path->text();
}

QSize OutNodeWidget::getRes() const
{
    return QSize(xRes->text().toInt(), yRes->text().toInt());
}
