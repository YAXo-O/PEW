#include "booldatawidget.h"

BoolDataWidget::BoolDataWidget(QWidget *parent) : QWidget(parent),
    check(new QCheckBox())
{
    check->setParent(this);
    connect(check, SIGNAL(stateChanged(int)), this, SIGNAL(stateChanged(int)));
    check->setText("Value");
}

BoolDataWidget::~BoolDataWidget()
{
    delete check;
}

void BoolDataWidget::setText(const QString &text)
{
    check->setText(text);
}

void BoolDataWidget::setText(const QString &&text)
{
    check->setText(text);
}

QString BoolDataWidget::getText() const
{
    return check->text();
}

void BoolDataWidget::setValue(bool bChecked)
{
    check->setChecked(bChecked);
}

bool BoolDataWidget::isChecked() const
{
    return check->isChecked();
}

QCheckBox *BoolDataWidget::getCheckBox()
{
    return check;
}

void BoolDataWidget::setCheckBox(QCheckBox *_check)
{
    if(check)
        delete check;
    check = _check;
    if(check)
        check->setParent(this);
}
