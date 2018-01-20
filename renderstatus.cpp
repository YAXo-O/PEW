#include "renderstatus.h"
#include "ui_renderstatus.h"

RenderStatus::RenderStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderStatus)
{
    ui->setupUi(this);
}

RenderStatus::~RenderStatus()
{
    delete ui;
}

void RenderStatus::setSimProgress(int val)
{
    ui->simProgress->setValue(val);
}

void RenderStatus::setDisplayProgress(int val)
{
    ui->displayProgress->setValue(val);
}

void RenderStatus::setRenderProgress(int val)
{
    ui->renderProgress->setValue(val);
}

void RenderStatus::reset()
{
    setSimProgress(0);
    setDisplayProgress(0);
    setRenderProgress(0);
}

void RenderStatus::setRenderEnabled(bool bEnabled)
{
    ui->renderProgress->setEnabled(bEnabled);
}
