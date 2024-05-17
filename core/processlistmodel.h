#ifndef PROCESSLISTMODEL_H
#define PROCESSLISTMODEL_H

#include "processmodel.h"
#include <QProcess>
#include <QAbstractListModel>

/*
 * Модель, позваляющая работать со списком ProcessModels
*/

class ProcessListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        Id = Qt::UserRole + 0,
        Model = Qt::UserRole + 1,
    };
    Q_ENUM(Roles)

    explicit ProcessListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ProcessModel*> m_models;

    void insert(ProcessModel *process);
    void onProcessCreated(ProcessModel *process);
};

#endif // PROCESSLISTMODEL_H
