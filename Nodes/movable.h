#ifndef MOVABLE_H
#define MOVABLE_H

#include <QWidget>
#include <QScrollArea>

const int movableBase = 0;

class NodeView;

class Movable : public QWidget
{
    Q_OBJECT
public:
    explicit Movable(QWidget *parent = nullptr);
    ~Movable();

    void setKeyName(const QString &keyName);
    void setKeyName(const QString &&keyName);
    QString getKeyName();

    virtual void connectToViewer(const NodeView *viewer);
    virtual void disconnectFromViewer();
    virtual void kill();

    virtual int type();

    bool getDeletable() const;
    void setDeletable(bool value);

protected:
    void mouseMoveEvent(QMouseEvent *me) override;
    void mousePressEvent(QMouseEvent *me) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    QWidget *getParamPanel() const;
    void setParamPanel(QWidget *panel);
    void displayPropertiesPanel() const;
    void hidePropertiesPanel();

    void appendParamsWidget(QWidget *appendee);

private:
    bool bDeletable;
    QPoint clickVector; // Vector from top left corner to click position
    QString keyName; // Key; Used for specific stuff (like colour of nodes and etc)

    //QWidget *paramPanel; // Panel to display and edit current nodes parametres
    QScrollArea *paramPanel;

public slots:
    virtual void becomeInactive();
    virtual void becomeActive();
    virtual void resetMovable();

signals:
    void becameActive(Movable *me);
    void killMe(Movable *me);
};

#endif // MOVABLE_H
