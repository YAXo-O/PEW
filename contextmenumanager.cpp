#include "contextmenumanager.h"

void ContextMenuManager::addAction(const QString &title, action act)
{
    actions.addAction(title, act);
    actionsMenu->addAction(title);
    QObject::connect(actionsMenu, &QMenu::triggered, [this](QAction *act)mutable
    {
        static int called = 0;
        if(called % actions.actionsCount() == 0)
            actions.createItem(act->text(), actionsMenu->pos());
        called++;
    });
}

void ContextMenuManager::addVariable(const QString &title, action act)
{
    vars.addAction(title, act);
    varsMenu->addAction(title);
    QObject::connect(varsMenu, &QMenu::triggered, [this](QAction *act)mutable
    {
        static int called = 0;
        if(called % vars.actionsCount() == 0)
            vars.createItem(act->text(), varsMenu->pos());
        called++;
    });
}

void ContextMenuManager::setActionMenu(QMenu *menu)
{
    actionsMenu = menu;
}

void ContextMenuManager::setVariableMenu(QMenu *menu)
{
    varsMenu = menu;
}
