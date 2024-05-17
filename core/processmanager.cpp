#include "processmanager.h"
#include "qdebug.h"

#include <execution>

ProcessManager *ProcessManager::self = nullptr;

ProcessManager::ProcessManager(QObject *parent)
    : QObject(parent), m_processModels(), m_searchStrings()
{
    Q_ASSERT_X(!ProcessManager::self, typeid(ProcessManager).name(), "there should be only one object");

    ProcessManager::self = this;
}

ProcessManager::~ProcessManager()
{
}

void ProcessManager::setSearchStrings(const QStringList &strings)
{
    m_searchStrings = QSet<QString>(strings.constBegin(), strings.constEnd());
}

QStringList ProcessManager::getSearchStrings() const
{
    return m_searchStrings.values();
}

qint64 ProcessManager::openProcess(const QString& programm, const QStringList& args, ProcessModel::ProcessOptions options)
{
    ProcessModel * processModel = new ProcessModel(programm, args, options, this);

    m_processModels.append(processModel);

    processModel->start();

    emit processCreated(processModel);

    return processModel->id();
}

ProcessModel *ProcessManager::processModel(qint64 processId) const
{
    auto predicate = [processId](ProcessModel *model){ return model->process()->processId() == processId; };
    auto iterator = std::find_if(m_processModels.cbegin(), m_processModels.cend(), predicate);

    if (iterator == m_processModels.cend())
        return nullptr;

    return (*iterator);
}

QProcess *ProcessManager::process(qint64 processId) const
{
    ProcessModel *model = processModel(processId);
    if (model == nullptr)
        return nullptr;

    return model->process();
}

ProcessModel::ProcessOptions ProcessManager::processOptions(qint64 processId) const
{
    ProcessModel *model = processModel(processId);
    if (model == nullptr)
        return ProcessModel::AlwaysClose;

    return model->options();
}

const QList<ProcessModel *> ProcessManager::processModels() const
{
    return m_processModels;
}
