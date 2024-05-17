#include "processmanager.h"
#include "processmodel.h"
#include "qdebug.h"
#include "qtimer.h"

ProcessModel::ProcessModel(const QString& programm, const QStringList& args, ProcessOptions options, QObject *parent)
    : QObject(parent), m_process(new QProcess(this)), m_options(options), m_standartOutput(), m_errorOutput(), m_connections()
{
    m_process->setProgram(programm);
    m_process->setArguments(args);

    m_connections.reserve(5);

    m_connections.append(connect(m_process, &QProcess::finished, this, &ProcessModel::onProcessFinished));
    m_connections.append(connect(m_process, &QProcess::errorOccurred, this, &ProcessModel::onProcessError));
    m_connections.append(connect(m_process, &QProcess::stateChanged, this, &ProcessModel::onProcessStateChanged));

    m_connections.append(connect(m_process, &QProcess::readyReadStandardOutput, this, &ProcessModel::onReadyReadStandartOutput));
    m_connections.append(connect(m_process, &QProcess::readyReadStandardError, this, &ProcessModel::onReadyReadErrorOutput));
}

ProcessModel::~ProcessModel()
{
    for( const auto &connection : m_connections)
        disconnect(connection);

    m_process->terminate();
    if (!m_process->waitForFinished(3000))
    {
        qDebug() << "Killing process:" << m_process->processId();
        m_process->kill();
        m_process->waitForFinished();
    }
}

qint64 ProcessModel::id() const
{
    return m_process->processId();
}

QString ProcessModel::title() const
{
    return m_process->program();
}

QProcess *ProcessModel::process() const
{
    return m_process;
}

ProcessModel::ProcessOptions ProcessModel::options() const
{
    return m_options;
}

QString ProcessModel::standartOutput() const
{
    return QString(m_standartOutput);
}

QString ProcessModel::errorOutput() const
{
    return QString(m_errorOutput);
}

void ProcessModel::start()
{
    m_closing = false;

    m_process->start();
}

void ProcessModel::close()
{
    // Отключаем перезапуск по завершении или ошибке
    m_closing = true;

    m_process->terminate();

    auto killProcess = [this](){
        if (m_process->state() == QProcess::NotRunning)
            return;

        qDebug() << "Can't close process " << m_process->processId() << ". Killing...";
        m_process->kill();
        m_process->waitForFinished();
        // Возвращаем предыдущее состояние
        m_closing = false;
    };

    // Запускаем таймер, чтоб не блокировать основой поток
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, killProcess, Qt::SingleShotConnection);
    timer->start(3000);

    auto killTimer = [timer, this]() {
        timer->stop();
        timer->deleteLater();

        m_closing = false;
    };

    // Отключаем таймер, если процесс завершился
    connect(m_process, &QProcess::finished, this, killTimer, Qt::SingleShotConnection);
}

void ProcessModel::restart()
{
    qDebug() << "Restarting process - " << id();

    if (m_process->state() != QProcess::NotRunning) {
        connect(m_process, &QProcess::finished, this, &ProcessModel::start, Qt::SingleShotConnection);
        close();
    } else {
        start();
    }
}

void ProcessModel::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    printLine("-- Process finished --");
    if (m_options.testFlag(ProcessOption::RestartOnExit) && !m_closing)
        restart();
}

void ProcessModel::onProcessError(QProcess::ProcessError error)
{
    printLine("-- Process has some error --");
    if (m_options.testFlag(ProcessOption::RestartOnError) && !m_closing)
        restart();
}

void ProcessModel::onProcessStateChanged(QProcess::ProcessState state)
{
    switch(state){
        case QProcess::NotRunning:
            emit idChanged();
            break;
        case QProcess::Starting:
            printLine("--- Process starting ---");
            emit idChanged();
            break;
        case QProcess::Running:
            //printLine("--- Process running ---");
            break;
    }
}

void ProcessModel::onReadyReadStandartOutput()
{
    m_process->setReadChannel(QProcess::StandardOutput);
    QByteArray data = m_process->readAll();

    print(data);

    QStringList searchStrings = ProcessManager::instance()->getSearchStrings();
    restartOnFind(data, searchStrings);
}

void ProcessModel::onReadyReadErrorOutput()
{
    m_process->setReadChannel(QProcess::StandardError);
    QByteArray data = m_process->readAll();

    printError(data);

    QStringList searchStrings = ProcessManager::instance()->getSearchStrings();
    restartOnFind(data, searchStrings);
}

void ProcessModel::restartOnFind(const QString &outputString, const QStringList &searchStrings)
{
    for (const QString &string : searchStrings) {
        if (outputString.contains(string)) {
            restart();
            return;
        }
    }
}

void ProcessModel::print(QByteArray byteArray)
{
    m_standartOutput.append(byteArray);
    emit standartOutputChanged();
}

void ProcessModel::printLine(QByteArray byteArray)
{
    print(byteArray + "\n");
}

void ProcessModel::printError(QByteArray byteArray)
{
    m_errorOutput.append(byteArray);
    emit errorOutputChanged();
}

void ProcessModel::printErrorLine(QByteArray byteArray)
{
    printError(byteArray + "\n");
}
