#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QProcess>

#include "processmanager.h"

int main(int argc, char *argv[])
{
    const QUrl url(u"qrc:/ProcessManager/qml/Main.qml"_qs);

    QGuiApplication app(argc, argv);

    ProcessManager processManager(&app);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
