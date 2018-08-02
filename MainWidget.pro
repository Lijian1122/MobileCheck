QT    +=gui
QT    += core gui
QT    += network
QT    += script
QT    += sql
QT    += printsupport

QT    +=axcontainer
CONFIG += axcontainer

RC_ICONS =screen/logo.ico

LIBS +=User32.LIB
LIBS +="hid/hid.lib"
#LIBS+= qrcodelib.lib

LIBS+= qrcodelib.lib
#LIBS+= qrcodelib.dll

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MobileCheck
#MainWidget
TEMPLATE = app

INCLUDEPATH += $$PWD/include
include(Protocal/Protocal.pri)

INCLUDEPATH += $$PWD/include
include(parseJson/parseJson.pri)

INCLUDEPATH += $$PWD/include
include(Database/Database.pri)

INCLUDEPATH += $$PWD/include
include(Common/Common.pri)

INCLUDEPATH += $$PWD/include
include(Mesgbox/MsgBox.pri)

INCLUDEPATH += $$PWD/include
include(exportword/QWord.pri)

INCLUDEPATH += $$PWD/include
include(LoginWidget/LoginWidget.pri)

INCLUDEPATH += $$PWD/include
include(QrcodeGenerate/QrcodeGenerate.pri)

INCLUDEPATH += $$PWD/include
include(QPrintQcrode/QPrintQcrode.pri)

#INCLUDEPATH += $$PWD/include
#include(MyMessageBox/MyMessageBox.pri)

SOURCES += main.cpp \
    mainwidget.cpp \
    upwidget.cpp \
    downwidget.cpp \
    maskmainwidget.cpp \
    mybutton.cpp \
    adb.cpp \
    socket.cpp \
    mainwidgetfunc.cpp \
    homewidgetfun.cpp \
    safecheckfun.cpp \
    safecheckreslult.cpp \
    checkallinfowidget.cpp \
    countcheckinfo.cpp \
    qrcodecheckinfo.cpp \
    tcpthread.cpp \
    homethread.cpp

HEADERS += \
    mainwidget.h \
    upwidget.h \
    downwidget.h \
    maskmainwidget.h \
    mybutton.h \
    adb.h \
    socket.h \
    tcpthread.h

RESOURCES += \
    source.qrc \
    pic.qrc

DISTFILES +=

