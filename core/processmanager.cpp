#include "processmanager.h"

#include <execution>

ProcessManager::ProcessManager(QObject *parent)
    : QObject{parent}, m_processesData{}
{
    Q_ASSERT_X(!ProcessManager::self, "ProcessManager", "there should be only one object");

    ProcessManager::self = this;
}

void ProcessManager::openProcess(const QString& programm, const QStringList& args, ProcessOptions options)
{
    QProcess* process = new QProcess(this);

    auto onExit = [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        Q_UNUSED(exitCode);
        Q_UNUSED(exitStatus);
        ProcessOptions options = getProcessOptions(process);
        if (options.testFlag(ProcessOption::RestartOnExit))
            process->start();
    };

    auto onError = [this, process](QProcess::ProcessError error) {
        Q_UNUSED(error);
        ProcessOptions options = getProcessOptions(process);
        if (options.testFlag(ProcessOption::RestartOnError))
            process->start();
    };

    connect(process, &QProcess::finished, this, onExit);
    connect(process, &QProcess::errorOccurred, this, onError);

    m_processesData.append({process, options});

    process->start(programm, args);
}

ProcessManager::ProcessOptions ProcessManager::getProcessOptions(QProcess *process) const
{
    auto predicate = [process](ProcessData data){ return data.process == process; };
    auto iterator = std::find_if(m_processesData.cbegin(), m_processesData.cend(), predicate);

    if (iterator == m_processesData.cend())
        return ProcessOption::AlwaysClose;

    return iterator->options;
}
