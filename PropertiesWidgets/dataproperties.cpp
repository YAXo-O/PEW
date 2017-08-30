#include <QVBoxLayout>
#include "dataproperties.h"

DataProperties::DataProperties(QWidget *parent) : QWidget(parent), box(new QGroupBox),
    varName(new LabeledInput), varDescription(new LabeledInput)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(varName);
    layout->addWidget(varDescription);
    box->setLayout(layout);
    setLayout(new QVBoxLayout);
    this->layout()->addWidget(box);

    setConnections();
}

void DataProperties::setConnections()
{
    connect(varName, SIGNAL(inputChanged(QString)), this, SIGNAL(nameChanged(QString)));
    connect(varDescription, SIGNAL(inputChanged(QString)), this, SIGNAL(descriptionChanged(QString)));
}

void DataProperties::setNameLabel(const QString &name)
{
    varName->setText(name);
}

void DataProperties::setNameLabel(const QString &&name)
{
    varName->setText(name);
}

QString DataProperties::getNameLabel() const
{
    return varName->getText();
}

void DataProperties::setNameInput(const QString &name)
{
    varName->setInput(name);
}

void DataProperties::setNameInput(const QString &&name)
{
    varName->setInput(name);
}

QString DataProperties::getNameInput() const
{
    return varName->getInput();
}

void DataProperties::setDescriptionLabel(const QString &description)
{
    varDescription->setText(description);
}

void DataProperties::setDescriptionLabel(const QString &&description)
{
    varDescription->setText(description);
}

void DataProperties::setDescriptionInput(const QString &name)
{
    varDescription->setInput(name);
}

void DataProperties::setDescriptionInput(const QString &&name)
{
    varDescription->setInput(name);
}

QString DataProperties::getDescriptionInput() const
{
    return varDescription->getInput();
}

void DataProperties::setGroupName(const QString &name)
{
    box->setTitle(name);
}

void DataProperties::setGroupName(const QString &&name)
{
    box->setTitle(name);
}

QString DataProperties::getGroupName() const
{
    return box->title();
}

LabeledInput *DataProperties::getVarName() const
{
    return varName;
}

LabeledInput *DataProperties::getVarDescription() const
{
    return varDescription;
}

QGroupBox *DataProperties::getGroup() const
{
    return box;
}

QString DataProperties::getDescriptionLabel() const
{
    return varDescription->getText();
}
