#include <downwidget.h>
#include <QScrollBar>
#include <QHeaderView>
#include <QCalendarWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
#include <QAxObject>
#include <QTimer>
#include <QTextDocument>
#include <QPixmap>
#include <QFile>

int downwidget::allApkcount = 0;
int downwidget::highRiskcount = 0;
int downwidget::lowRiskcount = 0;

void downwidget::countCheckResultInfo()
{

    checkername = new QLabel(this->countCheckInfo);
    checkername->setGeometry(20, 20, 60, 30);
    QFont font = checkername->font();
    //font.setBold(true);
    checkername->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkername->setFont(font);
    checkername->setText(QStringLiteral("检测人："));

    checkernameText = new QLineEdit(this->countCheckInfo);
    checkernameText->setGeometry(90, 20, 150, 30);
    QFont font1 = checkername->font();
    font1.setBold(true);
    checkernameText->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkernameText->setFont(font1);

    checkerUnit = new QLabel(this->countCheckInfo);
    checkerUnit->setGeometry(280, 20, 80, 30);
    QFont font2 = checkerUnit->font();
    font2.setBold(true);
    checkerUnit->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkerUnit->setFont(font2);
    checkerUnit->setText(QStringLiteral("检测单位："));

    checkUnitText = new QLineEdit(this->countCheckInfo);
    checkUnitText->setGeometry(370, 20, 150, 30);
    QFont font31 = checkUnitText->font();
    font31.setBold(true);
    checkUnitText->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkUnitText->setFont(font31);

    Checkedname = new QLabel(this->countCheckInfo);
    Checkedname->setGeometry(550, 20, 80, 30);
    QFont font41 = Checkedname->font();
    font41.setBold(true);
    Checkedname->setStyleSheet("font: 12pt,Microsoft YaHei");
    Checkedname->setFont(font41);
    Checkedname->setText(QStringLiteral("被检测人："));

    CheckednameEdit = new QLineEdit(this->countCheckInfo);
    CheckednameEdit->setGeometry(640, 20, 150, 30);
    QFont font51 = checkUnitText->font();
    font51.setBold(true);
    CheckednameEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    CheckednameEdit->setFont(font51);

    checkedUnit = new QLabel(this->countCheckInfo);
    checkedUnit->setGeometry(820, 20, 100, 30);
    QFont font61 = checkedUnit->font();
    font61.setBold(true);
    checkedUnit->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkedUnit->setFont(font61);
    checkedUnit->setText(QStringLiteral("被检测单位："));

    checkedUnitEdit = new QLineEdit(this->countCheckInfo);
    checkedUnitEdit->setGeometry(930, 20, 170, 30);
    QFont font71 = checkedUnitEdit->font();
    font71.setBold(true);
    checkedUnitEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkedUnitEdit->setFont(font71);


    //第二行
    checkedPhone = new QLabel(this->countCheckInfo);
    checkedPhone->setGeometry(20, 65, 60, 30);
    QFont font0 = checkedPhone->font();
    font0.setBold(true);
    checkedPhone->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkedPhone->setFont(font0);
    checkedPhone->setText(QStringLiteral("手机号："));

    checkedPhoneText = new QLineEdit(this->countCheckInfo);
    checkedPhoneText->setGeometry(90, 65, 150, 30);
    QFont font11 = checkedPhoneText->font();
    font11.setBold(true);
    checkedPhoneText->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkedPhoneText->setFont(font11);

    checkedRemark= new QLabel(this->countCheckInfo);
    checkedRemark->setGeometry(280, 65, 80, 30);
    QFont font21 = checkedRemark->font();
    font21.setBold(true);
    checkedRemark->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkedRemark->setFont(font21);
    checkedRemark->setText(QStringLiteral("备        注："));

    checkRemarkEdit = new QLineEdit(this->countCheckInfo);
    checkRemarkEdit->setGeometry(370, 65, 150, 30);
    QFont font3 = checkRemarkEdit->font();
    font3.setBold(true);
    checkRemarkEdit->setStyleSheet("font: 12pt");
    checkRemarkEdit->setFont(font3);

    checkStartTime = new QLabel(this->countCheckInfo);
    checkStartTime->setGeometry(550, 65, 80, 30);
    QFont font4 = checkStartTime->font();
    font4.setBold(true);
    checkStartTime->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkStartTime->setFont(font4);
    checkStartTime->setText(QStringLiteral("起始时间："));

    checkStartEdit = new QDateTimeEdit(this->countCheckInfo);
    checkStartEdit->setGeometry(640, 65, 150, 30);

    //checkStartEdit->setStyleSheet("font: 12pt,Microsoft YaHei");

    checkStartEdit->setCalendarPopup(true);
    checkStartEdit->setDisplayFormat("yyyy-M-d");
    QDateTime Currenttime1 = QDateTime::currentDateTime();
    checkStartEdit->setDateTime(Currenttime1);
    //checkStartEdit->setStyleSheet("background-color:rgb(0,85,0)");
    QCalendarWidget *widget = checkStartEdit->calendarWidget();

    QFont font5 = widget->font();
    font5.setBold(true);
    widget->setStyleSheet("font: 12pt;color:rgb(0,85,0)");
    widget->setFont(font5);


    //widget->yearShown()
    QString strTemp;

    strTemp.append("QWidget{font:normal 12pt Microsoft YaHei;}");

        //QDateTimeEdit
        strTemp.append("QDateTimeEdit{border:1px solid gray; height:24px; }");
        strTemp.append("QDateTimeEdit::down-arrow{image:url(Resources/calendar.png);}");
        strTemp.append("QDateTimeEdit::drop-down{width:30px; border:0px solid red;\
                       subcontrol-origin: padding;subcontrol-position: top right;}");
        //QScrollBar
        strTemp.append("QScrollBar:vertical{background-color:white; width: 10px;}\
                       QScrollBar::handle:vertical{background-color:rgb(0, 159, 149); border:1px solid white;border-radius:2px; min-height:8px}\
                       QScrollBar::handle:vertical:hover{background-color:rgb(0, 102, 96);}\
                       QScrollBar::sub-line{background-color:white;}\
                       QScrollBar::add-line{background-color:white;}");

    checkStartEdit->setStyleSheet(strTemp);


    checkEndTime = new QLabel(this->countCheckInfo);
    checkEndTime->setGeometry(820, 65, 100, 30);
    QFont font6 = checkEndTime->font();
    font6.setBold(true);
    checkEndTime->setStyleSheet("font: 12pt,Microsoft YaHei");
    checkEndTime->setFont(font6);
    checkEndTime->setText(QStringLiteral("结 束 时 间："));

    checkEndEdit = new QDateTimeEdit(this->countCheckInfo);
    checkEndEdit->setGeometry(930, 65, 170, 30);
    QFont font7 = checkEndEdit->font();
    font7.setBold(true);
    checkEndEdit->setStyleSheet("font: 12pt;Microsoft YaHei");
    checkEndEdit->setFont(font7);
    checkEndEdit->setCalendarPopup(true);

    checkEndEdit->setDisplayFormat("yyyy-M-d");
    QDateTime Currenttime = QDateTime::currentDateTime();
    checkEndEdit->setDateTime(Currenttime);

    QCalendarWidget *widget2 = checkEndEdit->calendarWidget();
    QFont font52 = widget2->font();
    font52.setBold(true);
    widget2->setStyleSheet("font: 12pt;color:rgb(0,85,0)");
    widget2->setFont(font52);

    checkEndEdit->setStyleSheet(strTemp);


    countInfoSelect = new QPushButton(this->countCheckInfo);
    countInfoSelect->setGeometry(1160, 25, 120, 60);
    QFont font72 = countInfoSelect->font();
    font72.setBold(true);
    countInfoSelect->setStyleSheet("font: 12pt,Microsoft YaHei");
    countInfoSelect->setFont(font72);
    //countInfoSelect->setText(QStringLiteral("查 询"));
    countInfoSelect->setStyleSheet("QPushButton{border-image: url(:/sourceskin/checkcountinit.png);}"
                                   "QPushButton:hover{border-image: url(:/sourceskin/checkcounthover.png);}"
                                   "QPushButton:pressed{border-image: url(:/sourceskin/checkcountpress.png);}");

    //setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");

    countCheckInfoWidget();


    countSummary = new QWidget(this->countCheckInfo);
    //countSummary->setFixedSize(100,1280);
    countSummary->setStyleSheet("background-color:rgb(234, 234, 234)");
    //cutoff1->setGeometry(350,105,930,2);
    countSummary->setGeometry(0,500,1365,110);


    SummaryTitle = new QLabel(countSummary);
    SummaryTitle->setGeometry(10, 5, 100, 35);
    QFont font01 = SummaryTitle->font();
    font01.setBold(true);
    SummaryTitle->setStyleSheet("font: 14pt,Microsoft YaHei");
    SummaryTitle->setFont(font01);
    SummaryTitle->setText(QStringLiteral("合计信息"));

    Personcount = new QLabel(countSummary);
    Personcount->setGeometry(110, 45, 60, 30);
    QFont font02 = Personcount->font();
    font02.setBold(true);
    Personcount->setStyleSheet("font: 12pt,Microsoft YaHei");
    Personcount->setFont(font02);
    Personcount->setText(QStringLiteral("总人数："));

    PersoncountEdit = new QLabel(countSummary);
    PersoncountEdit->setGeometry(180, 45, 50, 30);
    QFont font03 = PersoncountEdit->font();
    font03.setBold(true);
    PersoncountEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    PersoncountEdit->setFont(font03);
    //PersoncountEdit->setText(QStringLiteral("总人数"));

    ApkCount = new QLabel(countSummary);
    ApkCount->setGeometry(250, 45, 80, 30);
    QFont font04 = ApkCount->font();
    font04.setBold(true);
    ApkCount->setStyleSheet("font: 12pt,Microsoft YaHei");
    ApkCount->setFont(font04);
    ApkCount->setText(QStringLiteral("应用总数："));


    ApkCountEdit = new QLabel(countSummary);
    ApkCountEdit->setGeometry(330, 45, 50, 30);
    QFont font05 = ApkCountEdit->font();
    font05.setBold(true);
    ApkCountEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    ApkCountEdit->setFont(font05);
    //ApkCountEdit->setText(QStringLiteral("应用总数:"));

    Highcount = new QLabel(countSummary);
    Highcount->setGeometry(410, 45, 110, 30);
    QFont font06 = Highcount->font();
    font06.setBold(true);
    Highcount->setStyleSheet("font: 12pt,Microsoft YaHei");
    Highcount->setFont(font06);
    Highcount->setText(QStringLiteral("高危权限总数："));

    HighCountEdit = new QLabel(countSummary);
    HighCountEdit->setGeometry(520, 45, 50, 30);
    QFont font07 = HighCountEdit->font();
    font07.setBold(true);
    HighCountEdit->setStyleSheet("font: 12pt,Microsoft YaHei");
    HighCountEdit->setFont(font07);

    Riskcout = new QLabel(countSummary);
    Riskcout->setGeometry(590, 45, 110, 30);
    QFont font08 = Riskcout->font();
    font08.setBold(true);
    Riskcout->setStyleSheet("font: 12pt,Microsoft YaHei");
    Riskcout->setFont(font08);
    Riskcout->setText(QStringLiteral("危险权限总数："));

    RiskcoutEdit = new QLabel(countSummary);
    RiskcoutEdit->setGeometry(700, 45, 50, 30);
    QFont font09 = RiskcoutEdit->font();
    font09.setBold(true);
    RiskcoutEdit->setStyleSheet("font: 12pt");
    RiskcoutEdit->setFont(font09);

    ReportSummary = new QPushButton(countSummary);
    ReportSummary->setGeometry(880, 40, 120, 50);
    QFont font23 = ReportSummary->font();
    font23.setBold(true);
    ReportSummary->setStyleSheet("font: 12pt,Microsoft YaHei");
    ReportSummary->setFont(font23);
    //ReportSummary->setText(QStringLiteral("报告汇总"));
    ReportSummary->setStyleSheet("QPushButton{border-image: url(:/sourceskin/countallinit.png);}"
                                 "QPushButton:hover{border-image: url(:/sourceskin/countallhover.png);}"
                                 "QPushButton:pressed{border-image: url(:/sourceskin/countallpress.png);}");

    connect(countInfoSelect,SIGNAL(clicked()),this,SLOT(slotCountCheckInfo()));
    connect(ReportSummary,SIGNAL(clicked()),this,SLOT(slotSummaryInfo()));


}

void downwidget::countCheckInfoWidget()
{

    countTablewidget = new QTableWidget(this->countCheckInfo);
    countTablewidget->setFixedSize(1360,385);
    countTablewidget->setGeometry(QRect(0,115,1250,385));

    countTablewidget->setAlternatingRowColors(true);
    countTablewidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    //countTablewidget->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    countTablewidget->setStyleSheet("color:rgb(68,68,68);font:13pt,Microsoft YaHei;");

    QScrollBar *Resulbar2 = countTablewidget->verticalScrollBar();
    Resulbar2->setStyleSheet("QScrollBar{background:lightgray;}");


    //countTablewidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    countTablewidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    countTablewidget->setSelectionMode(QAbstractItemView::SingleSelection);
    countTablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

    int i = 0;
    QStringList header2;
    header2<<QStringLiteral("序号")<<QStringLiteral("检测人")<<QStringLiteral("被检测人")<<QStringLiteral("被检测单位")<<QStringLiteral("手机号码")
          <<QStringLiteral("应用总数")<<QStringLiteral("高危权限")<<QStringLiteral("危险权限")<<QStringLiteral("检测时间")<<QStringLiteral("二维码")
          <<QStringLiteral("查看详情");

    countTablewidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

    QFont font2 = countTablewidget->horizontalHeader()->font();
    font2.setBold(true);
    countTablewidget->horizontalHeader()->setFixedHeight(40);

    countTablewidget->setColumnCount(11);
    countTablewidget->setHorizontalHeaderLabels(header2);

    countTablewidget->setRowHeight(i,300);
    countTablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    countTablewidget->setColumnWidth(0,50);
    countTablewidget->setColumnWidth(1,160);
    countTablewidget->setColumnWidth(2,160);
    countTablewidget->setColumnWidth(3,160);
    countTablewidget->setColumnWidth(4,190);
    countTablewidget->setColumnWidth(5,110);
    countTablewidget->setColumnWidth(6,110);
    countTablewidget->setColumnWidth(7,110);
    countTablewidget->setColumnWidth(8,110);
    countTablewidget->setColumnWidth(9,100);
    countTablewidget->setColumnWidth(10,100);


    //ContactTable->setShowGrid(false); //设置不显示格子线

    QHeaderView *columnhead2 = countTablewidget->verticalHeader();
    columnhead2->setVisible(false);

    //MessagesTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行


    //表头样式表
    countTablewidget->horizontalHeader()->setEnabled(false);

    QFont font = countTablewidget->horizontalHeader()->font();    //设置表头字体加粗
    font.setBold(true);

    //color:rgb(25, 70, 100)
    //countTablewidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(134, 245, 99, 255),stop:0.5 rgba(134, 148, 99, 255),stop:1 rgba(115, 87, 128, 255));color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    countTablewidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    int nRow = countTablewidget->rowCount();

    qDebug()<<nRow<<"All Count";
    for(int i1 = 0 ; i1 < nRow; i1++)
    {
       for(int j=0;j<10;j++)
       {
          //safeResultTable->setItem(i,j,new QTableWidgetItem(QString::number((i+1)*(j+1))));
          countTablewidget->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
    }

}

//槽信号统计查询信息
void downwidget::slotCountCheckInfo()
{
    countInfoSelect->setEnabled(false);
    int  Row =  countTablewidget->rowCount();
    for(int i= 0; i <Row ; i++)
    {
        countTablewidget->removeRow(0);
    }

    QString starttime  = checkStartEdit->dateTime().toString("yyyy-MM-dd");
    QString endtime = checkEndEdit->dateTime().toString("yyyy-MM-dd");

    qDebug()<<starttime<<endtime;

    QString checkername = checkernameText->text().trimmed();
    QString checkerunit = checkUnitText->text().trimmed();
    QString checkedname = CheckednameEdit->text().trimmed();
    QString checkedunit = checkedUnitEdit->text().trimmed();
    QString checkedphone = checkedPhoneText->text().trimmed();
    QString checkedremark = checkRemarkEdit->text().trimmed();

    qDebug()<<"gfwr"<<checkername;

    QStringList checklist =  cmdData::selectCheckInfo(starttime,endtime,checkername,checkerunit,
                                                      checkedname,checkedunit,checkedphone,checkedremark);
    //QStringList checklist;

   if(checklist.isEmpty())
   {
       qDebug()<<"checklist is empty";

       PersoncountEdit->setText("");
       ApkCountEdit->setText("");
       HighCountEdit->setText("");
       RiskcoutEdit->setText("");
       QMessageBox box(QMessageBox::Warning,QStringLiteral("查询提示"),QStringLiteral("根据您输入的查询条件未能查到数据!"));
       box.setStandardButtons (QMessageBox::Ok);
       box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
       box.setWindowIcon(QIcon("screen/Info2.png"));
       box.exec();
       QTimer::singleShot(100, &box, SLOT(close()));
       countInfoSelect->setEnabled(true);
       return;
   }else
   {
       addUpdateCheckWidget(checklist);
       return;
   }

}

void downwidget::addUpdateCheckWidget(QStringList list)
{
    int  Row =  countTablewidget->rowCount();
    for(int i= 0; i <Row ; i++)
    {
        countTablewidget->removeRow(0);
    }

    //QStringList list = cmdData::selectAllUserInfo();

    int count  = list.count();

    qDebug()<<count<<"uuu";

    for(int i = 0; i < count; i++)
    {
        countTablewidget->insertRow(i);

        QString info = list.at(i);
        qDebug()<<info;


        QStringList userlist = info.split(MSG_DATA_ITEMS_SEPARATOR);

        QString str = userlist.at(9);
        qDebug()<<str<<"i7iii";

        CheckQrcode[i] = new QPushButton();
        CheckQrcode[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/printcheckinit.png);}"
                                      "QPushButton:hover{border-image: url(:/sourceskin/printcheckhover.png);}"
                                      "QPushButton:pressed{border-image: url(:/sourceskin/printcheckpress.png);}");


        CheckQrcode[i]->setFixedSize(99,29);

        CheckInfoOPen[i] = new QPushButton();
        CheckInfoOPen[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/viewinit.png);}"
                                        "QPushButton:hover{border-image: url(:/sourceskin/viewhover.png);}"
                                        "QPushButton:pressed{border-image: url(:/sourceskin/viewpress.png);}");
        CheckInfoOPen[i]->setFixedSize(99,29);

        countTablewidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        countTablewidget->setItem(i,1,new QTableWidgetItem(userlist.at(0)));
        countTablewidget->setItem(i,2,new QTableWidgetItem(userlist.at(1)));
        countTablewidget->setItem(i,3,new QTableWidgetItem(userlist.at(2)));
        countTablewidget->setItem(i,4,new QTableWidgetItem(userlist.at(3)));
        countTablewidget->setItem(i,5,new QTableWidgetItem(userlist.at(4)));
        countTablewidget->setItem(i,6,new QTableWidgetItem(userlist.at(5)));
        countTablewidget->setItem(i,7,new QTableWidgetItem(userlist.at(6)));
        countTablewidget->setItem(i,8,new QTableWidgetItem(str.right(10)));

        countTablewidget->setCellWidget(i,9, CheckQrcode[i]);
        countTablewidget->setItem(i, 9, new QTableWidgetItem(userlist.at(7)));
        connect(CheckQrcode[i],SIGNAL(clicked()),this,SLOT(slotPrintQrcode()));

        countTablewidget->setCellWidget(i,10,CheckInfoOPen[i]);
        countTablewidget->setItem(i, 10, new QTableWidgetItem(userlist.at(8)));
        connect(CheckInfoOPen[i],SIGNAL(clicked()),this,SLOT(slotOpenCheckInfo()));

    }

    int nRow = countTablewidget->rowCount();
    qDebug()<<nRow<<"All Count";

    allApkcount = 0;
    highRiskcount = 0;
    lowRiskcount = 0;

    for(int i1 = 0 ; i1 < nRow; i1++)
    {
       for(int j=0;j<10;j++)
       {
          countTablewidget->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
       int apkcount = countTablewidget->item(i1,5)->data(Qt::DisplayRole).toInt();
       int high = countTablewidget->item(i1,6)->data(Qt::DisplayRole).toInt();
       int low = countTablewidget->item(i1,7)->data(Qt::DisplayRole).toInt();

        //countTablewidget->item(i1,5)->data(Qt::DisplayRole).toInt();
       allApkcount  = allApkcount + apkcount;
       highRiskcount = highRiskcount+high;
       lowRiskcount = lowRiskcount+low;
    }

    //统计信息设置

    PersoncountEdit->setText(QString::number(nRow));
    ApkCountEdit->setText(QString::number(allApkcount));
    HighCountEdit->setText(QString::number(highRiskcount));
    RiskcoutEdit->setText(QString::number(lowRiskcount));

    countInfoSelect->setEnabled(true);

}


void downwidget::creatQrcodeImageForder()
{

    QString saveFileName= QDir::currentPath();

    QString currentpathPre = saveFileName.append("/").append("QrcodeImage");

    QDir *temp = new QDir;
    bool exist = temp->exists(currentpathPre);
    if(exist)
    {
       //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹已经存在！"));
        return;
    }
    else
    {
        bool ok = temp->mkdir(currentpathPre);
        if( ok )
        {
           //QMessageBox::warning(this,tr("创建文件夹"),tr("文件夹创建成功！"));
            return;
        }

    }

}

//打印二维码
void downwidget::slotPrintQrcode()
{

    qDebug()<<"打印二维码";

    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =countTablewidget->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    QString QcrodeStr = index.sibling(row,9).data().toString();

    QString checked  = index.sibling(row,2).data().toString();

    QString checker  = index.sibling(row,1).data().toString();

    QString time = index.sibling(row,8).data().toString();

    qDebug()<<time<<"";

    qDebug()<<QcrodeStr<<"strstr...";

    QFile f;
    QString saveFileName1= QDir::currentPath();
    QString pathname1 = saveFileName1.append("/QrcodeImage/").append("printqrcode").append(".png");
    f.remove(pathname1);

    m_printQrcode1 = new QPrintQcrode(this);

    creatQrcodeImageForder();

    //m_printQrcode->setFixedSize(40,40);
    //m_printQrcode1->show();
    m_printQrcode1->generateString(QcrodeStr);
    //m_printQrcode1->show();

    QString saveFileName= QDir::currentPath();

    QString pathname = saveFileName.append("/QrcodeImage/").append("printqrcode").append(".png");

    int size = 40;
    m_printQrcode1->image1->swap(*m_printQrcode1->image1);
    m_printQrcode1->saveImage(pathname,size,checked,checker,time);

    Qcrodeimg.load("QrcodeImage/printqrcode.png");

    //QcrodePrintPic();

}

void downwidget::QcrodePrintPic()
{
    QPrinter printer;       //---构建新对象
    QPrintDialog printDlg(&printer, this);
    printDlg.setVisible(false);
    printDlg.exec();

//    if (printDlg.exec())            // 用于判断用户是否点击“打印”按钮
//    {

//        qDebug()<<printDlg.exec()<<"oiooooooo";
        QPainter painter(&printer);
        QRect rect = painter.viewport();    //---获取Qpainter对象的矩形区域

        //QImage fitimage=Qcrodeimg.scaled(60,140,Qt::KeepAspectRatio);
        QSize size = Qcrodeimg.size();            //--获取图片的大小
        size.scale(rect.size(),Qt::KeepAspectRatio);    //----按照图形比例大小重新设置视口矩形区域

        //---打印图片
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(Qcrodeimg.rect());
        painter.drawImage(0, 0, Qcrodeimg);
//        printDlg.close();

        return;
//    }

}

//printer.setPageSizeMM(QSizeF(QSize(12.5,30)));
//printer.setPaperSize((QSizeF(QSize(12,30))),QPrinter::Millimeter);
//printer.setOrientation(QPrinter::Landscape);

//    printDlg.accept();

//    printDlg.setFixedSize(QSize(12,30));
//    printDlg.setOrientation(Qt::Horizontal);

//void downwidget::QprintPDdf()
//{
//    QPrinter printer_pixmap(QPrinter::HighResolution);
//    printer_pixmap.setPageSize(QPrinter::Custom); //设置纸张尺寸，默认不设置就是A4
//    printer_pixmap.setPaperSize((QSizeF(QSize(30,12))),QPrinter::Millimeter);
//    //printer_pixmap.setPageSize(QPrinter::A4);  //设置纸张大小为A4
//    printer_pixmap.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf

//    //设置PDF输出路径
//    QString saveFileName= QDir::currentPath();
//    QString file_path = saveFileName.append("/QrcodeImage/").append("print").append(".pdf");
//    printer_pixmap.setOutputFileName(file_path);
//    //printer_pixmap.setOutputFileName("E:\\test_pixmap.pdf");   //设置输出路径


//    QPixmap pixmap1;
//    pixmap1.load("QrcodeImage/printqrcode.png");
//    QPixmap pixmap=pixmap1.scaled(42,42,Qt::KeepAspectRatio);
//    QImage fitimage=Qcrodeimg.scaled(42,42,Qt::KeepAspectRatio);

//    QPainter painter;
//    painter.begin(&printer_pixmap);
//    QRect rect = painter.viewport();
//    int multiple = rect.width()/pixmap.width();
//    painter.scale(16, 16); //将图像(所有要画的东西)在pdf上放大multiple-1倍

//    painter.drawPixmap(0,0,pixmap);  //画图
//    //painter.drawImage(0,0,fitimage);  //画图

//    QFont font;
//    font.setPixelSize(7);
//    font.setBold(true);
//    painter.setFont(font);
//    painter.drawText(25,2,QStringLiteral("受检人:")); //图文混排
//    painter.drawText(55,2,QStringLiteral("李剑")); //图文混排
//    painter.drawText(25,12,QStringLiteral("检查人:")); //图文混排
//    painter.drawText(55,12,QStringLiteral("admin")); //图文混排
//    painter.drawText(25,22,QStringLiteral("日期:")); //图文混排
//    painter.drawText(48,22,QStringLiteral("2017-02-26")); //图文混排

//    painter.end();
//}


//打开检测文档
void downwidget::slotOpenCheckInfo()
{

    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =countTablewidget->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    QString filepath = index.sibling(row,10).data().toString();

    QDesktopServices::openUrl(QUrl::fromLocalFile(filepath));


//    qDebug()<<MsgBox::CurrentUsername;

//    modifypass = new MsgBox(this);
//    modifypass->ModifyPassword(MsgBox::CurrentUsername);
//    modifypass->show();

//    connect(modifypass->exportbutton,SIGNAL(clicked()),this,SLOT(slotModifyPassok()));


}

//汇总报告槽函数
void downwidget::slotSummaryInfo()
{
        int allrow = countTablewidget->rowCount();

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
        QString fileName = QFileDialog::getSaveFileName(countTablewidget, QStringLiteral("保存"),
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
                    int i,j,colcount=countTablewidget->columnCount() - 1;
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
                        col->setProperty("ColumnWidth", countTablewidget->columnWidth(i)/9);
                        cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
                        columnName=countTablewidget->horizontalHeaderItem(i)->text();

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
                    cellInfo->setProperty("ColumnWidth", countTablewidget->columnWidth(colcount-1)/3);

                    //数据区
                    int rowcount =  countTablewidget->rowCount();

                    for(i=0;i<rowcount;i++)
                    {
                        for (j=0;j<colcount-1;j++)
                        {
                            worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", countTablewidget->item(i,j)?countTablewidget->item(i,j)->text():"");
                        }
                        QString str = countTablewidget->item(i,colcount)->text();
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
                    merge_cell.append(QString::number(countTablewidget->rowCount()+3));  //初始行
                    merge_cell.append(":");
                    merge_cell.append(QChar(9 - 1 + 'A'));  //终止列
                    merge_cell.append(QString::number(countTablewidget->rowCount()+3));  //终止行
                    QAxObject *merge_range = worksheet->querySubObject("Range(const QString&)", merge_cell);
                    merge_range->setProperty("HorizontalAlignment", -4131);
                    merge_range->setProperty("VerticalAlignment", -4131);
                    merge_range->setProperty("WrapText", true);
                    merge_range->setProperty("MergeCells", true);  //合并单元格

                    merge_cell1.append(QChar(1 - 1 + 'A'));  //初始列
                    merge_cell1.append(QString::number(countTablewidget->rowCount()+4));  //初始行
                    merge_cell1.append(":");
                    merge_cell1.append(QChar(9 - 1 + 'A'));  //终止列
                    merge_cell1.append(QString::number(countTablewidget->rowCount()+4));  //终止行
                    QAxObject *merge_range1 = worksheet->querySubObject("Range(const QString&)", merge_cell1);
                    merge_range1->setProperty("HorizontalAlignment", -4131);
                    merge_range1->setProperty("VerticalAlignment", -4131);
                    merge_range1->setProperty("WrapText", true);
                    merge_range1->setProperty("MergeCells", true);  //合并单元格

                    //导出时间条件
                    QString ExportTime;
                    QString starttime  = checkStartEdit->dateTime().toString("yyyy-MM-dd");
                    QString endtime = checkEndEdit->dateTime().toString("yyyy-MM-dd");
                    QString time1 = QStringLiteral("起始时间：%1").arg(starttime);
                    QString time2 = QStringLiteral("  结束时间：%2").arg(endtime);
                    ExportTime = ExportTime.append(time1).append(time2);

                    //统计总数
                    QString Exportamount = QStringLiteral("合   计：");
                    QString count1 = QStringLiteral(" 总人数：%1").arg(QString::number(countTablewidget->rowCount()));
                    QString count2 = QStringLiteral("  应用总数：%1").arg(allApkcount);
                    QString count3 = QStringLiteral("  高危权限总数：%1").arg(highRiskcount);
                    QString count4 = QStringLiteral("  危险权限总数：%1").arg(lowRiskcount);
                    Exportamount = Exportamount.append(count1).append(count2).append(count3).append(count4);


                    worksheet->querySubObject("Cells(int,int)",rowcount+3, 1)->dynamicCall("SetValue(const QString&)",ExportTime);
                    worksheet->querySubObject("Cells(int,int)",rowcount+4, 1)->dynamicCall("SetValue(const QString&)",Exportamount);

                    //画框线
                    QString lrange;
                    lrange.append("A2:");
                    lrange.append(colcount - 1 + 'A');
                    lrange.append(QString::number(countTablewidget->rowCount() + 4));
                    range = worksheet->querySubObject("Range(const QString&)", lrange);
                    range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
                    range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));

                    //调整数据区行高
                    QString rowsName;
                    rowsName.append("2:");
                    rowsName.append(QString::number(countTablewidget->rowCount() + 4));
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


