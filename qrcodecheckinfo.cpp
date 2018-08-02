#include <downwidget.h>
#include <QScrollBar>
#include <QHeaderView>
#include <QCalendarWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
#include <QAxObject>
#include <QScreen>


int downwidget::qallApkcount;
int downwidget::qhighRiskcount;
int downwidget::qlowRiskcount;

QLineEdit* downwidget::QrcodeEdit;
QLabel* downwidget::QrcodeLabel;

HHOOK downwidget::hookkeyboard = NULL;
LRESULT WINAPI downwidget::KeyBoardProc(int nCode,WPARAM wparam,LPARAM lparam)
{
//      if(nCode>=0)
//      {

//          if (wparam == WM_KEYDOWN)
//          {
//                LPKBDLLHOOKSTRUCT pKeyBoardHook =(LPKBDLLHOOKSTRUCT)lparam;

//                //如果截获到键盘消息就利用函数指针传递

//                QString	strVKCode;
//                BYTE keyBoardState[256] = {0};
//                GetKeyboardState(keyBoardState);

//                 qDebug()<<"thjjhjh";
//                 static DWORD tickCount = 0;
//                 if ((GetTickCount() - tickCount) > 50)
//                 {
//                             strVKCode = "";
//                 }
//                 WCHAR lpString[1024] = {0};
//                 ToUnicode(pKeyBoardHook->vkCode, pKeyBoardHook->scanCode, keyBoardState, lpString, 1024, 0);
//                 qDebug()<<"fefeqfqef";
//                 QString str = QString::fromWCharArray(lpString);
//                 strVKCode = strVKCode.append(str);
//                 //strVKCode += lpString;
//                 tickCount = GetTickCount();

//                 qDebug()<<strVKCode<<"888";

//                 if(strVKCode.contains("#&%"))
//                 {


//                     QStringList list = strVKCode.split("%");

//                     QString str = list.at(1);
//                     qDebug()<<str;

//                     //downwidget* widget1 =  Instance();
//                     //pdWidget1->QrcodeLabel->setText(QStringLiteral(" 扫码结果："));


//                     //emit m_widget->SiganlUpdateQrcode(str);
//                     //qDebug()<<str1<<"kuk";

//                 }
//                 //QrcodeEdit->setText(strVKCode);
//                 //QrcodeLabel->setText(QStringLiteral(" 扫 码 结 果:"));
//                 //SelectByQcrode(strVKCode);
//                 qDebug()<<strVKCode<<"12354566";
//           }

//        }

        return CallNextHookEx(hookkeyboard,nCode,wparam,lparam);

}


void downwidget::QrcodeCheckInfo()
{

    //QPushButton *SweepQrcode;
    //QLineEdit *QrcodeText;

    SweepQrcode = new QPushButton(this->countQrcode);
    SweepQrcode->setGeometry(1020, 20, 130, 60);
    QFont font72 = SweepQrcode->font();
    font72.setBold(true);
    SweepQrcode->setStyleSheet("font: 15pt");  //,Microsoft YaHei
    SweepQrcode->setFont(font72);
    //SweepQrcode->setText(QStringLiteral("扫 码"));
    SweepQrcode->setStyleSheet("QPushButton{border-image: url(:/sourceskin/swepinit.png);}"
                               "QPushButton:hover{border-image: url(:/sourceskin/swephover.png);}"
                               "QPushButton:pressed{border-image: url(:/sourceskin/sweppress.png);}");

//    QrcodeLabel = new QLabel(this->countQrcode);
//    QrcodeLabel->setGeometry(10, 22, 120, 55);
//    QFont font73 = QrcodeLabel->font();
//    font73.setBold(true);
//    QrcodeLabel->setStyleSheet("font: 15pt");  //,Microsoft YaHei
//    QrcodeLabel->setFont(font72);
//    QrcodeLabel->setText(QStringLiteral("  请 扫 码："));
//    QrcodeLabel->setStyleSheet("color:rgb(255,255,0);background-color:rgb(0,85,0);font:15pt,Microsoft YaHei");


//    //QLabel *QrcodeEdit;

//    //= QLineEdit(downwidget->countQrcode)
//    QrcodeEdit = new QLineEdit(this->countQrcode);
//    QrcodeEdit->setGeometry(170, 22, 200, 55);
//    QFont font74 = QrcodeEdit->font();
//    font74.setBold(true);
//    QrcodeEdit->setStyleSheet("font: 15pt");  //,Microsoft YaHei
//    QrcodeEdit->setFont(font74);



//setStyleSheet("color:rgb(255,255,0);background-color:rgb(0,85,0);font:15pt");


//    checkedUnitEdit = new QLineEdit(this->countCheckInfo);
//    checkedUnitEdit->setGeometry(880, 20, 170, 30);
//    QFont font71 = checkedUnitEdit->font();
//    font71.setBold(true);
//    checkedUnitEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
//    checkedUnitEdit->setFont(font71);

    countQrocdeCheckWidget();


    QcountSummary = new QWidget(this->countQrcode);
    //countSummary->setFixedSize(100,1280);
    QcountSummary->setStyleSheet("background-color:rgb(234, 234, 234)");
    //cutoff1->setGeometry(350,105,930,2);
    //QcountSummary->setGeometry(0,500,1280,100);
    QcountSummary->setGeometry(0,500,1365,110);

    QSummaryTitle = new QLabel(QcountSummary);
    QSummaryTitle->setGeometry(10, 5, 100, 35);
    QFont font01 = QSummaryTitle->font();
    font01.setBold(true);
    QSummaryTitle->setStyleSheet("font: 14pt,Microsoft YaHei"); //
    QSummaryTitle->setFont(font01);
    QSummaryTitle->setText(QStringLiteral("合计信息"));

    QPersoncount = new QLabel(QcountSummary);
    QPersoncount->setGeometry(110, 45, 60, 30);
    QFont font02 = QPersoncount->font();
    font02.setBold(true);
    QPersoncount->setStyleSheet("font: 12pt,Microsoft YaHei");
    QPersoncount->setFont(font02);
    QPersoncount->setText(QStringLiteral("总人数："));

    QPersoncountEdit = new QLabel(QcountSummary);
    QPersoncountEdit->setGeometry(180, 45, 50, 30);
    QFont font03 = QPersoncountEdit->font();
    font03.setBold(true);
    QPersoncountEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    QPersoncountEdit->setFont(font03);
    //PersoncountEdit->setText(QStringLiteral("总人数"));

    QApkCount = new QLabel(QcountSummary);
    QApkCount->setGeometry(250, 45, 80, 30);
    QFont font04 = QApkCount->font();
    font04.setBold(true);
    QApkCount->setStyleSheet("font: 12pt,Microsoft YaHei");
    QApkCount->setFont(font04);
    QApkCount->setText(QStringLiteral("应用总数："));


    QApkCountEdit = new QLabel(QcountSummary);
    QApkCountEdit->setGeometry(330, 45, 50, 30);
    QFont font05 = QApkCountEdit->font();
    font05.setBold(true);
    QApkCountEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    QApkCountEdit->setFont(font05);
    //ApkCountEdit->setText(QStringLiteral("应用总数:"));

    QHighcount = new QLabel(QcountSummary);
    QHighcount->setGeometry(410, 45, 110, 30);
    QFont font06 = QHighcount->font();
    font06.setBold(true);
    QHighcount->setStyleSheet("font: 12pt,Microsoft YaHei");
    QHighcount->setFont(font06);
    QHighcount->setText(QStringLiteral("高危权限总数："));

    QHighCountEdit = new QLabel(QcountSummary);
    QHighCountEdit->setGeometry(520, 45, 50, 30);
    QFont font07 = QHighCountEdit->font();
    font07.setBold(true);
    QHighCountEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    QHighCountEdit->setFont(font07);

    QRiskcout = new QLabel(QcountSummary);
    QRiskcout->setGeometry(590, 45, 110, 30);
    QFont font08 = QRiskcout->font();
    font08.setBold(true);
    QRiskcout->setStyleSheet("font: 12pt,Microsoft YaHei");
    QRiskcout->setFont(font08);
    QRiskcout->setText(QStringLiteral("危险权限总数："));

    QRiskcoutEdit = new QLabel(QcountSummary);
    QRiskcoutEdit->setGeometry(700, 45, 50, 30);
    QFont font09 = QRiskcoutEdit->font();
    font09.setBold(true);
    QRiskcoutEdit->setStyleSheet("font: 12pt");
    QRiskcoutEdit->setFont(font09);

    QReportSummary = new QPushButton(QcountSummary);
    QReportSummary->setGeometry(880, 40, 120, 50);
    QFont font23 = QReportSummary->font();
    font23.setBold(true);
    QReportSummary->setStyleSheet("font: 12pt,Microsoft YaHei");
    QReportSummary->setFont(font23);
    //QReportSummary->setText(QStringLiteral("报告汇总"));
    //ReportSummary->setStyleSheet("color:rgb(255,255,255);font: 16pt;background-color:rgb(0,85,0)");
    QReportSummary->setStyleSheet("QPushButton{border-image: url(:/sourceskin/countallinit.png);}"
                                  "QPushButton:hover{border-image: url(:/sourceskin/countallhover.png);}"
                                  "QPushButton:pressed{border-image: url(:/sourceskin/countallpress.png);}");

            //setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");


    connect(SweepQrcode,SIGNAL(clicked()),this,SLOT(slotQCountCheckInfo()));
    connect(QReportSummary,SIGNAL(clicked()),this,SLOT(slotQSummaryInfo()));

    hookkeyboard = SetWindowsHookEx(WH_KEYBOARD_LL,KeyBoardProc,0,0);

}

void downwidget::countQrocdeCheckWidget()
{
     //QWidget *countQrocdeWidget;

     //二维码查询数据表格
     countQrocdeWidget = new QTableWidget(this->countQrcode);
     //countQrocdeWidget->setFixedSize(1280,405);
      countQrocdeWidget->setFixedSize(1360,405);
     countQrocdeWidget->setGeometry(0,95,1250,405);

     countQrocdeWidget->setAlternatingRowColors(true);
     countQrocdeWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
     //countTablewidget->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
     countQrocdeWidget->setStyleSheet("color:rgb(68,68,68);font:13pt,Microsoft YaHei;");

     QScrollBar *Resulbar2 = countQrocdeWidget->verticalScrollBar();
     Resulbar2->setStyleSheet("QScrollBar{background:lightgray;}");


     //countTablewidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     countQrocdeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

     countQrocdeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
     countQrocdeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

     //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

     int i = 0;
     QStringList header2;


     header2<<QStringLiteral("序号")<<QStringLiteral("检测人")<<QStringLiteral("被检测人")<<QStringLiteral("被检测单位")<<QStringLiteral("手机号码")
           <<QStringLiteral("应用总数")<<QStringLiteral("高危权限")<<QStringLiteral("危险权限")<<QStringLiteral("检测时间")<<QStringLiteral("二维码")
           <<QStringLiteral("查看详情");


     countQrocdeWidget->setColumnCount(11);
     countQrocdeWidget->setHorizontalHeaderLabels(header2);

     countQrocdeWidget->setRowHeight(i,300);
     countQrocdeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
     countQrocdeWidget->setColumnWidth(0,50);
     countQrocdeWidget->setColumnWidth(1,160);
     countQrocdeWidget->setColumnWidth(2,160);
     countQrocdeWidget->setColumnWidth(3,160);
     countQrocdeWidget->setColumnWidth(4,190);
     countQrocdeWidget->setColumnWidth(5,110);
     countQrocdeWidget->setColumnWidth(6,110);
     countQrocdeWidget->setColumnWidth(7,110);
     countQrocdeWidget->setColumnWidth(8,110);
     countQrocdeWidget->setColumnWidth(9,100);
     countQrocdeWidget->setColumnWidth(10,100);

     countQrocdeWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

     QFont font2 = countQrocdeWidget->horizontalHeader()->font();
     font2.setBold(true);
     countQrocdeWidget->horizontalHeader()->setFixedHeight(40);


     //ContactTable->setShowGrid(false); //设置不显示格子线

     QHeaderView *columnhead2 = countQrocdeWidget->verticalHeader();
     columnhead2->setVisible(false);


     //表头样式表
     countQrocdeWidget->horizontalHeader()->setEnabled(false);

     QFont font =countQrocdeWidget->horizontalHeader()->font();    //设置表头字体加粗
     font.setBold(true);

     //color:rgb(25, 70, 100)
     //countTablewidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(134, 245, 99, 255),stop:0.5 rgba(134, 148, 99, 255),stop:1 rgba(115, 87, 128, 255));color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

     countQrocdeWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色


     //MessagesTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
     int nRow = countQrocdeWidget->rowCount();

     qDebug()<<nRow<<"All Count";
     for(int i1 = 0 ; i1 < nRow; i1++)
     {
        for(int j=0;j<10;j++)
        {
           //safeResultTable->setItem(i,j,new QTableWidgetItem(QString::number((i+1)*(j+1))));
           countQrocdeWidget->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        }
     }
}

void downwidget::slotQCountCheckInfo()
{

    qcrodewidget  = new MsgBox(this);
    qcrodewidget->setSwepQrcodeInfo();
    qcrodewidget->show();

    connect(qcrodewidget->swepQrcodeEdit,SIGNAL(returnPressed()),this,SLOT(slotSelectByQcrode()));
    qcrodewidget->m_closebtn->setEnabled(true);

}
void downwidget::slotSelectByQcrode()
{
     //qcrodewidget->m_closebtn->setEnabled(false);

     QString qcordeStr = qcrodewidget->swepQrcodeEdit->text().trimmed();

     if(qcordeStr.isEmpty())
     {
         //qcrodewidget->m_closebtn->setEnabled(false);
         //qcrodewidget->m_closebtn->setDefault(false);
         qcrodewidget->m_closebtn->setDefault(false);
         QMessageBox box(QMessageBox::Warning,QStringLiteral("查询提示"),QStringLiteral("未发现数据，请先扫码!"));
         box.setStandardButtons (QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/Info2.png"));
         //qcrodewidget->m_closebtn->setEnabled(true);
         box.exec();

         return;
     }else
     {

         qDebug()<<"gfwr"<<qcordeStr ;

         //qcrodewidget->close();

         QStringList checklist =  cmdData::selectCheckByQcrode(qcordeStr);

         if(checklist.isEmpty())
         {
             qDebug()<<"checklist is empty";
             qcrodewidget->m_closebtn->setDefault(false);
             QMessageBox box(QMessageBox::Warning,QStringLiteral("提示"),QStringLiteral("扫码未能查到数据，请重新扫码!"));
             box.setStandardButtons (QMessageBox::Ok);
             box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
             box.setWindowIcon(QIcon("screen/Info2.png"));
             box.exec();
             qcrodewidget->swepQrcodeEdit->clear();
             qcrodewidget->swepQrcodeEdit->setFocus();
             return;
          }else
          {
              //addUpdateCheckWidget(checklist);
              addQrcrodeCheckWidget(checklist);
              qcrodewidget->close();
              return;
          }

      }

}

void downwidget::SelectByQcrode(QString qcordestr)
{

    if(qcordestr.isEmpty())
    {
        //qcrodewidget->m_closebtn->setEnabled(false);
        //qcrodewidget->m_closebtn->setDefault(false);
        //qcrodewidget->m_closebtn->setDefault(false);
        QMessageBox box(QMessageBox::Warning,QStringLiteral("查询提示"),QStringLiteral("未发现数据，请先扫码!"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/Info2.png"));
        //qcrodewidget->m_closebtn->setEnabled(true);
        box.exec();

        return;
    }else
    {

        qDebug()<<"gfwr"<<qcordestr ;

        //qcrodewidget->close();

        QStringList checklist = cmdData::selectCheckByQcrode(qcordestr);

        if(checklist.isEmpty())
        {
            qDebug()<<"checklist is empty";

            QMessageBox box(QMessageBox::Warning,QStringLiteral("提示"),QStringLiteral("扫码未能查到数据，请重新扫码!"));
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
            box.setWindowIcon(QIcon("screen/Info2.png"));
            box.exec();

            return;
         }else
         {

             addQrcrodeCheckWidget(checklist);
             QrcodeEdit->setText("");
             QrcodeLabel->setText(QStringLiteral(" 请 扫 码："));
             return;
         }

     }
}

void downwidget::addQrcrodeCheckWidget(QStringList list)
{

    int  Row =  countQrocdeWidget->rowCount();
    for(int i= 0; i <Row ; i++)
    {
        countQrocdeWidget->removeRow(0);
    }

    //QStringList list = cmdData::selectAllUserInfo();

    int count  = list.count();

    qDebug()<<count<<"uuu";

    for(int i = 0; i < count; i++)
    {
        countQrocdeWidget->insertRow(i);

        QString info = list.at(i);
        qDebug()<<info;


        QStringList userlist = info.split(MSG_DATA_ITEMS_SEPARATOR);

        QString str = userlist.at(9);

        QCheckQrcode[i] = new QPushButton();
        QCheckQrcode[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/printcheckinit.png);}"
                                       "QPushButton:hover{border-image: url(:/sourceskin/printcheckhover.png);}"
                                       "QPushButton:pressed{border-image: url(:/sourceskin/printcheckpress.png);}");


        QCheckQrcode[i]->setFixedSize(99,29);

        QCheckInfoOPen[i] = new QPushButton();
        QCheckInfoOPen[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/viewinit.png);}"
                                         "QPushButton:hover{border-image: url(:/sourceskin/viewhover.png);}"
                                         "QPushButton:pressed{border-image: url(:/sourceskin/viewpress.png);}");

        QCheckInfoOPen[i]->setFixedSize(98,29);

        countQrocdeWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        countQrocdeWidget->setItem(i,1,new QTableWidgetItem(userlist.at(0)));
        countQrocdeWidget->setItem(i,2,new QTableWidgetItem(userlist.at(1)));
        countQrocdeWidget->setItem(i,3,new QTableWidgetItem(userlist.at(2)));
        countQrocdeWidget->setItem(i,4,new QTableWidgetItem(userlist.at(3)));
        countQrocdeWidget->setItem(i,5,new QTableWidgetItem(userlist.at(4)));
        countQrocdeWidget->setItem(i,6,new QTableWidgetItem(userlist.at(5)));
        countQrocdeWidget->setItem(i,7,new QTableWidgetItem(userlist.at(6)));
        countQrocdeWidget->setItem(i,8,new QTableWidgetItem(str.right(10)));


        countQrocdeWidget->setCellWidget(i,9, QCheckQrcode[i]);
        countQrocdeWidget->setItem(i, 9, new QTableWidgetItem(userlist.at(7)));
        connect(QCheckQrcode[i],SIGNAL(clicked()),this,SLOT(slotQPrintQrcode()));

        countQrocdeWidget->setCellWidget(i,10,QCheckInfoOPen[i]);
        countQrocdeWidget->setItem(i, 10, new QTableWidgetItem(userlist.at(8)));
        connect(QCheckInfoOPen[i],SIGNAL(clicked()),this,SLOT(slotQOpenCheckInfo()));

    }

    int nRow = countQrocdeWidget->rowCount();
    qDebug()<<nRow<<"All Count";

    qallApkcount = 0;
    qhighRiskcount = 0;
    qlowRiskcount = 0;

    for(int i1 = 0 ; i1 < nRow; i1++)
    {
       for(int j=0;j<10;j++)
       {
          countQrocdeWidget->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
       int apkcount = countQrocdeWidget->item(i1,5)->data(Qt::DisplayRole).toInt();
       int high = countQrocdeWidget->item(i1,6)->data(Qt::DisplayRole).toInt();
       int low = countQrocdeWidget->item(i1,7)->data(Qt::DisplayRole).toInt();

        //countTablewidget->item(i1,5)->data(Qt::DisplayRole).toInt();
       qallApkcount  = qallApkcount + apkcount;
       qhighRiskcount = qhighRiskcount+high;
       qlowRiskcount = qlowRiskcount+low;
    }
    //统计信息设置
    QPersoncountEdit->setText(QString::number(nRow));
    QApkCountEdit->setText(QString::number(qallApkcount));
    QHighCountEdit->setText(QString::number(qhighRiskcount));
    QRiskcoutEdit->setText(QString::number(qlowRiskcount));

}

void downwidget::slotQPrintQrcode()
{

     qDebug()<<"打印二维码";

     QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
     if(senderObj == 0)
     {
             return;
     }
     QModelIndex index =countQrocdeWidget->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
     //int currentrow=index.row();

     int row = index.row();
     qDebug()<<"dangqian row:"<<row;


     QString QcrodeStr = index.sibling(row,9).data().toString();

     QString checked  = index.sibling(row,2).data().toString();

     QString checker  = index.sibling(row,1).data().toString();

     QString time = index.sibling(row,8).data().toString();

     qDebug()<<time<<"";

     qDebug()<<QcrodeStr<<"strstr...";

     m_printQrcode1 = new QPrintQcrode(this);

     creatQrcodeImageForder();

     m_printQrcode1->generateString(QcrodeStr);

     QString saveFileName= QDir::currentPath();

     QString pathname = saveFileName.append("/QrcodeImage/").append("printqrcode").append(".png");

     int size = 40;

     m_printQrcode1->saveImage(pathname,size,checked,checker,time);

     Qcrodeimg.load("QrcodeImage/printqrcode.png");

     QcrodePrintPic();


}

void downwidget::slotQOpenCheckInfo()
{

    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =countQrocdeWidget->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    QString filepath = index.sibling(row,10).data().toString();

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath));
}



void downwidget::slotUpdateQrcode(QString num)
{
    qDebug()<<"grgrrg";
    QrcodeLabel->setText(QStringLiteral(" 扫码结果："));
    QrcodeText->setText(num);

}

void downwidget::slotQSummaryInfo()
{


    qDebug()<<"7u7ju7u7";

    QString defaultFileName = QStringLiteral("汇总记录%1").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QString dirstr = defaultFileName.append(".xls");
    QString saveFileName= QDir::currentPath();
    QString path  = saveFileName.append("/%1").arg(dirstr);
    qDebug()<<"r1rr"<<path;

    int allrow = countQrocdeWidget->rowCount();


    if(allrow == 0)
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("汇总提示"),QStringLiteral("没有报告需要汇总!"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/Info2.png"));
        box.exec();
        return;
    }

    QString title = QStringLiteral("汇总报告");
    //QString str1 = "Excel 文件(*.xls *.xlsx)"

//    QString defaultFileName = QStringLiteral("汇总记录%1").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
//    QString dirstr = defaultFileName.append(".xls");
//    QString saveFileName= QDir::currentPath();
//    QString path  = saveFileName.append(dirstr);
//    qDebug()<<"r1rr"<<path;
    //QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
    QString fileName = QFileDialog::getSaveFileName(countQrocdeWidget, QStringLiteral("保存"),
                 QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                "Excel(*.xls *.xlsx)");

        if (fileName!="")
        {
            QAxObject *excel = new QAxObject;
            if (excel->setControl("Excel.Application")) //连接Excel控件
            {
                excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
                excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
                QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
                workbooks->dynamicCall("Add");//新建一个工作簿
                QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
                QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
                int i,j,colcount=countQrocdeWidget->columnCount() - 1;
                QAxObject *cell,*col ,*cellInfo;
                //标题行
                cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
                cell->dynamicCall("SetValue(const QString&)", title);
                cell->querySubObject("Font")->setProperty("Size", 18);
                //调整行高
                worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
                //合并标题行
                QString cellTitle;
                cellTitle.append("A1:");
                cellTitle.append(QChar(colcount - 1 + 'A'));
                cellTitle.append(QString::number(1));
                QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
                range->setProperty("WrapText", true);
                range->setProperty("MergeCells", true);
                range->setProperty("HorizontalAlignment", -4108);//xlCenter
                range->setProperty("VerticalAlignment", -4108);//xlCenter
                //列标题
                for(i=0;i<colcount-1;i++)
                {
                    QString columnName;
                    columnName.append(QChar(i  + 'A'));
                    columnName.append(":");
                    columnName.append(QChar(i + 'A'));
                    col = worksheet->querySubObject("Columns(const QString&)", columnName);
                    col->setProperty("ColumnWidth", countQrocdeWidget->columnWidth(i)/9);
                    cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                    columnName=countQrocdeWidget->horizontalHeaderItem(i)->text();

                    cell->dynamicCall("SetValue(const QString&)", columnName);
                    cell->querySubObject("Font")->setProperty("Bold", true);
                    cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                    cell->setProperty("HorizontalAlignment", -4108);//xlCenter
                    cell->setProperty("VerticalAlignment", -4108);//xlCenter
                }

                cellInfo=worksheet->querySubObject("Cells(int,int)", 2, colcount);
                QString columnNameInfo = QStringLiteral("详细报告名称");
                cellInfo->dynamicCall("SetValue(const QString&)",columnNameInfo);
                cellInfo->querySubObject("Font")->setProperty("Bold", true);
                cellInfo->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
                cellInfo->setProperty("HorizontalAlignment", -4108);//xlCenter
                cellInfo->setProperty("VerticalAlignment", -4108);//xlCenter
                cellInfo->setProperty("ColumnWidth", countQrocdeWidget->columnWidth(colcount-1)/3);

                //数据区
                int rowcount =  countQrocdeWidget->rowCount();

                for(i=0;i<rowcount;i++)
                {
                    for (j=0;j<colcount-1;j++)
                    {
                        worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", countQrocdeWidget->item(i,j)?countQrocdeWidget->item(i,j)->text():"");
                    }
                    QString str = countQrocdeWidget->item(i,colcount)->text();
                    qDebug()<<str<<"uki";
                    QStringList list = str.split("/");
                    if(!list.isEmpty())
                    {
                        int count = list.count();
                        QString fileName = list.at(count-1);
                        worksheet->querySubObject("Cells(int,int)", i+3, colcount)->dynamicCall("SetValue(const QString&)", fileName);
                    }else
                    {
                        worksheet->querySubObject("Cells(int,int)", i+3, colcount)->dynamicCall("SetValue(const QString&)", countTablewidget->item(i,j)?countTablewidget->item(i,j)->text():"");
                    }


                }

                QString merge_cell,merge_cell1;
                merge_cell.append(QChar(1 - 1 + 'A'));  //初始列
                merge_cell.append(QString::number(countQrocdeWidget->rowCount()+3));  //初始行
                merge_cell.append(":");
                merge_cell.append(QChar(9 - 1 + 'A'));  //终止列
                merge_cell.append(QString::number(countQrocdeWidget->rowCount()+3));  //终止行
                QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
                merge_range->setProperty("HorizontalAlignment", -4131);
                merge_range->setProperty("VerticalAlignment", -4131);
                merge_range->setProperty("WrapText", true);
                merge_range->setProperty("MergeCells", true);  //合并单元格

                merge_cell1.append(QChar(1 - 1 + 'A'));  //初始列
                merge_cell1.append(QString::number(countQrocdeWidget->rowCount()+4));  //初始行
                merge_cell1.append(":");
                merge_cell1.append(QChar(9 - 1 + 'A'));  //终止列
                merge_cell1.append(QString::number(countQrocdeWidget->rowCount()+4));  //终止行
                QAxObject *merge_range1 = worksheet->querySubObject("Range(const QString&)", merge_cell1);
                merge_range1->setProperty("HorizontalAlignment", -4131);
                merge_range1->setProperty("VerticalAlignment", -4131);
                merge_range1->setProperty("WrapText", true);
                merge_range1->setProperty("MergeCells", true);  //合并单元格

                //导出时间条件
                QString ExportTime  = QStringLiteral("");
                QString starttime  = checkStartEdit->dateTime().toString("yyyy-MM-dd");
                QString endtime = checkEndEdit->dateTime().toString("yyyy-MM-dd");
                QString time1 = QStringLiteral("起始时间：%1").arg(starttime);
                QString time2 = QStringLiteral("  结束时间：%2").arg(endtime);
                ExportTime = ExportTime.append(time1).append(time2);

                //统计总数
                QString Exportamount = QStringLiteral("合   计：");
                QString count1 = QStringLiteral("  总人数：%1").arg(QString::number(countQrocdeWidget->rowCount()));
                QString count2 = QStringLiteral("  应用总数：%1").arg(qallApkcount);
                QString count3 = QStringLiteral("  高危权限总数：%1").arg(qhighRiskcount);
                QString count4 = QStringLiteral("  危险权限总数：%1").arg(qlowRiskcount);
                Exportamount = Exportamount.append(count1).append(count2).append(count3).append(count4);


                worksheet->querySubObject("Cells(int,int)",rowcount+3, 1)->dynamicCall("SetValue(const QString&)",ExportTime);
                worksheet->querySubObject("Cells(int,int)",rowcount+4, 1)->dynamicCall("SetValue(const QString&)",Exportamount);

                //画框线
                QString lrange;
                lrange.append("A2:");
                lrange.append(colcount - 1 + 'A');
                lrange.append(QString::number(countQrocdeWidget->rowCount() + 4));
                range = worksheet->querySubObject("Range(const QString&)", lrange);
                range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
                range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));

                //调整数据区行高
                QString rowsName;
                rowsName.append("2:");
                rowsName.append(QString::number(countQrocdeWidget->rowCount() + 4));
                range = worksheet->querySubObject("Range(const QString&)", rowsName);
                range->setProperty("RowHeight", 20);
                workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
                workbook->dynamicCall("Close()");//关闭工作簿
                excel->dynamicCall("Quit()");//关闭excel
                delete excel;
                excel=NULL;
                QMessageBox box(QMessageBox::Question,QStringLiteral("完成"),QStringLiteral("文件已经导出，是否现在打开？"));
                box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
                box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
                box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
                box.setWindowIcon(QIcon("screen/open.ico"));

                if(box.exec() == QMessageBox::Ok)
                {
                    QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
                    //QDesktopServices::openUrl(QUrl::fromLocalFile(AppList::currentExportDir));
                    box.close();
                    return;
                }else
                {
                    box.close();
                    return;
                }

            }
            else
            {
                QMessageBox::warning(NULL,QStringLiteral("错误"),QStringLiteral("未能创建 Excel 对象，请安装 Microsoft Excel。"),QMessageBox::Apply);
            }
        }

}
