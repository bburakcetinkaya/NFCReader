#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QtAndroid>
#include <QByteArray>
#include "NFCReader.h"

#include <QQmlContext>
#include "NFCReader.h"

int main (int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    NFCReader nfcReader;
    engine.rootContext()->setContextProperty("NFCReader" ,&nfcReader);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);


    NFCReader nfcr;

    engine.rootContext()->setContextProperty("__nfcr",&nfcr);

#ifdef Q_OS_ANDROID
    QtAndroid::hideSplashScreen(200);
#endif
    return app.exec();
}
