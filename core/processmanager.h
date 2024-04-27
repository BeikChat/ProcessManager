#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QProcess>

class ProcessManager : public QObject
{
    Q_OBJECT

public:
    enum ProcessOption {
        CloseOnExit = 0x0000,
        RestartOnExit = 0x0001,

        CloseOnError = 0x0000,
        RestartOnError = 0x0002,

        AlwaysRestart = RestartOnExit | RestartOnError,
        AlwaysClose = CloseOnExit | CloseOnError,
    };
    Q_DECLARE_FLAGS(ProcessOptions, ProcessOption)

    static ProcessManager *instance() noexcept { return self; }

    explicit ProcessManager(QObject *parent = nullptr);

    void openProcess(const QString& programm, const QStringList& args = {}, ProcessOptions options = AlwaysRestart);
    QList<QProcess*> processes() const;

    ProcessOptions getProcessOptions(QProcess* process) const;

signals:

private:
    static ProcessManager *self;

    struct ProcessData {
        QProcess* process;
        ProcessOptions options;
    };

    QList<ProcessData> m_processesData;
};

#endif // PROCESSMANAGER_H
