#ifndef ADB_H
#define ADB_H

#include <QObject>
#include <QWidget>
#include <process.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <Psapi.h>
#include <string>
#include <QObject>
#include <QProcess>

static QString ServerIP;

class Adb : public QObject
{
    Q_OBJECT

public:
    Adb();
    ~Adb();

    bool CheckAndroidUsbByAdb();
    //bool GetMobileIP();
    QString get_localmachine_ip();
    bool ApplyServ();
    int AdbScreenShot();

    bool UninstallApp(QString package);
    void exportapk(QString package);

    bool checkPackagExist();

    void deletePic();

    static QString checkinfo;

    QString checkDevice();

signals:

    void signalCheck(QString str);
    void signalCheckIfAndirod(QString str);

private:

    QString m_name;
    QProcess *adbprocess;


};

#endif // ADB_H
