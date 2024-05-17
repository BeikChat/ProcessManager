#ifndef FOREIGNPROCESSMODEL_H
#define FOREIGNPROCESSMODEL_H

#include "processmodel.h"
#include <QQmlEngine>

/*
 * Обёртка над ProcessModel для QML
*/

struct ForeignProcessModel
{
    Q_GADGET
    QML_FOREIGN(ProcessModel)
    QML_NAMED_ELEMENT(ProcessModel)
    QML_UNCREATABLE("ProcessModel is uncreatable")
};

#endif // FOREIGNPROCESSMODEL_H
