#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>
#include <QLabel>

class BaseNode;

class Output : public QWidget
{
    Q_OBJECT
public:
    explicit Output(QString outputName, QWidget *parent = nullptr);

    void setName(const QString &name);
    void setName(const QString &&name);
    QString getName() const;

    void setSignalName(const QString &value);
    void setSignalName(const QString &&value);
    QString getSignalName() const;

    void setLab(QLabel *value);
    QLabel *getLab() const;

protected:
    void paintEvent(QPaintEvent *pe) override;
    void mousePressEvent(QMouseEvent *me) override;

private:
    QString outputName;
    QString signalName;
    QLabel *lab;

    void setUpStyle(QPainter &p);

signals:
    void startConnection(BaseNode *sender, const QString &outputName);
};

#endif // OUTPUT_H
