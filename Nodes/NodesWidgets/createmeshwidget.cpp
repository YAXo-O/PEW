#include "createmeshwidget.h"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>

CreateMeshWidget::CreateMeshWidget(QWidget *parent) : QWidget(parent), filename(new QLineEdit)
{
    QVBoxLayout *genLayout = new QVBoxLayout();
    QGroupBox *box = new QGroupBox();
    box->setTitle("File");
    genLayout->addWidget(box);
    QHBoxLayout *l = new QHBoxLayout();
    box->setLayout(l);
    l->addWidget(new QLabel("File: "));
    l->addWidget(filename);
    QPushButton *pb = new QPushButton();
    l->addWidget(pb);
    pb->setText("Choose...");

    connect(pb, &QPushButton::clicked, [this]()mutable
    {
        filename->setText(QFileDialog::getOpenFileName(nullptr, "Choose mesh file", "./", "*.obj"));
    });

    setLayout(genLayout);
}

QString CreateMeshWidget::getPath() const
{
    return filename->text();
}
