#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGroupBox>

class QPushButton;
class QLabel;
class QLineEdit;

class MapWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit MapWidget(const QString &name, QWidget *parent = 0);

    QString getFilename() const;
    QColor getColor() const;
    double getValue() const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QPushButton *map;
    QLabel *colorPicker;
    QLineEdit *value;
    QString filename;
    QColor color;

private slots:
    void pickTexture();
};

#endif // MAPWIDGET_H
