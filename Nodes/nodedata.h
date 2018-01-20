#ifndef NODEDATA_H
#define NODEDATA_H

#include <typeinfo>
#include "movable.h"
#include "../PropertiesWidgets/dataproperties.h"
#include "../PropertiesWidgets/labeledinput.h"

// How to store data? It can be any type

const int movableData = 1;

class NodeData : public Movable
{
    Q_OBJECT
public:
    explicit NodeData(QWidget *parent = nullptr); // Have to add initial data type
    virtual ~NodeData(); // Have to take care of data

    void connectToViewer(const NodeView *viewer) override;
    void disconnectFromViewer() override;

    void setConnections();
    void breakConnections();

    virtual bool isPresent() const;
    virtual const void *getData();
    virtual void setData(const void *newData);
    virtual const char *dataType() const;
    static const char *dataType_s();

    void setBorderColour(QColor &colour);
    void setBorderColour(QColor &&colour);
    QColor getBorderColour() const;

    int type() override;

    int getRadius() const;
    int getOffset() const;
    const QString &getVarName() const;
    const QString &getVarDescription() const;

    void setDebugValue(const QString &value);
    void setDebugValue(const QString &&value);

protected:
    void paintEvent(QPaintEvent *pe) override;
    void mouseMoveEvent(QMouseEvent *me) override;
    void mousePressEvent(QMouseEvent *me) override;
    void enterEvent(QEvent *me) override;

    // Visual properties of the variable
    // Excliding border color, as it is chosen from the table
    // In order to keep unity
    void setRadius(int newRadius);
    void setOffset(int newOffset);
    void setVarName(const QString &newName);
    void setVarName(const QString &&newName);
    void setVarDescription(const QString &newDescription);
    void setVarDescription(const QString &&newDescription);

    void setUpBorder();
    void setRealKeyName(const QString &name);
    void setRealKeyName(const QString &&name);
    QString getRealKeyName();

    void visualPrepare(const QString &name);
    void visualPrepare(const QString &&name);
    virtual void prepareParamPanel();

private:
    QColor borderColor; // Border color depends on current data type
    int radius; // Radius of circle
    int offset; // Offset from the edges of the widget
    QString varName; // Name of the variable
    QString varDescription; // Description of the variable
    QString realKeyName; // its real key name; (used for swapping with selected)

    // NodeParams UI
    DataProperties *basicDataProps;
    LabeledInput *debugValue;

public slots:
    void becomeInactive() override;
    void becomeActive() override;

private slots:
    void changeName(const QString &name);
    void changeDescriprion(const QString &description);

signals:
    void dataConnection(NodeData *data);
};

#endif // NODEDATA_H
