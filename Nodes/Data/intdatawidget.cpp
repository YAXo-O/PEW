#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QLabel>

#include "intdatawidget.h"

IntDataWidget::IntDataWidget(QWidget *parent): QWidget(parent), value(new QLineEdit("0"))
{
    QGroupBox *box = new QGroupBox(this);
    QLabel *lab = new QLabel("Value: ");
    QHBoxLayout *lay = new QHBoxLayout();
    lay->addWidget(lab);
    lay->addWidget(value);
    box->setTitle("Int value: ");
    box->setLayout(lay);
    value->setValidator(new QIntValidator());

    QVBoxLayout *generalLayout = new QVBoxLayout();
    setLayout(generalLayout);
    generalLayout->addWidget(box);

    connect(value, &QLineEdit::textEdited, [this](const QString &value)mutable{emit valueChanged(value.toInt());});

}

int32_t IntDataWidget::getValue() const
{
    return value->text().toInt();
}

void IntDataWidget::setValue(int32_t val)
{
    value->setText(QString::number(val));
}
