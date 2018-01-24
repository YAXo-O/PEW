#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "../../texturemanager.h"
#include "../../worldinfo.h"
#include "materialdatawidget.h"
#include "mapwidget.h"

MaterialDataWidget::MaterialDataWidget(QWidget *parent) : QWidget(parent),
    diff(new MapWidget("Diffuse")), ambient(new MapWidget("Ambient")),
    specularColor(new MapWidget("Specular color")), specularLevel(new MapWidget("Specular level"))
{
    QGroupBox *mat = new QGroupBox("Material");
    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(diff);
    l->addWidget(ambient);
    l->addWidget(specularColor);
    l->addWidget(specularLevel);
    mat->setLayout(l);

    QVBoxLayout *lay = new QVBoxLayout();
    setLayout(lay);
    lay->addWidget(mat);
}

Material MaterialDataWidget::getValue() const
{
    TextureManager &man = WorldInfo::getInstance().textureManager();

    Material res;

    res.getDiffuse().setBaseColor(diff->getColor());
    res.getDiffuse().setIndex(diff->getValue());
    if(diff->getFilename() != "")
        res.getDiffuse().setTexture(man.getTexture(diff->getFilename()));
    else
        res.getDiffuse().setTexture(nullptr);

    res.getAmbient().setBaseColor(ambient->getColor());
    res.getAmbient().setIndex(ambient->getValue());
    if(ambient->getFilename() != "")
        res.getAmbient().setTexture(man.getTexture(ambient->getFilename()));
    else
        res.getAmbient().setTexture(nullptr);

    res.getSpecularLevel().setBaseColor(specularLevel->getColor());
    res.getSpecularLevel().setIndex(specularLevel->getValue());
    if(specularLevel->getFilename() != "")
        res.getSpecularLevel().setTexture(man.getTexture(specularLevel->getFilename()));
    else
        res.getSpecularLevel().setTexture(nullptr);

    res.getSpecularColor().setBaseColor(specularColor->getColor());
    res.getSpecularColor().setIndex(specularColor->getValue());
    if(specularColor->getFilename() != "")
        res.getSpecularColor().setTexture(man.getTexture(specularColor->getFilename()));
    else
        res.getSpecularColor().setTexture(nullptr);

    return res;
}
