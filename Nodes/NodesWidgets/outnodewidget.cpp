#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>

#include "outnodewidget.h"

OutNodeWidget::OutNodeWidget(QWidget *parent) : QWidget(parent), path(new QLineEdit("./Out/")),
    xRes(new QLineEdit("1280")), yRes(new QLineEdit("720")), renderToFile(new QCheckBox("Render to file"))
{
    QLabel *pathLab = new QLabel("Directory for render: ");
    QLabel *xResLab = new QLabel("X resolution: ");
    QLabel *yResLab = new QLabel("Y resolution: ");
    QPushButton *choosePB = new QPushButton("Choose...");

    connect(choosePB, &QPushButton::clicked, [this]()mutable
    {
        path->setText(QFileDialog::getExistingDirectory(nullptr, "Save File dir", "./"));
    });

    QIntValidator *val = new QIntValidator();
    xRes->setValidator(val);
    yRes->setValidator(val);

    QGroupBox *group = new QGroupBox();
    group->setTitle("Render to file options");
    QVBoxLayout *groupLayout = new QVBoxLayout();
    group->setLayout(groupLayout);
    QVBoxLayout *general = new QVBoxLayout();
    setLayout(general);

    // Render
    renderToFile->setChecked(false);
    groupLayout->addWidget(renderToFile);

    // Path
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathLab);
    pathLayout->addWidget(path);
    pathLayout->addWidget(choosePB);
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

bool OutNodeWidget::getRender() const
{
    return renderToFile->isChecked();
}
