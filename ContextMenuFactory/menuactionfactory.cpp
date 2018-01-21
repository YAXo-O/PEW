#include "menuactionfactory.h"

void MenuActionFactory::createItem(const QString &title, const QPoint &pos)
{
    if(actions.contains(title))
        actions[title](pos);
}

void MenuActionFactory::addAction(const QString &title, action act)
{
    if(actions.contains(title))
        throw std::invalid_argument("Duplicates are not allowed!");

    actions[title] = act;
}

int MenuActionFactory::actionsCount() const
{
    return actions.count();
}
