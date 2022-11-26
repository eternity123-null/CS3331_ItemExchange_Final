QT       += core gui
QT       += sql
Qt       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additem.cpp \
    database.cpp \
    itemclassmanage.cpp \
    logindig.cpp \
    main.cpp \
    mainwindow.cpp \
    newuserappr.cpp \
    signup.cpp \
    usermainwindow.cpp \
    usermanage.cpp

HEADERS += \
    additem.h \
    database.h \
    itemclassmanage.h \
    logindig.h \
    mainwindow.h \
    newuserappr.h \
    signup.h \
    usermainwindow.h \
    usermanage.h

FORMS += \
    additem.ui \
    itemclassmanage.ui \
    logindig.ui \
    mainwindow.ui \
    newuserappr.ui \
    signup.ui \
    usermainwindow.ui \
    usermanage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
