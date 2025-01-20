#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <loglib/loglib.h>
#include "entrymodel.h"

int main(int argc, char *argv[])
{
    loglib::logger().setName("dictionary");
    loglib::logger().registerLogger(logging::LOGGER_FILE);

    QGuiApplication app(argc, argv);
    qmlRegisterType<EntryModel>("sgy.pine.dictionary", 1, 0, "EntryModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/dictionary/qml/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
