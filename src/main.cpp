#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <include/TreeModel.h>
#include <include/TreeItem.h>

#include "TreeItem.h"
#include "TreeModel.h"

#include "MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
//        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//        QGuiApplication app(argc, argv);
//        QQmlApplicationEngine engine;
//        engine.addImportPath(":/qml");
//        TreeModel treeModel;
//        engine.rootContext()->setContextProperty("_myTreeModel", &treeModel);
//        const QUrl url(QStringLiteral("qrc:/main.qml"));
//        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                         &app, [url](QObject *obj, const QUrl &objUrl) {
//            if (!obj && url == objUrl)
//                QCoreApplication::exit(-1);
//        }, Qt::QueuedConnection);
//        engine.load(url);

//        return app.exec();

    QApplication a(argc, argv);
//    QQmlApplicationEngine engine;
//    engine.addImportPath(":/qml");
//    TreeModel treeModel;
//    engine.rootContext()->setContextProperty("_myTreeModel", &treeModel);

////    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//    {
//        printf("empty\n");
//        return -1;
//    }
    MainWindow w;
    w.show();
    return a.exec();
}
