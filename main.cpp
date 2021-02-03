#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include <QApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QTranslator>
#include <QFile>
#include <QStyleFactory>
#include <QSettings>

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
    translator.load(QString(":/i18n_") + QLocale::system().name());
    app.installTranslator(&translator);
    QTranslator translatorQt;
    translatorQt.load(QString("translations/qt_") + QLocale::system().name());
    app.installTranslator(&translatorQt);
    QTranslator translatorWebEngine;
    translatorWebEngine.load(QString(":/qtwebengine_") + QLocale::system().name());
    app.installTranslator(&translatorWebEngine);

#ifdef Q_OS_WIN
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",QSettings::NativeFormat);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    if(settings.value("AppsUseLightTheme")==0){
        QPalette darkPalette;
        QColor darkColor = QColor(43,43,43);
        QColor disabledColor = QColor(127,127,127);
        darkPalette.setColor(QPalette::Window, darkColor);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(32,32,32));
        darkPalette.setColor(QPalette::AlternateBase, darkColor);
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
        darkPalette.setColor(QPalette::Button, darkColor);
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

        qApp->setPalette(darkPalette);

        qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    }
#endif

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
    userAgent.replace(userAgent.indexOf(qtUA),qtUA.length(),QString("Pd2Browser/").append(__APP_VERSION__));
    QWebEngineProfile::defaultProfile()->setHttpUserAgent(userAgent);
#endif

    QUrl url = commandLineUrlArgument();

    Browser browser;
    BrowserWindow *window = browser.createWindow();
    window->tabWidget()->setUrl(url);

    return app.exec();
}
