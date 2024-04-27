#ifndef PROCESSLISTMODEL_H
#define PROCESSLISTMODEL_H

#include <QAbstractListModel>
#include "processmodel.h"

class ProcessListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        StandartOutput = Qt::UserRole + 0,
        ErrorOutput = Qt::UserRole + 1,
    };
    Q_ENUM(Roles)

    explicit ProcessListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ProcessModel*> m_models;
};

#endif // PROCESSLISTMODEL_H
