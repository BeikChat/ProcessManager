#ifndef QMLPROCESSMANAGERSINGLETON_H
#define QMLPROCESSMANAGERSINGLETON_H

#include <QObject>
#include <QQmlEngine>

class QmlProcessManagerSingleton : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ProcessListModel* processList READ processList NOTIFY processListChanged)

    QML_SINGLETON
    QML_NAMED_ELEMENT(ProcessManager)

public:
    explicit QmlProcessManagerSingleton(QObject *parent = nullptr);

signals:

};

#endif // QMLPROCESSMANAGERSINGLETON_H
