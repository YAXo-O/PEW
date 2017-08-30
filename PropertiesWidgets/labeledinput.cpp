#include <QHBoxLayout>
#include "labeledinput.h"

LabeledInput::LabeledInput(QWidget *parent) : QWidget(parent), line(new QLineEdit), text(new QLabel)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(line);
    layout->addWidget(text);
    setLayout(layout);

    setConnections();
}

LabeledInput::~LabeledInput()
{
}

void LabeledInput::setConnections()
{
    connect(line, SIGNAL(textChanged(QString)), this, SIGNAL(inputChanged(QString)));
}

void LabeledInput::setValidator(QValidator *val)
{
    line->setValidator(val);
}

void LabeledInput::setText(const QString &_text)
{
    text->setText(_text);
}

void LabeledInput::setText(const QString &&_text)
{
    text->setText(_text);
}

QString LabeledInput::getText()
{
    return text->text();
}

void LabeledInput::setInput(const QString &_text)
{
    line->setText(_text);
}

void LabeledInput::setInput(const QString &&_text)
{
    line->setText(_text);
}

QString LabeledInput::getInput()
{
    return line->text();
}

QLineEdit *LabeledInput::getLineEdit() const
{
    return line;
}

QLabel *LabeledInput::getLabel() const
{
    return text;
}

