#ifndef RENDERSTATUS_H
#define RENDERSTATUS_H

#include <QDialog>

namespace Ui {
    class RenderStatus;
}

class RenderStatus : public QDialog
{
    Q_OBJECT

public:
    explicit RenderStatus(QWidget *parent = 0);
    ~RenderStatus();

    void setSimProgress(int val);
    void setDisplayProgress(int val);
    void setRenderProgress(int val);
    void reset();

    void setRenderEnabled(bool bEnabled);

private:
    Ui::RenderStatus *ui;
};

#endif // RENDERSTATUS_H
