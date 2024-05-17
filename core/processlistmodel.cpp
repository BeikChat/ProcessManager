#include "processmanager.h"
#include "processlistmodel.h"

ProcessListModel::ProcessListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    ProcessManager* processManager = ProcessManager::instance();

    const QList<ProcessModel *> processModels = processManager->processModels();

    for (ProcessModel* processModel : processModels)
        insert(processModel);

    connect(processManager, &ProcessManager::processCreated, this, &ProcessListModel::onProcessCreated);
}

int ProcessListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_models.count();
}

QVariant ProcessListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_models.size())
        return QVariant();

    ProcessModel *model = m_models.at(index.row());

    switch(role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return model->title();
        case Id:
            return model->id();
        case Model:
            return QVariant::fromValue(model);
    }

    return QVariant();
}

QHash<int, QByteArray> ProcessListModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = {
        { Id, "processId" },
        { Model, "processModel" }
    };

    roleNames.insert(QAbstractListModel::roleNames());

    return roleNames;
}

void ProcessListModel::insert(ProcessModel *process)
{
    m_models.append(process);
}

void ProcessListModel::onProcessCreated(ProcessModel *process)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    insert(process);

    endInsertRows();
}
