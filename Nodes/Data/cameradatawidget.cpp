#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QValidator>
#include <QVector3D>
#include "cameradatawidget.h"

CameraDataWidget::CameraDataWidget(QWidget *parent) : QWidget(parent),
    pitch(new QDial), roll(new QDial), yaw(new QDial),
    pitchLab(new QLabel), rollLab(new QLabel), yawLab(new QLabel),
    pitchLine(new QLineEdit), rollLine(new QLineEdit), yawLine(new QLineEdit),
    orientation(new QGroupBox),
    xLab(new QLabel), yLab(new QLabel), zLab(new QLabel),
    xLine(new QLineEdit), yLine(new QLineEdit), zLine(new QLineEdit),
    location(new QGroupBox),
    fovLab(new QLabel), fovLine(new QLineEdit)
{
    QVBoxLayout *cameraLayout = new QVBoxLayout;
    setLayout(cameraLayout);

    QVBoxLayout *orientationLayout = new QVBoxLayout;
    orientation->setLayout(orientationLayout);

    QHBoxLayout *pitchLayout = new QHBoxLayout;
    pitchLayout->addWidget(pitchLab);
    pitchLayout->addWidget(pitchLine);
    pitchLayout->addWidget(pitch);

    QHBoxLayout *rollLayout = new QHBoxLayout;
    rollLayout->addWidget(rollLab);
    rollLayout->addWidget(rollLine);
    rollLayout->addWidget(roll);

    QHBoxLayout *yawLayout = new QHBoxLayout;
    yawLayout->addWidget(yawLab);
    yawLayout->addWidget(yawLine);
    yawLayout->addWidget(yaw);

    orientationLayout->addLayout(pitchLayout);
    orientationLayout->addLayout(rollLayout);
    orientationLayout->addLayout(yawLayout);
    cameraLayout->addWidget(orientation);

    QIntValidator *validator = new QIntValidator(0, 360);
    pitchLine->setValidator(validator);
    rollLine->setValidator(validator);
    yawLine->setValidator(validator);

    orientation->setTitle("Camera orientation");

    QDoubleValidator *doubleValidator = new QDoubleValidator();

    QHBoxLayout *xLayout = new QHBoxLayout;
    xLayout->addWidget(xLab);
    xLayout->addWidget(xLine);
    xLine->setValidator(doubleValidator);
    xLab->setText("X: ");
    xLine->setText("200");

    QHBoxLayout *yLayout = new QHBoxLayout;
    yLayout->addWidget(yLab);
    yLayout->addWidget(yLine);
    yLine->setValidator(doubleValidator);
    yLab->setText("Y: ");
    yLine->setText("0");

    QHBoxLayout *zLayout = new QHBoxLayout;
    zLayout->addWidget(zLab);
    zLayout->addWidget(zLine);
    zLine->setValidator(doubleValidator);
    zLab->setText("Z: ");
    zLine->setText("0");

    QVBoxLayout *locationLayout = new QVBoxLayout;
    locationLayout->addLayout(xLayout);
    locationLayout->addLayout(yLayout);
    locationLayout->addLayout(zLayout);
    location->setLayout(locationLayout);

    location->setTitle("Camera location");
    cameraLayout->addWidget(location);

    QHBoxLayout *fovLayout = new QHBoxLayout;
    fovLayout->addWidget(fovLab);
    fovLayout->addWidget(fovLine);
    fovLab->setText("FOV(degrees): ");
    fovLine->setText("45");
    fovLine->setValidator(doubleValidator);

    cameraLayout->addLayout(fovLayout);

    setConnections();
}

int CameraDataWidget::getPitch() const
{
    return pitch->value();
}

int CameraDataWidget::getRoll() const
{
    return roll->value();
}

int CameraDataWidget::getYaw() const
{
    return yaw->value();
}

QVector3D CameraDataWidget::getLocation() const
{
    return QVector3D(xLine->text().toFloat(), yLine->text().toFloat(), zLine->text().toFloat());
}

float CameraDataWidget::getFov() const
{
    return fovLine->text().toFloat();
}

void CameraDataWidget::setPitch(int _pitch)
{
    pitch->setValue(_pitch);
}

void CameraDataWidget::setRoll(int _roll)
{
    roll->setValue(_roll);
}

void CameraDataWidget::setYaw(int _yaw)
{
    yaw->setValue(_yaw);
}

void CameraDataWidget::setLocation(const QVector3D &location)
{
    xLine->setText(QString::number(location.x()));
    yLine->setText(QString::number(location.y()));
    zLine->setText(QString::number(location.z()));
}

void CameraDataWidget::setLocation(const QVector3D &&location)
{
    setLocation(location);
}

void CameraDataWidget::setFov(float fov)
{
    fovLine->setText(QString::number(fov));
}

void CameraDataWidget::setPitchLine(int value)
{
    pitchLine->setText(QString::number(value));
}

void CameraDataWidget::setRollLine(int value)
{
    rollLine->setText(QString::number(value));
}

void CameraDataWidget::setYawLine(int value)
{
    yawLine->setText(QString::number(value));
}

void CameraDataWidget::setPitchWid(const QString &value)
{
    setPitch(value.toInt());
}

void CameraDataWidget::setRollWid(const QString &value)
{
    setRoll(value.toInt());
}

void CameraDataWidget::setYawWid(const QString &value)
{
    setYaw(value.toInt());
}

void CameraDataWidget::setConnections()
{
    pitch->setValue(0);
    roll->setValue(0);
    yaw->setValue(0);
    setPitchLine(0);
    setRollLine(0);
    setYawLine(0);
    pitchLab->setText("Pitch: ");
    rollLab->setText("Roll: ");
    yawLab->setText("Yaw: ");

    connect(pitch, SIGNAL(valueChanged(int)), this, SLOT(setPitchLine(int)));
    connect(roll, SIGNAL(valueChanged(int)), this, SLOT(setRollLine(int)));
    connect(yaw, SIGNAL(valueChanged(int)), this, SLOT(setYawLine(int)));
    connect(pitchLine, SIGNAL(textChanged(QString)), this, SLOT(setPitchWid(QString)));
    connect(rollLine, SIGNAL(textChanged(QString)), this, SLOT(setRollWid(QString)));
    connect(yawLine, SIGNAL(textChanged(QString)), this, SLOT(setYawWid(QString)));

    pitch->setRange(0, 360);
    roll->setRange(0, 360);
    yaw->setRange(0, 360);
}
