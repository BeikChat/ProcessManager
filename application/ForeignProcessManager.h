#ifndef FOREIGNPROCESSMANAGER_H
#define FOREIGNPROCESSMANAGER_H

#include "processmanager.h"
#include "processmodel.h"
#include <QtQmlIntegration>
#include <QObject>

/*
 * Обёртка над ProcessManager для QML
*/

class ForeignProcessManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(ProcessManager)

public:
    explicit ForeignProcessManager(QObject *parent = nullptr)
        : QObject(parent), m_processManagerInstance(ProcessManager::instance())
    {
    }

    Q_INVOKABLE void createProcess(const QString& programm)
    {
        m_processManagerInstance->openProcess(programm);
    }

    Q_INVOKABLE ProcessModel* processModel(quint64 processId) const
    {
        return m_processManagerInstance->processModel(processId);
    }

private:
    ProcessManager* m_processManagerInstance;
};

#endif // FOREIGNPROCESSMANAGER_H
