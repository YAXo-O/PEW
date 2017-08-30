#ifndef LABELEDINPUT_H
#define LABELEDINPUT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>

class LabeledInput : public QWidget
{
    Q_OBJECT
public:
    explicit LabeledInput(QWidget *parent = nullptr);
    ~LabeledInput();

    void setConnections();
    void setValidator(QValidator *val);

    void setText(const QString &text);
    void setText(const QString &&text);
    QString getText();
    void setInput(const QString &text);
    void setInput(const QString &&text);
    QString getInput();

    QLineEdit *getLineEdit() const;
    QLabel *getLabel() const;

private:
    QLineEdit *line;
    QLabel *text;

signals:
    void inputChanged(QString value);
};

#endif // LABELEDINPUT_H
