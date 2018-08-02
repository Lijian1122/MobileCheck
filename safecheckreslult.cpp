#include <downwidget.h>
#include <QScrollBar>
#include <QStringList>
#include <QHeaderView>
#include <QScrollArea>
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QByteArray>
#include <QJsonValue>
#include <Common/applist.h>
#include <Database/cmddata.h>
#include <QMessageBox>
#include <applist.h>
//#include <QWord/qword.h>
#include <QComboBox>
#include <QDesktopServices>
#include <MyMessageBox/mymessagebox.h>
#include <LoginWidget/loginwidget.h>
#include <QStringList>

int downwidget::row = 0;
int downwidget::permissi = 1;
int downwidget::lowriski = 0;
int downwidget::highriski = 0;
int downwidget::currentrow = 0;
int downwidget::countLowRisk = 0;
int downwidget::countHighRisk = 0;

QString downwidget::Appname = "";
int downwidget::riskAppCount = 0;
QString downwidget::unit ;
QString downwidget::name ;
QString downwidget::phone ;
QString downwidget::vType = "";
QString downwidget::detail ;
int downwidget::vTypecount = 0;

void downwidget::safeResultshow()
{

   appcountlabel = new QLabel(this->CheckResultwidget);
   appcountlabel->setText(QStringLiteral("未发现设备，请插入设备进行检测。"));
   appcountlabel->setFixedSize(550,60);
   appcountlabel->setStyleSheet("color:rgb(68,68,68);font:14pt,Microsoft YaHei;");
   appcountlabel->setGeometry(10,10,550,60);

   GetReportbutton = new QPushButton(this->CheckResultwidget);
   GetReportbutton->setFixedSize(130,50);
   GetReportbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/safePoinit.png);}"
                                  "QPushButton:hover{border-image: url(:/sourceskin/safePohover.png);}"
                                  "QPushButton:pressed{border-image: url(:/sourceskin/safePohover.png);}");

           //setStyleSheet("background-image:url(:/skin/source/icon1/SafeRepro.png);background-color:transparent;");
   GetReportbutton->setGeometry(QRect(this->width()-160,20,130,50));

   safeResultTable  = new QTableWidget(this->CheckResultwidget);
   //safeResultTable->setFixedSize(1260,516);
   //safeResultTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy);
   //safeResultTable->setStyleSheet("color:rgb(68,68,68);font:12pt,黑体;");
   safeResultTable->setGeometry(10,80,1350,520);
   safeResultTable->setAlternatingRowColors(true);
   safeResultTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
   //safeResultTable->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
   //"QTableView{background-color: rgb(250, 250, 115);"
   //170, 255, 255.rgb(233, 245, 252)
   //safeResultTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
   safeResultTable->setStyleSheet("font:12pt,黑体;");

   //获取滑动条
   Resulbar = safeResultTable->verticalScrollBar();
   Resulbar->setStyleSheet("QScrollBar{background:lightgray;}");
   //Resulbar->setFixedSize(20,50);
   //Resulbar->setGeometry(1240,0,20,27);
   //Resulbar->setMinimum(18);

   //safeResultTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   safeResultTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

   int i = 0;
   QStringList header;
   header<<QStringLiteral("应用名称")<<QStringLiteral("检测权限情况")<<QStringLiteral("检测详情")<<QStringLiteral("白名单")<<
           QStringLiteral("卸载");

   safeResultTable->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

   QFont font = safeResultTable->horizontalHeader()->font();
   font.setBold(true);
   safeResultTable->horizontalHeader()->setFixedHeight(50);

   safeResultTable->setColumnCount(5);
   safeResultTable->setHorizontalHeaderLabels(header);

   safeResultTable->setRowHeight(i,300);
   safeResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
   safeResultTable->setColumnWidth(0,525);
   safeResultTable->setColumnWidth(1,525);
   safeResultTable->setColumnWidth(2,100);
   safeResultTable->setColumnWidth(3,100);
   safeResultTable->setColumnWidth(4,100);
   //safeResultTable->setColumnWidth(5,100);

   //safeResultTable->setShowGrid(false); //设置不显示格子线

   QHeaderView *columnhead = safeResultTable->verticalHeader();
   columnhead->setVisible(false);

   //safeResultTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行


   //表头样式表
   safeResultTable->horizontalHeader()->setEnabled(false);

   QFont font3 =safeResultTable->horizontalHeader()->font();    //设置表头字体加粗
   font3.setBold(true);

   safeResultTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

   //表头居左
   //safeResultTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);

   int nRow = safeResultTable->rowCount();
   //safeResultTable->setFixedSize(1260,50+40*nRow);

   qDebug()<<nRow<<"All Count";
   for(i = 0 ; i < nRow; i++)
   {
      for(int j=0;j<5;j++)
      {

         safeResultTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

      }
   }

  connect(GetReportbutton,SIGNAL(clicked()),this,SLOT(slotExportReport()));



}
void downwidget::slotslidevalue()
{

}

//表中添加检测结果
void downwidget::safeResultJson(QJsonObject object)
{
    downwidget::lowriski = 0;
    downwidget::highriski = 0;
    parseSafeResult(object);

    qDebug()<<"row:"<<row<<"oooooo888666";


    if(downwidget::Appname == NULL)
    {
        return;
    }

    if((downwidget::lowriski + downwidget::highriski == 0) || (downwidget::vType.isEmpty()))
    {

        return;
    }

    safeResultTable->insertRow(row);

    CheckDetailbutton[row] = new QPushButton();
//    CheckDetailbutton[row]->setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127);}"
//                                  "QPushButton:pressed{background-color: rgb(255, 0, 0);}");
    CheckDetailbutton[row]->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/safeinfoInit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/safeinfohover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/safeInfopress.png);}");

    CheckDetailbutton[row]->setFixedSize(98,36);


    whitelistbutton[row] = new QPushButton();
    whitelistbutton[row]->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/setwhiteinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/setwhitehover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/setwhitepress.png);}");

    //whitelistbutton[row]->setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127);}"
    //                                  "QPushButton:pressed{background-color: rgb(255, 0, 0);}");
    whitelistbutton[row]->setFixedSize(98,36);


    Uninstallbutton[row] = new QPushButton();
    Uninstallbutton[row]->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/uninit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/unhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/unpress.png);}");

    //Uninstallbutton[row]->setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127);}"
                                      //"QPushButton:pressed{background-color: rgb(255, 0, 0);}");
    Uninstallbutton[row]->setFixedSize(98,36);


//    ExportAppbutton[row] = new QPushButton(QStringLiteral("导出"));
//    ExportAppbutton[row]->setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127);}"
//                                      "QPushButton:pressed{background-color: rgb(255, 0, 0);}");
//    ExportAppbutton[row]->setFixedSize(100,38);
   safeResultTable->setItem(row, 0, new QTableWidgetItem(downwidget::Appname));


    QString lowrisk1 = QStringLiteral("危险:");
    QString highrisk1 = QStringLiteral(" 高危:");
    QString riskcount = lowrisk1.append(QString::number(downwidget::lowriski))
                         .append(highrisk1).append(QString::number(downwidget::highriski));
    safeResultTable->setItem(row, 1, new QTableWidgetItem(riskcount));

    QTableWidgetItem *item = safeResultTable->item(row,0);
    QTableWidgetItem *item1 = safeResultTable->item(row,1);

    if(downwidget::vType != "-1")
    {
         item->setBackgroundColor(QColor(255,67,67));
         item1->setBackgroundColor(QColor(255,67,67));
         vTypecount++;
         AppList::Viruscount++;
    }


    QComboBox *ComboBoxWork1 = new QComboBox();
    ComboBoxWork1->addItem(tr("Worker"));
    ComboBoxWork1->addItem(tr("Farmer"));
    ComboBoxWork1->addItem(tr("Doctor"));
    ComboBoxWork1->addItem(tr("Lawyer"));
    ComboBoxWork1->addItem(tr("Soldier"));
    //safeResultTable->setCellWidget(row,2,ComboBoxWork1);
    safeResultTable->setCellWidget(row,2,CheckDetailbutton[row]);
    safeResultTable->setItem(row, 2, new QTableWidgetItem(""));
    connect(CheckDetailbutton[row],SIGNAL(clicked()),this,SLOT(slotCheckDetail()));
    //CheckDetailbutton[row]->setText("ffffff");

    safeResultTable->setCellWidget(row,3,whitelistbutton[row]);
    safeResultTable->setItem(row, 3, new QTableWidgetItem(QStringLiteral("")));
    connect(whitelistbutton[row],SIGNAL(clicked()),this,SLOT(slotSetWhiteList()));

    safeResultTable->setCellWidget(row,4,Uninstallbutton[row]);
    safeResultTable->setItem(row, 4, new QTableWidgetItem(QStringLiteral("")));
    connect(Uninstallbutton[row],SIGNAL(clicked()),this,SLOT(slotUninstall()));

//    safeResultTable->setCellWidget(row,5,ExportAppbutton[row]);
//    safeResultTable->setItem(row, 5, new QTableWidgetItem(QStringLiteral("")));
//    connect(ExportAppbutton[row],SIGNAL(clicked()),this,SLOT(slotExportApp()));

    int nRow = safeResultTable->rowCount();
    //safeResultTable->setFixedSize(1260,50+40*nRow);

    //safeResultTable->scrollToBottom();
    qDebug()<<nRow<<row<<"All Count";
    for(int i = 0 ; i < nRow; i++)
    {
       for(int j=0;j<5;j++)
       {
          safeResultTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       }
    }
    for(int i =0; i<nRow; i++)
    {
        safeResultTable->setRowHeight(i,40);
    }
    if(nRow>0)
    {
       safeResultTable->scrollToItem(safeResultTable->item(nRow,0)
                                     ,QAbstractItemView::PositionAtBottom);
    }

    row++;
}

//保存权限和病毒信息
void downwidget::parseSafeResult(QJsonObject object)
{
    qDebug()<<"start safeResultJson"<<"123";

    QString apkPermission;
    QString packageName;
    QString packageNameInfo;
    QString vNanme;
    //QString vType;
    QString vDetail;
    QString vRemark;
    QString checkinfo;
    QJsonObject json;
    QStringList perlist;
    QStringList permissionlist;
    QString level;
    QString permisson = QStringLiteral("一、应用拥有的敏感权限如下:");
    QString antivirus = QStringLiteral("二、病毒检测风险:");
    QString name = QStringLiteral("病毒名称:");
    QString type = QStringLiteral("病毒类型:");
    QString detail= QStringLiteral("病毒详细:");
    QString remark = QStringLiteral("标记:");
    QJsonValue ret_vaue = object.take("ret");
    QString ret = ret_vaue.toString();
    QString usepermisson;

    downwidget::permissi = 1;
    //downwidget::lowriski = 0;
    //downwidget::highriski = 0;
    downwidget::vType = "";

    json= object.take("appInfo").toObject();
    QString apaname = json.value("appName").toString();

    qDebug()<<ret<<apaname<<"result";

    if(ret == "200")
    {
        qDebug()<<"start parse";

        QString apaname = json.value("appName").toString();
        downwidget::Appname = m_socket->m_parsejson->RightInfoTransCode(apaname);

        QString packnage = json.value("packageName").toString();
        packageName = m_socket->m_parsejson->RightInfoTransCode(packnage);
        packageNameInfo = m_socket->m_parsejson->RightInfoTransCode(packnage);


        QString apkPermission1 = json.value("opPerssion").toString();
        apkPermission = m_socket->m_parsejson->RightInfoTransCode(apkPermission1);

        QJsonObject vInfojson = json.value("vInfo").toObject();
        QString vNanm1 = vInfojson.value("vName").toString();
        vNanme = m_socket->m_parsejson->RightInfoTransCode(vNanm1);

        QString vType1 = vInfojson.value("vType").toString();
        downwidget::vType = m_socket->m_parsejson->RightInfoTransCode(vType1);

        qDebug()<<downwidget::vType<<"virusss";

        QString vDetail1 = vInfojson.value("vDetail").toString();
        vDetail = m_socket->m_parsejson->RightInfoTransCode(vDetail1);

        QString vRemark1 = vInfojson.value("remark").toString();
        vRemark = m_socket->m_parsejson->RightInfoTransCode(vRemark1);
    }else if(ret == "210")
    {
        QString desc = object.value("desc").toString();

        downwidget::Appname = "";
        qDebug()<<desc<<"jjjjjj";

        return;

    }else
    {
         qDebug()<<"parseRightJson Error";
    }

    if(!vNanme.isEmpty())
    {
        QString vname = name.append(vNanme);
        QString vtype = type.append(downwidget::vType);
        QString vdetail = detail.append(vDetail);
        QString vremark = remark.append(vRemark);

        antivirus = antivirus.append(MSG_DATA_ITEMS_SEPARATOR).append(vname).
                        append(MSG_DATA_ITEMS_SEPARATOR).append(vtype).append(MSG_DATA_ITEMS_SEPARATOR).
                        append(vdetail).append(MSG_DATA_ITEMS_SEPARATOR).append(vremark);

        qDebug()<<antivirus;

    }

    qDebug()<<antivirus<<"+++++antivir+++";

    //qDebug()<<apkPermission<<"++++====";
    permissionlist = apkPermission.split(MSG_DATA_ITEMS_SEPARATOR);
    int percount = permissionlist.count();

    qDebug()<<percount<<"count";
    for(int i = 0; i < percount -1; i++)
    {

      QString permenber = permissionlist.at(i);
      QString ppart  = cmdData::selectperDetail(permenber);
      if(!ppart.isEmpty())
      {
         perlist = ppart.split(MSG_DATA_ITEMS_SEPARATOR);

         qDebug()<<perlist.at(0);
         qDebug()<<perlist.at(1);
         level = perlist.at(1);
         qDebug()<<ppart<<level;
         if(!level.isEmpty() && (level != QStringLiteral("普通")))
         {

            if(level == QStringLiteral("危险"))
            {
                downwidget::lowriski++;
                downwidget::countLowRisk++;

                QString perpart = perlist.at(0);

                permisson = permisson.append(MSG_DATA_ITEMS_SEPARATOR).
                           append(QString::number(downwidget::permissi)).
                           append(MSG_DATA_ITEMS_POINT).append(perpart).append(QStringLiteral(" (危险)"));


            }else if(level == QStringLiteral("高危"))
            {
                downwidget::highriski++;
                downwidget::countHighRisk++;

                QString perpart = perlist.at(0);

                permisson = permisson.append(MSG_DATA_ITEMS_SEPARATOR).
                           append(QString::number(downwidget::permissi)).
                           append(MSG_DATA_ITEMS_POINT).append(perpart).append(QStringLiteral(" (高危)"));

            }

           usepermisson = usepermisson.append(permissionlist.at(i)).append(MSG_DATA_ITEMS_SEPARATOR);

           downwidget::permissi++;

         }

      }

    }

    qDebug()<<permisson<<"+++++permisson+++";
    checkinfo = packageName.append(MSG_CHECKOUT).append(antivirus).
                            append(MSG_CHECKOUT).append(permisson);


    qDebug()<<downwidget::lowriski<<"ooooooo";
    qDebug()<<downwidget::highriski<<"uuuuuuu";

    if((downwidget::lowriski + downwidget::highriski == 0) || (downwidget::vType.isEmpty()))
    {
         return;

    }else
    {
        downwidget::riskAppCount++;
        AppList::riskcount++;

        AppList::AppPackageDanger.append(packageNameInfo);
        AppList::AppNameListDanger.append(downwidget::Appname);

        AppList::ApkPermission[row] = checkinfo;
        AppList::permisson[row] = usepermisson;

        int score = getScore(countLowRisk+countHighRisk);

        qDebug()<<score<<"popopo";


        QString scorestr = QStringLiteral("检测得分：%1分").arg(QString::number(score));
        CheckScoreLabel->setText(scorestr);

        return;

    }

}

//检测详情
void downwidget::slotCheckDetail()
{
    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =safeResultTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    AppList::currentrow = index.row();
    qDebug()<<"dangqian row:"<<AppList::currentrow;

    QStringList AllInfo;
    QString Permisson;
    QString Virus;
    QString safeResultInfo;
    QString VirusInfo;
    //QString info;

    QString msg = AppList::ApkPermission[AppList::currentrow];


    AllInfo = msg.split(MSG_CHECKOUT);


    qDebug()<<msg<<AllInfo.count()<<"uuuuu";

    QString perInfo = AllInfo.at(2);
    QString vires = AllInfo.at(1);

    QString apkinfo = perInfo.append(MSG_DATA_ITEMS_SEPARATOR);


    QStringList perInfoList = perInfo.split(MSG_DATA_ITEMS_SEPARATOR);
    int count = perInfoList.count();
    for(int i = 0; i < count - 1; i++)
    {
        Permisson = Permisson.append(perInfoList.at(i)).append("|");
    }

    safeResultInfo = safeResultInfo.append(Permisson);

    Virus = AllInfo.at(1);
    QStringList VirusList = Virus.split(MSG_DATA_ITEMS_SEPARATOR);
    int count1 = VirusList.count();
    qDebug()<<count1<<"9999";
    if(count1 == 1)
    {
        safeResultInfo = safeResultInfo.append(Virus).append("|").append(QStringLiteral("未发现病毒"));
    }else
    {
        for(int i = 0; i < count1 - 1; i++)
        {

            VirusInfo = VirusInfo.append(VirusList.at(i)).append("|");
        }

        safeResultInfo = safeResultInfo.append(VirusInfo);
    }

     msginfobox = new MsgBox;
     msginfobox->setInfo(QStringLiteral("检测详细信息"), safeResultInfo, QStringLiteral("../source/logo.ico"));
     msginfobox->show();


    if(!msg.isEmpty())
    {
        return;
    }

}
//进入白名单
void downwidget::slotSetWhiteList()
{

    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =safeResultTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    AppList::currentrow = index.row();
    qDebug()<<"dangqian row:"<<AppList::currentrow;

    QStringList AllInfo;


    QString msg = AppList::ApkPermission[AppList::currentrow];


    AllInfo = msg.split(MSG_CHECKOUT);

    QString packagename = AllInfo.at(0);


    qDebug()<<msg<<AllInfo.count()<<packagename<<"uuuuu";


    m_setWhiteListInfo = new MsgBox(this);

    m_setWhiteListInfo->setWhiteListIntoSql(packagename);

    m_setWhiteListInfo->show();


    connect(m_setWhiteListInfo->exportbutton,SIGNAL(clicked()),this,SLOT(setWhiteList()));


    return;


}


//设置白名单
void downwidget::setWhiteList()
{
    QString package = m_setWhiteListInfo->anmeEdit->text().trimmed();
    QString remark = m_setWhiteListInfo->unitEdit->text().trimmed();

    if(remark.isEmpty())
    {

        QMessageBox box(QMessageBox::Warning,QStringLiteral("设置提示"),QStringLiteral("应用说明不能为空！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //QMessageBox::Cancel
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        m_setWhiteListInfo->unitEdit->setFocus();

        return;
    }

    bool OK = cmdData::addWhiteListInfo(package,remark);

    if(OK == true)
    {

        m_setWhiteListInfo->close();
        DeleteAwarryString(AppList::currentrow);

        safeResultTable->removeRow(AppList::currentrow);

        //检测结果统计
        downwidget::range--;
        downwidget::riskAppCount--;

        QString str1 = QStringLiteral("共检测应用");
        QString str2 = QStringLiteral("发现风险应用");
        QString str3 = QStringLiteral("个，");
        QString str4 = QStringLiteral("个。");

        QString strstr = str1.append(QString::number(downwidget::range)).append(str3).append(str2).
                       append(QString::number(downwidget::riskAppCount).append(str4));
        appcountlabel->setText(strstr);
        //safeResultTable->removeRow(AppList::currentrow);

        QMessageBox box(QMessageBox::Question,QStringLiteral("设置提示"),QStringLiteral("该应用设置白名单成功！！!"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/info.png"));

        if(box.exec() == QMessageBox::Ok)
        {
            box.close();
            return;
        }else
        {
            box.close();
            return;
        }

    }else if(OK == false)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("设置提示"),QStringLiteral("未能设置成功，请重新设置！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确定"));
        box.setWindowIcon(QIcon("screen/info.png"));
        box.exec();
        return;
    }

}

void downwidget::DeleteAwarryString(int row)
{
    QString Delpermission[10001];

    for(int i = row; i < downwidget::row; i++)
    {
       Delpermission[i] = AppList::ApkPermission[i+1];
       qDebug()<<Delpermission[i]<<"llloooo";

    }

    downwidget::row = downwidget::row - 1;
    for(int i = row; i < downwidget::row - 1; i++)
    {
        AppList::ApkPermission[i] = Delpermission[i];
    }

    return;
}

//卸载APP
void downwidget::slotUninstall()
{

    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
        return;
    }
    QModelIndex index =safeResultTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row=index.row();
    qDebug()<<"row:"<<row;

    QStringList AllInfo;

    QString msg = AppList::ApkPermission[row];

    qDebug()<<msg<<downwidget::row<<"++++";

    AllInfo = msg.split(MSG_CHECKOUT);

    QString packageInfo = AllInfo.at(0);

    bool OK = m_adb->UninstallApp(packageInfo);

    if(OK == true)
    {

        DeleteAwarryString(row);

        safeResultTable->removeRow(row);

        //检测结果统计
        downwidget::range--;
        downwidget::riskAppCount--;
        AppList::CheckAllApk--;

        QString str1 = QStringLiteral("共检测应用");
        QString str2 = QStringLiteral("发现风险应用");
        QString str3 = QStringLiteral("个，");
        QString str4 = QStringLiteral("个。");

        QString strstr = str1.append(QString::number(downwidget::range)).append(str3).append(str2).
                       append(QString::number(downwidget::riskAppCount).append(str4));
        appcountlabel->setText(strstr);

//        MyMessageBox *msgBox = new MyMessageBox();
//        msgBox->showInformationBox(QStringLiteral("提示"), QStringLiteral("卸载完成！！！"),
//                                    QPixmap(":/resources/information.png"), true, QStringLiteral("确定"), QStringLiteral("取消"));
//        msgBox->show();


        QMessageBox box(QMessageBox::Information,QStringLiteral("卸载提示"),QStringLiteral("卸载完成！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/unscuall.ico"));
        box.exec();

        OK = false;

//        for(int i = 0; i < downwidget::row;i++)
//        {
//            Uninstallbutton[i]->setEnabled(true);
//        }

        qDebug()<<"Uninstall scussfull!!!!";

        return;

    }else
    {

//        for(int i = 0; i < downwidget::row;i++)
//        {
//            Uninstallbutton[i]->setEnabled(true);
//        }

        qDebug()<<"Uninstall Failed!!!";

        return;
    }


}

//导出APK;
void downwidget::slotExportApp()
{
//    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
//    if(senderObj == 0)
//    {
//            return;
//    }
//    QModelIndex index =safeResultTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
//    int row=index.row();
//    qDebug()<<"row:"<<row;

//    QStringList AllInfo;

//    QString msg = AppList::ApkPermission[row];

//    AllInfo = msg.split(MSG_CHECKOUT);

    //QString packageInfo = AllInfo.at(0);

}

//导出报表
void downwidget::slotExportReport()
{

    if(AppList::ApkPermission[0].isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("请先安全检测再导出！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //QMessageBox::Cancel
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        return;
    }

    qDebug()<<"rrrr";
    msg_box = new MsgBox;
    msg_box->setExport(QStringLiteral("安全检测报表"));

    msg_box->anmeEdit->setText(downwidget::unit);
    msg_box->unitEdit->setText(downwidget::name);
    msg_box->phoneEdit->setText(downwidget::phone);
    msg_box->remarkEdit->setText(downwidget::detail);

    msg_box->show();

    //QWord::showSafewordinfo("unit","name","phone","detail");

    connect(msg_box->exportbutton,SIGNAL(clicked()),this,SLOT(slotReport()));

}

void downwidget::word123()
{

}

void downwidget::slotReport()
{

    downwidget::unit = msg_box->anmeEdit->text();
    downwidget::name = msg_box->unitEdit->text();
    downwidget::phone = msg_box->phoneEdit->text();
    downwidget::detail = msg_box->remarkEdit->text();

    if(downwidget::unit.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("所属单位不允许为空，请输入！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //QMessageBox::Cancel
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        return;

    }
    if(downwidget::name.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("姓名不允许为空，请输入！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //QMessageBox::Cancel
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        return;

    }

    if(downwidget::phone.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("电话号码不允许为空，请输入！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //QMessageBox::Cancel
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();
        return;
    }


    msg_box->close();

    qDebug()<<name<<unit<<"dfbhtrfghtfrdbhgtfc";

    m_safeResultWord = new QWord;

    int score = getScore(countLowRisk+countHighRisk);


    bool OK =  m_safeResultWord->showSafewordinfo(unit,name,phone,detail,downwidget::row,score);

    if(OK == true)
    {

        qDebug()<<AppList::UserInfolist.count();
        QString userid = AppList::UserInfolist.at(6);
        qDebug()<<userid.toInt()<<"kkkk"<<AppList::UserInfolist.at(0);

        int id = cmdData::userid(AppList::UserInfolist.at(0));

        qDebug()<<"iii"<<id;
        QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");



        bool insertOK = cmdData::addCheckInfo(currenttime,downwidget::name,downwidget::unit,downwidget::phone,AppList::MobileImei,AppList::currentExportDir,
                        downwidget::detail,AppList::UserInfolist.at(0),AppList::UserInfolist.at(3),AppList::CheckAllApk,riskAppCount,countHighRisk,
                        countLowRisk,AppList::CheckAllApk-riskAppCount-vTypecount,vTypecount, score);

        if(insertOK == true)
        {
            qDebug()<<"insert scuessfull";
        }else
        {
            qDebug()<<"export fulase";
        }

        QMessageBox box(QMessageBox::Question,QStringLiteral("导出完成"),QStringLiteral("文件已经导出，是否现在打开？？"));
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/open.ico"));

        if(box.exec() == QMessageBox::Ok)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(AppList::currentExportDir));
            box.close();
            return;
        }else
        {
            box.close();
            return;
        }

//        QString safeResultInfo = QStringLiteral("检测结果已经导出，请查阅！！！");
//        QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                                     safeResultInfo, QStringLiteral("确定"));
    }else if(OK == false)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("导出提示"),QStringLiteral("未能成功导出，请重新导出！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确定"));
        box.setWindowIcon(QIcon("screen/info.png"));
        box.exec();
        return;
    }
}

