#include "processlistmodel.h"

ProcessListModel::ProcessListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int ProcessListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_models.count();
}

QVariant ProcessListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    if (row >= m_models.size())
        return QVariant();

    const ProcessModel *model = m_models.at(index.row());

    switch(role) {
        case Qt::DisplayRole:
            return model->title();
        case Qt::EditRole:
            return model->title();
        case StandartOutput:
            return model->standartOutput();
        case ErrorOutput:
            return model->errorOutput();
    }

    if (role == Qt::DisplayRole)
        return model.content();
    else if (role == Qt::EditRole)
        return model.content();
    else if (role == IdRole)
        return model.id();
    else if (role == UuidRole)
        return model.uuid();
    else if (role == CreationDateRole)
        return model.creationDate();
    else if (role == UpdateDateRole)
        return model.updateDate();
    else if (role == ContentRole)
        return model.content();

    return QVariant();
}
