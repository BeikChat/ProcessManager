#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QObject>
#include <QProcess>

/*
 * ProcessModel - Объект, который управляет конкретным потоком
 * Выполняет поиск по строке в выводе,
 * а так же перезапускает процессы по необходимости
*/

class ProcessModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint64 id READ id NOTIFY idChanged)
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

    explicit ProcessModel(const QString& programm, const QStringList& args, ProcessOptions options, QObject *parent = nullptr);
    virtual ~ProcessModel();

    qint64 id() const;
    QString title() const;

    QProcess* process() const;
    ProcessOptions options() const;

    QString standartOutput() const;
    QString errorOutput() const;

    void start();
    void close();
    void restart();

private slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessError(QProcess::ProcessError error);
    void onProcessStateChanged(QProcess::ProcessState state);

    void onReadyReadStandartOutput();
    void onReadyReadErrorOutput();

signals:
    void idChanged();
    void titleChanged();

    void standartOutputChanged();
    void errorOutputChanged();

private:
    void restartOnFind(const QString &outputString, const QStringList &searchStrings);

    void print(QByteArray byteArray);
    void printLine(QByteArray byteArray);
    void printError(QByteArray byteArray);
    void printErrorLine(QByteArray byteArray);

    QProcess* m_process;
    ProcessOptions m_options;

    bool m_closing;

    QByteArray m_standartOutput;
    QByteArray m_errorOutput;

    QVector<QMetaObject::Connection> m_connections;
};

#endif // PROCESSMODEL_H
