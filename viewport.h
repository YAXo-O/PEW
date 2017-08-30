#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "pewwidget.h"

class Viewport : public PEWWidget
{
    Q_OBJECT
public:
    Viewport(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *pe) override;

private:
    void setUpStyle(QPainter &p);
};

#endif // VIEWPORT_H
