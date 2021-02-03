TEMPLATE = app
TARGET = pd2browser
QT += webenginewidgets
VERSION = 0.1.7

DEFINES += __APP_VERSION__=\\\"'$$VERSION'\\\"

HEADERS += \
    browser.h \
    browserwindow.h \
    downloadmanagerwidget.h \
    downloadwidget.h \
    tabwidget.h \
    webpage.h \
    webpopupwindow.h \
    webview.h

SOURCES += \
    browser.cpp \
    browserwindow.cpp \
    downloadmanagerwidget.cpp \
    downloadwidget.cpp \
    main.cpp \
    tabwidget.cpp \
    webpage.cpp \
    webpopupwindow.cpp \
    webview.cpp

FORMS += \
    certificateerrordialog.ui \
    passworddialog.ui \
    downloadmanagerwidget.ui \
    downloadwidget.ui

RC_ICONS = data/Logo.ico

TRANSLATIONS += data/i18n_zh.ts

RESOURCES += data/pd2browser.qrc
