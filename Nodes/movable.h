#ifndef MOVABLE_H
#define MOVABLE_H

#include <QWidget>

const int movableBase = 0;

class NodeView;

class Movable : public QWidget
{
    Q_OBJECT
public:
    explicit Movable(QWidget *parent = nullptr);

    void setKeyName(const QString &keyName);
    void setKeyName(const QString &&keyName);
    QString getKeyName();

    virtual void connectToViewer(const NodeView *viewer);
    virtual void disconnectFromViewer();

    virtual int type();

protected:
    void mouseMoveEvent(QMouseEvent *me) override;
    void mousePressEvent(QMouseEvent *me) override;

    QWidget *getParamPanel() const;
    void setParamPanel(QWidget *panel);
    void displayPropertiesPanel() const;
    void hidePropertiesPanel();

private:
    QPoint clickVector; // Vector from top left corner to click position
    QString keyName; // Key; Used for specific stuff (like colour of nodes and etc)

    QWidget *paramPanel; // Panel to display and edit current nodes parametres

public slots:
    virtual void becomeInactive();
    virtual void becomeActive();

signals:
    void becameActive(Movable *me);
};

#endif // MOVABLE_H
