#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include <QApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QTranslator>
#include <QFile>

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("https://cn.bing.com/"));
}

int main(int argc, char **argv)
{
    QCoreApplication::setOrganizationName("");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":Logo.png")));

    QTranslator translator;
    translator.load(QString(":i18n_") + QLocale::system().name());
    app.installTranslator(&translator);
    QTranslator translatorWebEngine;
    translatorWebEngine.load(QString(":qtwebengine_") + QLocale::system().name());
    app.installTranslator(&translatorWebEngine);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled,true);
    //QWebEngineSettings::
#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled,true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::ScreenCaptureEnabled,true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent,true);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif
#if QT_VERSION >= QT_VERSION_CHECK(5 ,6 ,0)
    QString userAgent = QWebEngineProfile::defaultProfile()->httpUserAgent();
    QString qtUA = "QtWebEngine/";
    qtUA.append(qVersion());
    userAgent.replace(userAgent.indexOf(qtUA),qtUA.length(),"Pd2Browser/0.1.1");
    QWebEngineProfile::defaultProfile()->setHttpUserAgent(userAgent);
#endif

    QUrl url = commandLineUrlArgument();

    Browser browser;
    BrowserWindow *window = browser.createWindow();
    window->tabWidget()->setUrl(url);

    return app.exec();
}
