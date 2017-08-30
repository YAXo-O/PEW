#ifndef PEWWIDGET_H
#define PEWWIDGET_H

#include <QWidget>

class PEWWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PEWWidget(QWidget *parent = nullptr);

    void setBorder(QColor col = Qt::black, int wid = 1);
    void setActiveBorder(QColor col = Qt::yellow, int wid = 1);
    QColor getBorderColor() const;
    int getBorderWidth() const;
    QColor getActiveBorderColor() const;
    int getActiveBorderWidth() const;
    bool isCurrent() const;

public slots:
    void receiveActive(PEWWidget *wid);

protected:
    enum resizeDir
    {
        RD_NONE, RD_X, RD_Y, RD_DIAG
    };

    // Overriding
    void mousePressEvent(QMouseEvent *me) override;
    void mouseMoveEvent(QMouseEvent *me) override;// Kinda template-method
    void paintEvent(QPaintEvent *pe) override;

    // Template-method steps
    void mouseUnpressedMove(QMouseEvent *me);
    void mouseResizeMove(QMouseEvent *me);

    // New methods
    void becomeInactive();

private:
    resizeDir resizeDirection;

    // Border
    int borderWidth;
    QColor borderColor;
    int activeBorderWidth;
    QColor activeBorderColor;
    int currentWidth;
    QColor currentColor;
    bool bActive;

signals:
    void becameActive(PEWWidget *wid);
};

#endif // PEWWIDGET_H
