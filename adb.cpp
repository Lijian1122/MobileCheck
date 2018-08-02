#include "adb.h"
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QCoreApplication>
#include <qstringlist.h>
#include <QMessageBox>
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QtNetwork>
#include <QList>
#include <Tlhelp32.h>
#include <Windows.h>
#include <QByteArray>
#include <QMessageBox>
#include <MyMessageBox/mymessagebox.h>
#include <QIcon>

QString Adb::checkinfo;
Adb::Adb()
{
    adbprocess = new QProcess;
}

Adb::~Adb()
{

}


//检测是否有安卓设备序列
QString Adb::checkDevice()
{

     qDebug()<<"Check Android";

     QProcess *process = new QProcess;

     QString device = "adb/adb.exe";

     device +=  " devices";

     process->start(device);

     if(!process->waitForFinished(3000))
     {

         qDebug()<<"install error";
         QString str = "install error";

         process->kill();
         process->close();
         return str;
     }else
     {
         QString output =QString::fromLocal8Bit(process->readAll());

         if(!output.isEmpty())
         {

             qDebug()<<output;

             process->kill();
             process->close();
             return output;

         }else
         {
             process->kill();
             process->close();
             return NULL;
         }
     }
}


bool Adb::CheckAndroidUsbByAdb()
{

    QString str  = checkDevice();

    qDebug()<<"Device:"<<str;


    qDebug()<<"Adb Start";

    QProcess *process = new QProcess;

    QString program = "adb/adb.exe";

    QString device = "adb/adb.exe";

    device +=  " devices";

    process->start(device);


    process->kill();
    process->close();

    //安装APK文件
    program += " install";
    program += " APKFile/app-release.apk";
    qDebug()<<program;
    process->start(program);


    if(!process->waitForFinished(8000))
    {

        qDebug()<<"install error";
        return false;
    }else
    {
        QString output =QString::fromLocal8Bit(process->readAllStandardOutput());

        QString str = "Success";

        qDebug()<<output;

        if(output.contains(str))
        {

            process->kill();
            process->close();

            program = "adb/adb.exe";

            program = program + " shell am start -n com.forsuntech.secchkphone/com.forsuntech.secchkphone.MainActivity";

            qDebug()<<program;
            process->start(program);

            QString outputcheck =QString::fromLocal8Bit(process->readAll());

            Adb::checkinfo = QStringLiteral("请开始进行检测！");

            qDebug()<<outputcheck<<"checkinfo";

            return true;

        }else
        {
            return false;
        }
    }

}

//卸载APK
bool Adb::UninstallApp(QString package)
{
    qDebug()<<"Adb Start";

    QProcess *process = new QProcess;

    //QString program = "../adb/adb.exe";
    QString program = "adb/adb.exe";


    //卸载APK文件
    program += " uninstall ";
    program = program.append(package);
    qDebug()<<program;

    QMessageBox box(QMessageBox::Warning,QStringLiteral("卸载提示"),QStringLiteral("确定要卸载该应用吗？"));
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
    box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
    box.setWindowIcon(QIcon("screen/unstall.ico"));

    if(box.exec() == QMessageBox::Ok)
    {
        process->start(program);
        box.close();
        return true;
    }else
    {
        box.close();
        return false;
    }

    if(!process->waitForFinished(-1))
    {
       return false;
    }else
    {
        //QString output =QString::fromLocal8Bit(process->readAllStandardError());

        QString output1 =QString::fromLocal8Bit(process->readAll());

        qDebug()<<output1<<"xixi";


        return true;
    }
}

//检测安装包是否存在
bool Adb::checkPackagExist()
{

    qDebug()<<"Adb check";

    QProcess *process = new QProcess;

    QString program = "adb/adb.exe";

    QString checkResult = "";

    //QString checkResult1 ="Starting: Intent { cmp=com.forsuntech.secchkphone/.MainActivity }\r\r\nWarning: Activity not started, its current task has been brought to the front\r\r\n";

    //卸载手机应用
    //program += " shell pm list packages";
    program += " shell pm list package -3";

    qDebug()<<program;

    process->start(program);

    if(!process->waitForFinished(-1))
    {
       return false;
    }else
    {

        checkResult =QString::fromLocal8Bit(process->readAll());

        qDebug()<<checkResult<<"xixi";

        QString str = "com.forsuntech.secchkphone";
        if(checkResult.contains(str))
        {
             qDebug()<<"应用已经安装";

             process->kill();
             process->close();

             QString program1 = "adb/adb.exe";

             program1 = program1 + " shell am start -n com.forsuntech.secchkphone/com.forsuntech.secchkphone.MainActivity";

             qDebug()<<program1;
             process->start(program1);

             QString outputcheck =QString::fromLocal8Bit(process->readAll());

             qDebug()<<outputcheck<<"checkinfo";

             return true;
        }else
        {
            qDebug()<<"应用没有安装";
            return false;
        }
    }
}

//bool  Adb::GetMobileIP()
//{

//    qDebug()<<"start GetIP";

//    QProcess *adbprocess = new QProcess;
//    QString IPAddr = NULL;
//    int i = 0;

//    get_localmachine_ip();

//    QString program = "../adbfile/adb.exe";
//    program += " shell netcfg";

//    adbprocess->start(program);

//    if(!adbprocess->waitForFinished(-1))
//    {
//       return false;
//    }else
//    {
//        QByteArray output0 =adbprocess->readAll();
//        QByteArray cstr(output0);
//        QString s = cstr;
//        if(s != NULL)
//        {

//           //QString outi= output0.at(i);
//           for(i=46;i<55;i++)
//           {
//              ServerIP += output0.at(i);

//           }
//           qDebug()<<s<<"*********";
//           qDebug()<<ServerIP<<"++++++++";
//        }else
//        {
//            qDebug()<<"NetConfig is Empty";
//        }

//    }

//}


bool Adb::ApplyServ()
{

    qDebug()<<"start ApplyServ";

    QProcess *process = new QProcess;

    //QProcess *adbprocess = new QProcess;
    QString startserv = NULL;


    //QString program = "../adb/adb.exe";
    QString program = "adb/adb.exe";

    QString port = program + " shell am broadcast -a NotifyServiceStop";
    qDebug()<<port;
    process->start(port);
    QString output0 =QString::fromLocal8Bit(process->readAll());
    qDebug()<<output0;
    process->kill();
    process->close();

    //端口转换
    QString PortChange = program + " forward tcp:12580 tcp:10086";

    qDebug()<<"restart :"<<PortChange;
    process->start(PortChange);


    if(!process->waitForFinished(-1))
    {
       return false;
    }else
    {
        QString output =QString::fromLocal8Bit(process->readAllStandardError());
        qDebug()<<output;
        process->close();

    }

    startserv = program.append(" shell am broadcast -a NotifyServiceStart");
    qDebug()<<"restart server:"<<startserv;

    process->start(startserv);

    if(!process->waitForFinished(-1))
    {
       return false;
    }else
    {
        QString output =QString::fromLocal8Bit(process->readAll());
        qDebug()<<output;

        return true;
    }

}

//导出APK文件
void Adb::exportapk(QString package)
{
    qDebug()<<"start ExportAPK";

    QProcess *adbprocess = new QProcess;

    QString program = "../adb/adb.exe";

    //将手机APK文件推送到PC客户端
    QString exportapk = program.append(" pull /sdcard/");
    exportapk = exportapk.append(package).append(" ApkFile");

    adbprocess->start(exportapk);

    if(!adbprocess->waitForFinished(-1))
    {
       return ;
    }else
    {
        QString output =QString::fromLocal8Bit(adbprocess->readAllStandardError());
        qDebug()<<output;
        return;
    }


}

//实时获取手机截图
int Adb::AdbScreenShot()
{

    qDebug()<<"start AdbScreenShot";

    //获取截图手机本地文件
    QProcess *adbprocess = new QProcess;

    QString program = "adb/adb.exe";
    //QString image =  program + " shell netcfg";
    QString port = program + " shell screencap -p /sdcard/screenshot.png";

    qDebug()<<"port:"<<port;

    adbprocess->start(port);

    if(!adbprocess->waitForFinished(-1))
    {
       return false;
    }else
    {
        QString output0 =QString::fromLocal8Bit(adbprocess->readAllStandardError());
        qDebug()<<output0;

    }

    //将手机本地截图推送到PC客户端
    QString picture = program.append(" pull /sdcard/screenshot.png ScreenImage");

    qDebug()<<"start :"<<picture;
    adbprocess->start(picture);

    if(!adbprocess->waitForFinished(-1))
    {
       return 0;
    }else
    {
        QString output =QString::fromLocal8Bit(adbprocess->readAllStandardError());
        qDebug()<<output;
        return 1;
    }

}

void Adb::deletePic()
{

    qDebug()<<"start AdbScreenShot";

    //获取截图手机本地文件
    QProcess *adbprocess = new QProcess;

    QString program = "adb/adb.exe";

    //将手机本地截图进行删除
    QString picture = program.append(" shell rm /sdcard/screenshot.png");

    qDebug()<<"delete pic:"<<picture;
    adbprocess->start(picture);

    if(!adbprocess->waitForFinished(-1))
    {
       return;
    }else
    {
        QString output =QString::fromLocal8Bit(adbprocess->readAllStandardError());
        qDebug()<<output;
        return;
    }

}


QString Adb::get_localmachine_ip()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qDebug()<<"IP"<<ipAddress;
    return ipAddress;
}


