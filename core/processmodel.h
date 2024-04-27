#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QObject>
#include <QProcess>

class ProcessModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString standartOutput READ standartOutput NOTIFY standartOutputChanged)
    Q_PROPERTY(QString errorOutput READ errorOutput NOTIFY errorOutputChanged)

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

    ProcessModel(QProcess *process, QObject *parent = nullptr);
    ~ProcessModel();

    QString title() const;
    QString standartOutput() const;
    QString errorOutput() const;

private slots:

signals:
    void titleChanged();
    void standartOutputChanged();
    void errorOutputChanged();

private:
    QProcess* m_process;
    ProcessOptions m_oprions;
};

#endif // PROCESSMODEL_H
