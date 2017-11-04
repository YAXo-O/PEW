#ifndef BOOLDATAWIDGET_H
#define BOOLDATAWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>

class BoolDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoolDataWidget(QWidget *parent = nullptr);
    ~BoolDataWidget();

    void setText(const QString &text);
    void setText(const QString &&text);
    QString getText() const;

    void setValue(bool bChecked);
    bool isChecked() const;

    QCheckBox *getCheckBox();
    void setCheckBox(QCheckBox *check);

private:
    QCheckBox *check;

signals:
    void stateChanged(int);
};

#endif // BOOLDATAWIDGET_H
