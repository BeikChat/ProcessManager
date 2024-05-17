#ifndef FOREIGNPROCESSLISTMODEL_H
#define FOREIGNPROCESSLISTMODEL_H

#include "processlistmodel.h"
#include <QQmlEngine>

/*
 * Обёртка над ProcessListModel для QML
*/

struct ForeignProcessListModel
{
    Q_GADGET
    QML_FOREIGN(ProcessListModel)
    QML_NAMED_ELEMENT(ProcessListModel)
};

#endif // FOREIGNPROCESSLISTMODEL_H
