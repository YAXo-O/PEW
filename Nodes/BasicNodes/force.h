#ifndef FORCE_H
#define FORCE_H

#include "../basenode.h"
#include "../externalvariable.h"

class Force : public BaseNode
{
    Q_OBJECT
public:
    explicit Force(QString name = "Force", QWidget *parent = nullptr);
    virtual ~Force() {}

public slots:
    void enable(BaseNode *caller) override;

private:
    ExternalVariable *system;
};

#endif // FORCE_H
