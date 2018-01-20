#ifndef CAMERADATAWIDGET_H
#define CAMERADATAWIDGET_H

#include <QWidget>
#include <QDial>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>

class CameraDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraDataWidget(QWidget *parent = 0);
    ~CameraDataWidget() = default;

    int getPitch() const;
    int getRoll() const;
    int getYaw() const;
    QVector3D getLocation() const;
    float getFov() const;

    void setPitch(int pitch);
    void setRoll(int roll);
    void setYaw(int yaw);
    void setLocation(const QVector3D &location);
    void setLocation(const QVector3D &&location);
    void setFov(float fov);

private slots:
    void setPitchLine(int value);
    void setRollLine(int value);
    void setYawLine(int value);
    void setPitchWid(const QString &value);
    void setRollWid(const QString &value);
    void setYawWid(const QString &value);

protected:
    void setConnections();

private:
    QDial *pitch;
    QDial *roll;
    QDial *yaw;
    QLabel *pitchLab;
    QLabel *rollLab;
    QLabel *yawLab;
    QLineEdit *pitchLine;
    QLineEdit *rollLine;
    QLineEdit *yawLine;
    QGroupBox *orientation;

    QLabel *xLab;
    QLabel *yLab;
    QLabel *zLab;
    QLineEdit *xLine;
    QLineEdit *yLine;
    QLineEdit *zLine;
    QGroupBox *location;

    QLabel *fovLab;
    QLineEdit *fovLine;

};

#endif // CAMERADATAWIDGET_H
