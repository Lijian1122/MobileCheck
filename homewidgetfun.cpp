#include "downwidget.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QRect>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <Common/applist.h>
#include <QBitmap>
#include <QrcodeGenerate/qrcodegenerate.h>
#include <QDir>
#include <tcpthread.h>
#include <QWaitCondition>
#include <QMutex>

void downwidget::setHomePageshow()
{

    //截屏控件
    screenwidget = new QLabel(this->widget1);
    screenwidget->setFixedSize(270,525);
    screenwidget->setStyleSheet("background-image:url(:/source/Image/androidint.png)");
    screenwidget->setGeometry(25,35,270,525);

    //版本信息
    labelverson = new QLabel(QStringLiteral("   手机检测系统1.0版"),this->widget1);
    labelverson->setFixedSize(150,30);
    labelverson->setStyleSheet("color:rgb(68,68,68);font: 10pt,Microsoft YaHei;");
    labelverson->setGeometry((this->width()-130),this->height()-30,100,40);

    //手机状态控件
    moblestate = new QLabel(QStringLiteral("设备未连接"),this->widget1);
    moblestate->setFixedSize(550,55);
    moblestate->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    moblestate->setGeometry(364,42,235,55);


    //手机截屏工具

    QPixmap pixmap;
    pixmap.load("ScreenShot/screen.png");
    QPixmap fitpixmap=pixmap.scaled(240,428,Qt::KeepAspectRatio);
    labelscreen = new QLabel(this->widget1);
    labelscreen->setFixedSize(240,428);
    labelscreen->setPixmap(fitpixmap);
    labelscreen->setGeometry(42,88,240,425);

    //分割线框
    QWidget *cutoff1 = new QWidget(this->widget1);
    cutoff1->setFixedSize((this->maximumWidth()-350),2);
    cutoff1->setStyleSheet("background-image:url(:/source/Image/cutoff.jpg)");
    //cutoff1->setGeometry(350,105,930,2);
    cutoff1->setGeometry(350,105,(this->maximumWidth()-350),2);

    //连接手机时状态
//    QWidget *transwidegt = new QWidget(this->widget1);
//    transwidegt->setFixedSize(600,350);
//    transwidegt->setStyleSheet("background-image:url(:/source/Image/trans.jpg)");
//    transwidegt->setGeometry(370,170,600,350);


    //手机相关信息显示
    label1 = new QLabel(QStringLiteral("手机型号:"),this->widget1);
    label1->setFixedSize(130,40);
    label1->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label1->setGeometry(355,135,130,40);

    label2 = new QLabel(QStringLiteral("操作系统:"),this->widget1);
    label2->setFixedSize(90,40);
    label2->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label2->setGeometry(355,177,90,40);

    label3 = new QLabel(QStringLiteral("制造商:"),this->widget1);
    label3->setFixedSize(90,40);
    label3->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label3->setGeometry(355,219,90,40);

    label4 = new QLabel(QStringLiteral("系统版本:"),this->widget1);
    label4->setFixedSize(90,40);
    label4->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label4->setGeometry(355,261,90,40);

    label5 = new QLabel(QStringLiteral("SDK版本:"),this->widget1);
    label5->setFixedSize(90,40);
    label5->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label5->setGeometry(355,303,90,40);

    label6 = new QLabel(QStringLiteral("CPU型号:"),this->widget1);
    label6->setFixedSize(90,40);
    label6->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label6->setGeometry(355,345,90,40);

    label7 = new QLabel(QStringLiteral("MAC地址:"),this->widget1);
    label7->setFixedSize(90,40);
    label7->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label7->setGeometry(355,387,90,40);

    label8 = new QLabel(QStringLiteral("运营商:"),this->widget1);
    label8->setFixedSize(90,40);
    label8->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label8->setGeometry(355,429,90,40);

    label9 = new QLabel(QStringLiteral("是否Root:"),this->widget1);
    label9->setFixedSize(100,40);
    label9->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label9->setGeometry(355,471,100,40);

    label11 = new QLabel(this->widget1);
    label11->setFixedSize(300,40);
    label11->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label11->setGeometry(455,135,150,40);

    label21 = new QLabel(this->widget1);
    label21->setFixedSize(90,40);
    label21->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label21->setGeometry(455,177,90,40);

    label31= new QLabel(this->widget1);
    label31->setFixedSize(90,40);
    label31->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label31->setGeometry(445,219,90,40);

    label41 = new QLabel(this->widget1);
    label41->setFixedSize(90,40);
    label41->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label41->setGeometry(455,261,90,40);

    label51 = new QLabel(this->widget1);
    label51->setFixedSize(90,40);
    label51->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label51->setGeometry(455,303,90,40);

    label61 = new QLabel(this->widget1);
    label61->setFixedSize(120,40);
    label61->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label61->setGeometry(455,345,120,40);

    label71 = new QLabel(this->widget1);
    label71->setFixedSize(250,40);
    label71->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label71->setGeometry(455,387,190,40);

    label81 = new QLabel(this->widget1);
    label81->setFixedSize(90,40);
    label81->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label81->setGeometry(445,429,90,40);

    label91 = new QLabel(this->widget1);
    label91->setFixedSize(90,40);
    label91->setStyleSheet("color:rgb(68,68,68);font: 16pt,Microsoft YaHei;");
    label91->setGeometry(465,471,90,40);

    m_qrcode = new QrcodeGenerate(this->widget1);


    m_qrcode->setGeometry((this->width()-330),150,300,300);

    QString saveFileName= QDir::currentPath();

    QString pathname = saveFileName.append("/QrcodeImage/").append("qrcode").append(".png");

    m_qrcode->saveImage(pathname);


    saveqrcode = new QPushButton(this->widget1);
    saveqrcode->setFixedSize(125,45);
    //saveqrcode->setStyleSheet("background-image:url(:/skin/source/icon1/save.png);background-color:transparent;");
    saveqrcode->setStyleSheet("background-color:transparent;");
    saveqrcode->setGeometry((this->width()- 245),476,145,50);

    connect(saveqrcode,SIGNAL(clicked()),this,SLOT(slotQrcodeSave()));

}

void downwidget::slotMobileState(QString str)
{
     qDebug()<<"请开始进行检测！！！";
     moblestate->setText(str);    
}
void downwidget::ScreenShotShow()
{
    //开始截图
    m_adb->AdbScreenShot();

    //显示当前截图
    QPixmap pixmap;
    pixmap.load("ScreenImage/screenshot.png");
    QPixmap fitpixmap=pixmap.scaled(240,428,Qt::KeepAspectRatio);
    labelscreen->setPixmap(fitpixmap);

    //删除手机截图
    m_adb->deletePic();

}
void downwidget::slotHomePageshow2()
{

    checkbutton->setEnabled(false);

    AppList::mobileinfo.clear();
    AppList::MobileInfo.clear();
    moblestate->setText(QStringLiteral("正在检测中，请稍后..."));


    QString Deviceout =  m_adb->checkDevice();
    QString Device = Deviceout.mid(16);
    qDebug()<<Deviceout<<Device<<"hhhh";

    if(Device.contains("device"))
    {
        safecheckbutton->setEnabled(true);
        ContactCheck->setEnabled(true);
        CallhistoryCheck->setEnabled(true);
        MessagesCheck->setEnabled(true);
        FileCheck->setEnabled(true);

        moblestate->setText(QStringLiteral("已检测到设备，正在检测中..."));
        labelprogress->setText(QStringLiteral("已发现设备插入，请开始检测！"));
        labelPrompt->setText(QStringLiteral("已检测到设备插入!"));

        bool checkApk =  m_adb->checkPackagExist();
        if(false == checkApk)
        {
            bool ok = m_adb->CheckAndroidUsbByAdb();
            if(true == ok)
            {
                 qDebug()<<QStringLiteral("app已经打开！！！");

            }else
            {
                moblestate->setText(QStringLiteral("检测异常，请重新插拔设备！"));
                checkbutton->setEnabled(true);
                return;
            }
        }


        m_adb->ApplyServ();
        AppList::number = 0;

        if(m_socket->linkServer())
        {
            //moblestate->setText(QStringLiteral("设备已连接!"));
            ScreenShotShow();
            qDebug()<<"Link Server";
            QString msg;
            msg.append(MSG_USER_OPERATE_Detail).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL);
            qDebug()<<msg<<"++++===";
            m_socket->sendMsg(MSG_USER_OPERATE_Detail,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);

        }else
        {
            moblestate->setText(QStringLiteral("服务器连接异常，请重新检测！"));
            qDebug()<<"Server Conn Filed";
            checkbutton->setEnabled(true);
            return;
        }


    }else
    {
        moblestate->setText(QStringLiteral("未能识别该设备，请插入安卓设备或打开USB调试模式!"));
        checkbutton->setEnabled(true);
        return;
    }

}

void downwidget::slotHomePage()
{

    AppList::mobileinfo.clear();
    AppList::MobileInfo.clear();
    label11->setText("");
    label21->setText("");
    label31->setText("");
    label41->setText("");
    label51->setText("");
    label61->setText("");
    label71->setText("");
    label81->setText("");
    label91->setText("");

    moblestate->setText(QStringLiteral("正在检测中，请稍后..."));

    bool checkApk =  m_adb->checkPackagExist();

    if(true == checkApk)
    {
       QString str1 =  m_adb->checkDevice();
       QString str2 = "List of devices attached \r\n\r\n";
       qDebug()<<str1;
       if(str1 ==str2 )
       {
           moblestate->setText(QStringLiteral("未能识别该设备，请插入安卓设备或打开USB调试模式!"));
           return;
       }
    }else
    {
        bool ok = m_adb->CheckAndroidUsbByAdb();
        if(true == ok)
        {
             //m_mainwidget->m_maskmainwidget->m_downwidget->
             //moblestate->setText(QStringLiteral("已检测到设备，请开始检测！"));
             //m_mainwidget->m_maskmainwidget->m_downwidget->
             //labelprogress->setText(QStringLiteral("已发现设备插入，请开始检测！"));
             qDebug()<<QStringLiteral("确认安卓设备插入");
             //return true;

        }else
        {
            return;

        }
    }
    m_adb->ApplyServ();
    AppList::number = 0;
    if(m_socket->linkServer())
    {

        //moblestate->setText(QStringLiteral("设备已连接!"));
        ScreenShotShow();
        qDebug()<<"Link Server";
        QString msg;
        msg.append(MSG_USER_OPERATE_Detail).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL);
        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_Detail,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";

        //m_socket->CheckIfConnection();

    }else
    {
        qDebug()<<"Server Conn Filed";
    }

}

void downwidget::addSaveQcrode()
{

    saveqrcode = new QPushButton(this->widget1);
    saveqrcode->setFixedSize(125,45);

    saveqrcode->setGeometry((this->width()-200),485,135,50);
    saveqrcode->setStyleSheet("background-image:url(:/skin/source/icon1/save.png);background-color:transparent;");

}
void downwidget::slotmobileinfo(QString info)
{

     bool OK =  safecheckSignal(info);

     if(OK == TRUE)
     {

         QMutex mutex;
         QWaitCondition sleep;
         mutex.lock();
         sleep.wait(&mutex, 1000);
         mutex.unlock();

         for(int i = 0 ;i < 100000000; i++)
         {

         }

         m_stackwidget->setCurrentIndex(1);

         safecheckbutton->setEnabled(false);

         SafeCheckInfo();

     }
}

bool downwidget::safecheckSignal(QString info)
{

    qDebug()<<info<<"999999";

    //addSaveQcrode();

    AppList::MobileInfo = info.split(MSG_DATA_ITEMS_SEPARATOR);

    moblestate->setText(AppList::MobileInfo.at(0));

    QString  mobielMac = AppList::MobileInfo.at(6);
    if(mobielMac == "null")
    {
        mobielMac = QStringLiteral("无MAC地址");
    }

    label11->setText(AppList::MobileInfo.at(0));
    label21->setText(AppList::MobileInfo.at(1));
    label31->setText(AppList::MobileInfo.at(2));
    label41->setText(AppList::MobileInfo.at(3));
    label51->setText(AppList::MobileInfo.at(4));
    label61->setText(AppList::MobileInfo.at(5));
    label71->setText(mobielMac);
    label81->setText(AppList::MobileInfo.at(7));
    label91->setText(AppList::MobileInfo.at(8));

    labelPrompt->setText(QStringLiteral("已检测到设备插入"));

    //QString mobileImei = m_socket->m_parsejson->RightInfoTransCode(AppList::MobileImei);
    m_qrcode->generateString(AppList::MobileImei);

    QString saveFileName= QDir::currentPath();

    //AppList::IconSrcdate = saveFileName.append("/appIcon/").append(AppList::AppNameList.at(pngi)).append(".png");
    QString pathname = saveFileName.append("/QrcodeImage/").append("qrcode").append(".png");

    m_qrcode->saveImage(pathname);

    //saveqrcode->setStyleSheet("background-image:url(:/skin/source/icon1/save.png);background-color:transparent;");

    saveqrcode->setStyleSheet("QPushButton{border-image: url(:/sourceskin/saveqrinit.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/saveqrhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/saveqrpress.png);}");

    emit runsafecheckSignal();

    return true;
}

void downwidget::slotsafecheckSignal()
{
      m_stackwidget->setCurrentIndex(1);
}

void downwidget::UsbRemove()
{
    label11->setText("");
    label21->setText("");
    label31->setText("");
    label41->setText("");
    label51->setText("");
    label61->setText("");
    label71->setText("");
    label81->setText("");
    label91->setText("");

    //checkbutton->setEnabled(false);
    safecheckbutton->setEnabled(false);
    ContactCheck->setEnabled(false);;
    CallhistoryCheck->setEnabled(false);
    MessagesCheck->setEnabled(false);
    FileCheck->setEnabled(false);

//    bool ok = this->m_socket->disconnect();

//    ok = true;

    QPixmap pixmap;
    pixmap.load("screen/black.png");
    QPixmap fitpixmap=pixmap.scaled(240,428,Qt::KeepAspectRatio);
    labelscreen->setPixmap(fitpixmap);

    //labelscreen->setStyleSheet("background-image:url(:/source/Image/black.png)");
    //screenwidget->setStyleSheet("background-image:url(:/source/Image/androidint.png)");
    labelPrompt->setText(QStringLiteral("设备未连接，请插入设备"));
    moblestate->setText(QStringLiteral("设备未连接，请插入设备"));
    appcountlabel->setText(QStringLiteral("未发现设备，请插入设备进行检测。"));
    labelPrompt->setText(QStringLiteral(" 未发现设备，请插入设备!"));
    labelprogress->setText(QStringLiteral("未发现设备，请插入设备进行检测。"));
    CheckScoreLabel->setText(QStringLiteral(""));

    saveqrcode->setStyleSheet("background-color:transparent;");

    m_qrcode->generateString("");

    QString saveFileName= QDir::currentPath();
    QString pathname = saveFileName.append("/QrcodeImage/").append("qrcode").append(".png");

    m_qrcode->saveImage(pathname);

    QPixmap pixmap1;
    pixmap1.load("screen/IconNo.png");
    QPixmap fitpixmap1=pixmap1.scaled(80,75,Qt::KeepAspectRatio);

    safeprogressBar->setValue(0); //设置当前值
    safeprogressBar->setMinimum(0); //设置当前值
    safeprogressBar->setMaximum(0); //设置当前值

    for(int i = 0; i < AppList::Iconi; i++)
    {

       Iconlabel[i]->setPixmap(fitpixmap1);

    }

    for(int j = 0; j <AppList::AppNanmei;j++)
    {
       AppNamelabel[j]->setText("");
    }

    int row = safeResultTable->rowCount();
    for(int i= 0; i <row; i++)
    {
        safeResultTable->removeRow(i);
    }

    int  contanctRow =  ContactTable->rowCount();
    for(int i= 0; i <contanctRow ; i++)
    {
        ContactTable->removeRow(0);
    }

    int  callRow =  CallhistoryTable->rowCount();
    for(int i= 0; i <callRow; i++)
    {
        CallhistoryTable->removeRow(0);
    }

    int  messsRow =  MessagesTable->rowCount();
    for(int i= 0; i <messsRow; i++)
    {
       MessagesTable->removeRow(0);
    }

    int  fileRow =  FileTable->rowCount();
    for(int i= 0; i < fileRow; i++)
    {
        FileTable->removeRow(0);
    }

}

void downwidget::slotQrcodeSave()
{

    m_printQrcode1 = new QPrintQcrode(this);

    creatQrcodeImageForder();

    //m_printQrcode->setFixedSize(40,40);
    //m_printQrcode1->show();
    m_printQrcode1->generateString(AppList::MobileImei);
    //m_printQrcode1->show();

    QString saveFileName= QDir::currentPath();

    QString pathname = saveFileName.append("/QrcodeImage/").append("printqrcode").append(".png");

    int size = 40;

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    m_printQrcode1->saveImage(pathname,size,downwidget::name,AppList::UserInfolist.at(0),time);


    Qcrodeimg.load("QrcodeImage/printqrcode.png");

    QcrodePrintPic();


//    QString fileName = QFileDialog::getSaveFileName(this,
//     (QStringLiteral("保存二维码")), "/home/mobileqrcode",tr("Image Files (*.png *.jpg *.bmp)"));
//    if(!fileName.isEmpty() )
//    {
//       m_qrcode->saveImage(fileName);
//    }

    return;

//    bool insertOK = cmdData::addCheckInfo("grg","grg","tht","tht","tht","tht",
//                                          "tht","tht","tht",21,22,2,
//                                          34,35,36,37);

//    if(insertOK == true)
//    {
//        qDebug()<<"insert scuessfull";
//    }else
//    {
//        qDebug()<<"export fulase";
//    }

}
