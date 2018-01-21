#ifndef MENUACTIONFACTORY_H
#define MENUACTIONFACTORY_H

#include <QHash>
#include <QPoint>

typedef void (*action)(QPoint);

class MenuActionFactory
{
public:
    MenuActionFactory() = default;
    virtual ~MenuActionFactory() {}

    virtual void createItem(const QString &title, const QPoint &pos);
    void addAction(const QString &title, action act);

    int actionsCount() const;

private:
    QHash<QString, action> actions;
};

#endif // MENUACTIONFACTORY_H
