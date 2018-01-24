#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QFileDialog>
#include <QEvent>
#include <QLineEdit>
#include <QDoubleValidator>
#include "mapwidget.h"

MapWidget::MapWidget(const QString &name, QWidget *parent) : QGroupBox(parent), map(new QPushButton("Choose...")),
    colorPicker(new QLabel("<div style=\"background-color: #000000\">Color</div>")),
    value(new QLineEdit("1")), filename(""), color(Qt::black)
{
    setTitle(name);
    QHBoxLayout *hor = new QHBoxLayout();
    setLayout(hor);
    hor->addWidget(colorPicker);
    hor->addWidget(map);
    value->setValidator(new QDoubleValidator(0, 1e9, 3));
    hor->addWidget(value);

    connect(map, SIGNAL(clicked()), SLOT(pickTexture()));

    colorPicker->installEventFilter(this);

    value->setLocale(QLocale("RU-ru"));
}

QString MapWidget::getFilename() const
{
    return filename;
}

QColor MapWidget::getColor() const
{
    return color;
}

double MapWidget::getValue() const
{
    return locale().toDouble(value->text());
}

bool MapWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == colorPicker && event->type() == QEvent::MouseButtonPress)
    {
        color = QColorDialog::getColor(Qt::red, nullptr, "Choose base color");
        colorPicker->setText(QString("<div style=\"background-color: ") + color.name() + QString("\">Color</div>"));

        return true;
    }

    return false;
}

void MapWidget::pickTexture()
{
    filename = QFileDialog::getOpenFileName(nullptr, "", "Choose texture");
    if(filename != "")
        map->setText("M");
    else
        map->setText("Choose...");
}
