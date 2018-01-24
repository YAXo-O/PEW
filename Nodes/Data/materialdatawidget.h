#ifndef MATERIALDATAWIDGET_H
#define MATERIALDATAWIDGET_H

#include <QWidget>
#include "../../Model/material.h"
#include "../../Model/colormap.h"

class MapWidget;

class MaterialDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MaterialDataWidget(QWidget *parent = 0);
    ~MaterialDataWidget() {}

    Material getValue() const;

private:
    MapWidget *diff;
    MapWidget *ambient;
    MapWidget *specularColor;
    MapWidget *specularLevel;
};

#endif // MATERIALDATAWIDGET_H
