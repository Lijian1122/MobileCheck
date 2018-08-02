#include "downwidget.h"
#include <QPalette>
#include <QSpacerItem>
#include <Common/applist.h>
#include <QPixmap>
#include <QList>
#include <QThread>


//int downwidget::Iconi = 0;
int downwidget::Iconiw = 0;
int downwidget::appRequesti = 1;
int downwidget::range = 0;

void downwidget::SafeCheck()
{  

    IconInfoshow();
    AppNameshow();

    //安全监测
    safecheckbutton = new QPushButton(this->SafeCheckwidget);
    safecheckbutton->setFixedSize(130,55);
    //safecheckbutton->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    safecheckbutton->setGeometry(QRect(this->width()- 320,27,150,55));
    //safecheckbutton->setStyleSheet("background-image:url(:/skin/source/icon1/safeCheck.png);background-color:transparent;");
    safecheckbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/safecheck.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/safecheckhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/safecheckpress.png);}");
    //监测结果
    safeResultbutton = new QPushButton(this->SafeCheckwidget);
    safeResultbutton->setFixedSize(130,55);
    //safeResultbutton->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    safeResultbutton->setGeometry(QRect(this->width()-160,27,150,55));
    //safeResultbutton->setStyleSheet("background-image:url(:/skin/source/icon1/SafeResut.png);background-color:transparent;");
    safeResultbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/safeReInit.png);}"
                                    "QPushButton:hover{border-image: url(:/sourceskin/safeRehover.png);}"
                                    "QPushButton:pressed{border-image: url(:/sourceskin/safeRepress.png);}");

    //进度条
    safeprogressBar = new QProgressBar(this->SafeCheckwidget);
    safeprogressBar->setFixedSize(this->maximumWidth(),10);
    safeprogressBar->setAlignment(Qt::AlignRight|Qt::AlignVCenter);  // 对齐方式
    safeprogressBar->setFormat("");
    //safeprogressBar->setAutoFillBackground(true);

    //safeprogressBar->setMaximum(0);
    //safeprogressBar->setValue(100);

//    safeprogressBar->setStyleSheet("background-color:rgb(0,85,0)");
//    safeprogressBar->setStyleSheet("border: 2px solid grey;border-radius:5px;background-color:grey;");
//   safeprogressBar->setStyleSheet("\
            QProgressBar::chunk {\
                background-color:rgb(0,85,0);\
                width: 5px;}");

    //safeprogressBar->setAlignment(Qt::AlignCenter);
    safeprogressBar->setGeometry(0,90,1364,30);

    labelprogress = new QLabel(this->SafeCheckwidget);
    labelprogress->setFixedSize(500,40);
    labelprogress->setStyleSheet("font: 16pt,Microsoft YaHei;");
    labelprogress->setGeometry(350,30,400,40);

    CheckScoreLabel = new QLabel(this->SafeCheckwidget);
    CheckScoreLabel->setFixedSize(200,40);
    CheckScoreLabel->setStyleSheet("font: 16pt,Microsoft YaHei;");
    CheckScoreLabel->setGeometry(20,30,200,40);
    //CheckScoreLabel->setText(QStringLiteral("检测 100分"));

}

void downwidget::SafeCheckInfo()
{

    safecheckbutton->setEnabled(false);
    QPixmap pixmap1;
    pixmap1.load("screen/IconNo.png");
    QPixmap fitpixmap1=pixmap1.scaled(80,75,Qt::KeepAspectRatio);

    CheckScoreLabel->setText(QStringLiteral("检测得分：100分"));

    appcountlabel->setText(QStringLiteral("正在检测中，请稍后....."));

    labelprogress->setText(QStringLiteral("正在统计应用总数中,请稍后....."));

    downwidget::appRequesti = 0;
    safeprogressBar->setValue(downwidget::appRequesti); //设置当前值

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
        safeResultTable->removeRow(0);
    }

    for(int i = 0; i < downwidget::row; i++)
    {
       AppList::ApkPermission[i].clear();
       AppList::permisson[i].clear();
    }

    AppList::number = 0;
    AppList::AppPackageList.clear();
    AppList::AppNameList.clear();
    ParseJson::pngi = 0;
    AppList::Iconi = 0;
    AppList::AppNanmei = 0;

    downwidget::range = 0;
    downwidget::riskAppCount =0;
    downwidget::row = 0;
    downwidget::lowriski = 0;
    downwidget::highriski = 0;

    downwidget::countLowRisk = 0;
    downwidget::countHighRisk = 0;
    AppList::riskcount= 0;
    AppList::CheckAllApk = 0;
    downwidget::vTypecount= 0;
    AppList::Viruscount = 0;
    AppList::AppPackageDanger.clear();
    AppList::AppNameListDanger.clear();

    m_adb->ApplyServ();
    if(m_socket->linkServer())
    {
        safecheckbutton->setEnabled(false);
        qDebug()<<"Link Server";
        QString msg;
        msg.append(MSG_USER_OPERATE_APPList).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL);
        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_APPList,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";
    }else
    {
        qDebug()<<"Server Conn Filed";
    }

}

void downwidget::SafeCountCheckAPP()
{

}

void downwidget::IfCheckPackage(QString str)
{


}

void downwidget::slotRequestCheckInfo(QStringList packagelist)
{
    //QString str = QStringLiteral("正在检测") ;
    //labelprogress->setText(str.append(AppList::AppNameList.at(0)));

    downwidget::range= AppList::AppPackageList.count();

    qDebug()<<downwidget::range<<"tyttytyt";

    safeprogressBar->setMinimum(0);  // 最小值
    safeprogressBar->setMaximum(downwidget::range);  // 最大值

    //safeprogressBar->setRange(0,downwidget::range-1);

    safeprogressBar->setOrientation(Qt::Horizontal);  // 水平方向
    //safeprogressBar->setRange(0,downwidget::range);

    CheckScoreLabel->setText(QStringLiteral("检测得分: "));

    m_adb->ApplyServ();
    if(m_socket->linkServer())
    {
        QString checkMsg;
        int count = AppList::AppPackageList.count();
        qDebug()<<count;

        //AppList::AppNameList.clear();
        for(int i = 0; i<AppList::AppPackageList.count();i++)
        {
              AppList::number = 0;

              checkMsg.append(MSG_USER_OPERATE_Right).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL).
                       append(MSG_DATA_ITEMS_SEPARATOR).append(AppList::AppPackageList.at(i));
              qDebug()<<checkMsg<<"APP包名";
              m_socket->sendMsg(MSG_USER_OPERATE_Right,MSG_OPERATE_CMD_SELECT_ALL,checkMsg.size(),checkMsg);
              AppList::number = 0;
              checkMsg = "";

       }

    }else
    {
            qDebug()<<"Server Conn Filed";
    }

}

void downwidget::slotProgressUpdate(QString appname)
{

    if(appname == NULL)
    {
        return;
    }

    if(appname == "LastOne")
    {

        QString str = QStringLiteral("检测已完成，请查看检测结果!");
        int count = AppList::AppPackageList.count();
        //QString str1 = AppList::AppPackageList.count(count-1);
        safeprogressBar->setValue(count); //设置当前值

        labelprogress->setText(str);

        QString str1 = QStringLiteral("共检测应用");
        QString str2 = QStringLiteral("发现风险应用");
        QString str3 = QStringLiteral("个，");
        QString str4 = QStringLiteral("个，");
        QString str5 = QStringLiteral("个，");
        QString str6 = QStringLiteral("风险应用如下表所示。");
//        QString strstr1 = str1.append(QString::number(AppList::CheckAllApk)).append(str3).append(str2).
//                       append(QString::number(downwidget::riskAppCount).append(str4));

        QString strstr1;
        if(vTypecount != 0)
        {
            strstr1 = str1.append(QString::number(AppList::CheckAllApk)).append(str3).append(str2).
                        append(QString::number(downwidget::riskAppCount - downwidget::vTypecount).append(str4).append(str6));

            QString virtrustr = QStringLiteral("发现病毒%1个。").arg(QString::number(downwidget::vTypecount));
            strstr1 = strstr1.append(virtrustr);
        }else
        {
            strstr1 = strstr1.append(QString::number(AppList::CheckAllApk)).append(str3).append(str2).
                          append(QString::number(downwidget::riskAppCount).append(str5).append(str6));

        }

        appcountlabel->setText(strstr1);

        int score = getScore(countLowRisk+countHighRisk);
        QString scorestr = QStringLiteral("检测得分：%1分").arg(QString::number(score));
        CheckScoreLabel->setText(scorestr);

        safecheckbutton->setEnabled(true);

        m_stackwidget->setCurrentWidget(CheckResultwidget);

        checkbutton->setEnabled(true);

        return;
    }

    qDebug()<<appname<<"jindutiao==";

    qDebug()<<appRequesti<<"fffefeff";

    QString str = QStringLiteral("正在扫描：") ;
    labelprogress->setText(str.append(appname));

    if(appRequesti+1 == AppList::AppNameList.count())
    {

       //进度条检测结果
       //labelprogress->setText(str.append(appname));

       safeprogressBar->setValue(appRequesti); //设置当前值
       QThread::sleep(2);
       safeprogressBar->setValue(AppList::AppNameList.count()); //设置当前值

       QString str = QStringLiteral("检测已完成,请查看检测结果!");
       labelprogress->setText(str);

       //检测结果统计
       QString str1 = QStringLiteral("共检测应用");
       QString str2 = QStringLiteral("发现风险应用");
       QString str3 = QStringLiteral("个，");
       QString str4 = QStringLiteral("个，");
       QString str5 = QStringLiteral("个，");
       QString str6 = QStringLiteral("风险应用如下表所示。");

       QString strstr;
       if(vTypecount != 0)
       {
           strstr = str1.append(QString::number(AppList::CheckAllApk)).append(str3).append(str2).
                       append(QString::number(downwidget::riskAppCount - downwidget::vTypecount).append(str4).append(str6));

           QString virtrustr = QStringLiteral("发现病毒%1个。").arg(QString::number(downwidget::vTypecount));
           strstr = strstr.append(virtrustr);
       }else
       {
           strstr = str1.append(QString::number(AppList::CheckAllApk)).append(str3).append(str2).
                         append(QString::number(downwidget::riskAppCount).append(str5).append(str6));

       }

       appcountlabel->setText(strstr);

       safeprogressBar->setValue(downwidget::range); //设置当前值

       int score = getScore(countLowRisk+countHighRisk);



       QString scorestr = QStringLiteral("检测得分：%1分").arg(QString::number(score));
       CheckScoreLabel->setText(scorestr);

       safecheckbutton->setEnabled(true);

       m_stackwidget->setCurrentWidget(CheckResultwidget);

       checkbutton->setEnabled(true);

       return;

    }else
    {
          safeprogressBar->setValue(appRequesti); //设置当前值
    }

    downwidget::appRequesti++;

}

int downwidget::getScore(int number)
{
    int score= 0;

    if(vTypecount != 0)
    {
        score = 100 -41;
    }else {
        score = 100;
    }

    if(number >= 0 && number <= 5)
    {
        score = score- (number*2);
        return score;

    }else if(number > 5 && number <= 15)
    {
         score = score- (number*1);
         return score;

    }else if(number > 15 && number <= 36)
    {
        score = score- 0.5*(number);
        return score;

    }else if(number > 36)
    {
        number = 36;
        score = score - 0.5*(number);
        return score;
    }

}

void downwidget::IconInfoshow()
{
    int coowid;
    int coohieght;
    int time = 0;
    int time1 = 0;
    AppList::Iconi = 0;
    for(Iconiw = 0;Iconiw < 1000;Iconiw++)
    {
        coowid = 10;
        time1 = 0;
        coohieght = 120+(48*Iconiw);
        //coohieght = 120+(48*Iconiw);
        //coohieght = 120+(76*Iconiw);
        //coohieght = 120+(100*Iconiw);
        //Iconi = (time*2)+Iconi;
        if(coohieght > 550)
        //if(coohieght > 600)
        {
          return;
        }
        while(AppList::Iconi<1000)
        //for(AppList::Iconi = 0;AppList::Iconi<1000;AppList::Iconi++)
        {

          Iconlabel[AppList::Iconi] = new QLabel(this->SafeCheckwidget);

          Iconlabel[AppList::Iconi]->setFixedSize(80,75);

          coowid = 10+(97*time1);
          //Iconlabel[Iconi]->setGeometry(coowid,120,80,80);
          Iconlabel[AppList::Iconi]->setGeometry(coowid,coohieght,80,75);

          if((coowid) == 1271)
          //if((coowid) == 1368)
          {
            //time++;
            Iconiw++;
            AppList::Iconi++;
            break;
          }
          time1++;
          AppList::Iconi++;
        }

    }
}
void downwidget::AppNameshow()
{
    int Appcoowid;
    int Appcoohieght;
    int Apptime = 0;
    int Apptime1 = 0;
    AppList::AppNanmei = 0;
    for(int Iconiw = 0;Iconiw < 1000;Iconiw++)
    {
        Appcoowid = 10;
        Apptime1 = 0;
        Appcoohieght = 196+(48*Iconiw);
        //coohieght = 120+(48*Iconiw);
        //coohieght = 120+(76*Iconiw);
        //coohieght = 120+(100*Iconiw);
        if(Appcoohieght > 600)
        //if(coohieght > 600)
        {
          return;
        }
        while(AppList::AppNanmei<1000)
        //for(AppList::Iconi = 0;AppList::Iconi<1000;AppList::Iconi++)
        {

          AppNamelabel[AppList::AppNanmei] = new QLabel(this->SafeCheckwidget);

          AppNamelabel[AppList::AppNanmei]->setFixedSize(85,20);
          //AppNamelabel[AppList::AppNanmei]->setStyleSheet("background-color:black");
          AppNamelabel[AppList::AppNanmei]->setStyleSheet("color:rgb(68,68,68);font: 9pt;");
          AppNamelabel[AppList::AppNanmei]->setAlignment(Qt::AlignCenter);

          Appcoowid = 10+(97*Apptime1);
          //Iconlabel[Iconi]->setGeometry(coowid,120,80,80);
          AppNamelabel[AppList::AppNanmei]->setGeometry(Appcoowid,Appcoohieght,80,20);

          if((Appcoowid) == 1271)
          //if((Appcoowid) == 1368)
          {
            //time++;
            Iconiw++;
            AppList::AppNanmei++;
            break;
          }
          Apptime1++;
          AppList::AppNanmei++;
        }
    }
    qDebug()<<AppList::AppNanmei<<"5798765";

}

void downwidget::slotAppIcon(QString icondata)
{
    qDebug()<<icondata<<"ICON=====";
    qDebug()<<AppList::Iconi<<22222;
    qDebug()<<AppList::AppNanmei<<3333;

    //加载图标信息
    QPixmap pixmap;
    pixmap.load(icondata);
    QPixmap fitpixmap=pixmap.scaled(80,76,Qt::KeepAspectRatio);
    Iconlabel[AppList::Iconi]->setPixmap(fitpixmap);
    AppList::Iconi++;

    //加载APP名字
    QStringList testlist = icondata.split("/");
    int count = testlist.count();
    QString icondir = testlist.at(count-1);
    QString iconname = icondir.left(icondir.length()-4);
    qDebug()<<iconname<<"999999";
    AppNamelabel[AppList::AppNanmei]->setText(iconname);

    AppList::AppNanmei++;
}

void downwidget::slotSafeResult()
{
    m_stackwidget->setCurrentWidget(CheckResultwidget);

}

void downwidget::slotSafecheck()
{
   SafeCheckInfo();

}

