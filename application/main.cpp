#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QProcess>

#include "processmanager.h"
#include "qsettings.h"

const QStringView iniFileName = u"settings.ini"_qs;

int main(int argc, char *argv[])
{
    const QUrl url(u"qrc:/ProcessManager/Main.qml"_qs);

    QGuiApplication app(argc, argv);

    ProcessManager processManager(&app);

    QString pathToIniFile = QString("%1/%2")
                                .arg(app.applicationDirPath(), iniFileName);
    QSettings settings(pathToIniFile, QSettings::IniFormat);

    QStringList appList = settings.value("apps").toStringList();
    QStringList searchList = settings.value("search").toStringList();

    qDebug() << "Список приложений:" << appList.join(',');
    qDebug() << "Ключевые слова:" << searchList.join(',');

    processManager.setSearchStrings(searchList);

    for(const QString &app : appList)
    {
        processManager.openProcess(app);
    }

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
