#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QLabel>

class BaseNode;

class Input : public QWidget
{
    Q_OBJECT
public:
    explicit Input(QString inputName, QWidget *parent = nullptr);

    void setName(const QString &name);
    void setName(const QString &&name);
    QString getName() const;

    void setSlotName(const QString &value);
    void setSlotName(const QString &&value);
    QString getSlotName() const;

    void setLab(QLabel *value);
    QLabel *getLab() const;

protected:
    void paintEvent(QPaintEvent *pe) override;
    void mouseReleaseEvent(QMouseEvent *me) override;

private:
    QString inputName;
    QString slotName;

    QLabel *lab;

    void setUpStyle(QPainter &p);

signals:
    void receiveConnection(BaseNode *receiver, const QString &inputSlot);
};

#endif // INPUT_H
