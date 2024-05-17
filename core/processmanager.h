#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "processmodel.h"
#include <QObject>
#include <QProcess>
#include <QSet>

/*
 * ProcessManager - singletone, запускающий дочерние потоки,
 * а так же предоставляющий доступ к ним
*/

class ProcessManager : public QObject
{
    Q_OBJECT

public:
    static ProcessManager *instance() noexcept { return self; }

    explicit ProcessManager(QObject *parent = nullptr);
    virtual ~ProcessManager();

    void setSearchStrings(const QStringList &strings);
    QStringList getSearchStrings() const;

    qint64 openProcess(const QString& programm, const QStringList& args = {}, ProcessModel::ProcessOptions options = ProcessModel::AlwaysRestart);

    ProcessModel *processModel(qint64 processId) const;
    QProcess* process(qint64 processId) const;
    ProcessModel::ProcessOptions processOptions(qint64 processId) const;

    const QList<ProcessModel*> processModels() const;

signals:
    void processCreated(ProcessModel* newProcess);

private:
    static ProcessManager *self;

    QSet<QString> m_searchStrings;
    QList<ProcessModel*> m_processModels;
};

#endif // PROCESSMANAGER_H
