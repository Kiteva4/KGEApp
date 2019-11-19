#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TreeItem.h"
#include "TreeModelTest.h"

#include "MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;
        engine.addImportPath(":/qml");
        TreeModelTest treeModel;
        engine.rootContext()->setContextProperty("_myTreeModel", &treeModel);
        const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        return app.exec();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
