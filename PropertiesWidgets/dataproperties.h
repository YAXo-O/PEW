#ifndef DATAPROPERTIES_H
#define DATAPROPERTIES_H

#include <QWidget>
#include <QGroupBox>
#include "labeledinput.h"

class DataProperties : public QWidget
{
    Q_OBJECT
public:
    explicit DataProperties(QWidget *parent = nullptr);

    void setConnections();

    void setNameLabel(const QString &name);
    void setNameLabel(const QString &&name);
    QString getNameLabel() const;
    void setNameInput(const QString &name);
    void setNameInput(const QString &&name);
    QString getNameInput() const;
    void setDescriptionLabel(const QString &description);
    void setDescriptionLabel(const QString &&description);
    QString getDescriptionLabel() const;
    void setDescriptionInput(const QString &name);
    void setDescriptionInput(const QString &&name);
    QString getDescriptionInput() const;
    void setGroupName(const QString &name);
    void setGroupName(const QString &&name);
    QString getGroupName() const;

    LabeledInput *getVarName() const;
    LabeledInput *getVarDescription() const;
    QGroupBox *getGroup() const;

private:
    QGroupBox *box;
    LabeledInput *varName;
    LabeledInput *varDescription;

signals:
    void nameChanged(const QString newName);
    void descriptionChanged(const QString newDescr);

};

#endif // DATAPROPERTIES_H
