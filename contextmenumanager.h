#ifndef CONTEXTMENUMANAGER_H
#define CONTEXTMENUMANAGER_H

#include <QString>
#include <QPoint>
#include <QMenu>
#include "ContextMenuFactory/menuactionfactory.h"

class ContextMenuManager
{
public:
    ContextMenuManager() = default;

    void addAction(const QString &title, action act);
    void addVariable(const QString &title, action act);
    void setActionMenu(QMenu *menu);
    void setVariableMenu(QMenu *menu);

private:
    MenuActionFactory actions;
    MenuActionFactory vars;
    QMenu *actionsMenu;
    QMenu *varsMenu;
};

#endif // CONTEXTMENUMANAGER_H
