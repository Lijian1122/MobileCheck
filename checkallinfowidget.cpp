#include <downwidget.h>
#include <QStringList>
#include <QScrollBar>
#include <QHeaderView>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QByteArray>
#include <QJsonValue>
#include <QStringList>
#include <Common/applist.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <QDesktopServices>

int downwidget::contactInfoi = 0;
int downwidget::Callhistoryi = 0;
int downwidget::Messagei = 0;
int downwidget::Filei = 0;
int downwidget::nCurScroller = 0; //翻页时的当时滑动条
int downwidget::pageValue = 10; // 一页显示条数
int downwidget::pageIndex = 1; //页面索引
int downwidget::Messagecount;
int downwidget::MessageAllRow = 0;
int downwidget::count;

void downwidget::PhoneInfoCheckfun()
{
    //手机信息检测按钮
    buttonWidget= new QWidget(this->PhoneDatailInfowidget);
    buttonWidget->setFixedSize(270,610);
    //rgb(0,85,0);
    //buttonWidget->setStyleSheet("background-color:lightgray;");
    buttonWidget->setGeometry(0,0,250,600);

    labelPrompt = new QLabel(buttonWidget);
    labelPrompt->setText(QStringLiteral(" 未发现设备，请插入设备!"));
    labelPrompt->setAlignment(Qt::AlignCenter);
    labelPrompt->setFixedSize(250,60);
    labelPrompt->setStyleSheet("color:rgb(68,68,68);font:14pt,Microsoft YaHei;");
    labelPrompt->setGeometry(15,10,250,60);

    Contactsbutton = new QPushButton(this->PhoneDatailInfowidget);
//    Contactsbutton->setText(QStringLiteral("通讯录"));
    Contactsbutton->setFixedSize(160,60);
//    Contactsbutton->setStyleSheet("background-image:url(:/source/icon1/contactup.png);background-color:transparent;");
    Contactsbutton->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/contactinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/contatchover .png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/contactpress.png);}");

    Contactsbutton->setGeometry(55,105,160,60);


    Callhistorybutton = new QPushButton(this->PhoneDatailInfowidget);
    //Callhistorybutton->setText(QStringLiteral("通话记录"));
    Callhistorybutton->setFixedSize(160,60);
    //Callhistorybutton->setStyleSheet("color:rgb(255,255,255);font: 16pt;background-color:rgb(0,85,0)");
    //Callhistorybutton->setStyleSheet("background-image:url(:/source/icon1/callhistoryup.png);background-color:transparent;");
    Callhistorybutton->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/callhisinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/callhishover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/callhispress.png);}");
    Callhistorybutton->setGeometry(55,240,160,60);


    Messagesbutton = new QPushButton(this->PhoneDatailInfowidget);
    //Messagesbutton->setText(QStringLiteral("短信记录"));
    Messagesbutton->setFixedSize(160,60);
    //Messagesbutton->setStyleSheet("color:rgb(255,255,255);font: 16pt;background-color:rgb(0,85,0)");
    //Messagesbutton->setStyleSheet("background-image:url(:/source/icon1/messageup.png);background-color:transparent;");
    Messagesbutton->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/messageinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/messagehover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/mesaagepress.png);}");
    Messagesbutton->setGeometry(55,375,160,60);


    Filebutton = new QPushButton(this->PhoneDatailInfowidget);
    //Filebutton->setText(QStringLiteral("手机文件"));
    Filebutton->setFixedSize(160,60);
    Filebutton->setStyleSheet("background-image:url(:/source/icon1/Fileup.png);background-color:transparent;");
    //Filebutton->setStyleSheet("color:rgb(255,255,255);font: 16pt;background-color:rgb(0,85,0)");
    Filebutton->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/fileinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/filehover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/filepress.png);}");
    Filebutton->setGeometry(55,505,160,60);


    //显示检测表格

    MobileAllInfowidget = new QStackedWidget(this->PhoneDatailInfowidget);
    //MobileAllInfo->setText(QStringLiteral("手机文件检测"));
    //MobileAllInfowidget->setFixedSize(1020,600);
    MobileAllInfowidget->setFixedSize(1100,600);
    //Filebutton->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    MobileAllInfowidget->setGeometry(270,0,1020,600);

    ContactsWidget  = new QWidget();
    CallhistoryWidget = new QWidget();
    MessageWidget = new QWidget();
    FileWidget = new QWidget();

    MobileAllInfowidget->addWidget(ContactsWidget);
    MobileAllInfowidget->addWidget(CallhistoryWidget);
    MobileAllInfowidget->addWidget(MessageWidget);
    MobileAllInfowidget->addWidget(FileWidget);

    MobileAllInfowidget->setCurrentIndex(0);


    //通讯录检测
    ContactCheck =new QPushButton(ContactsWidget);
    ContactCheck->setFixedSize(120,50);

    ContactCheck->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/checkmoinit.png);}"
                                "QPushButton:hover{border-image: url(:/skin/sourceskin/checkmohover.png);}"
                                "QPushButton:pressed{border-image: url(:/skin/sourceskin/checkmopress.png);}");
    ContactCheck->setGeometry(QRect(800,20,120,50));

    ContactExport = new QPushButton(ContactsWidget);
    ContactExport->setFixedSize(120,50);
    ContactExport->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/exinfoinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/exinfohover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/exinfopress.png);}");
    //ContactExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
    //ContactExport->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    ContactExport->setGeometry(QRect(950,20,130,50));

    //通话记录检测
    CallhistoryCheck =new QPushButton(CallhistoryWidget);
    CallhistoryCheck->setFixedSize(120,50);
    CallhistoryCheck->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/checkmoinit.png);}"
                                    "QPushButton:hover{border-image: url(:/skin/sourceskin/checkmohover.png);}"
                                    "QPushButton:pressed{border-image: url(:/skin/sourceskin/checkmopress.png);}");


    //CallhistoryCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
    CallhistoryCheck->setGeometry(QRect(800,20,100,50));


    CallhistoryExport = new QPushButton(CallhistoryWidget);
    //CallhistoryExport->setText(QStringLiteral("导出报表"));
    CallhistoryExport->setFixedSize(120,50);
    CallhistoryExport->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/exinfoinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/exinfohover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/exinfopress.png);}");
    //CallhistoryExport->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    CallhistoryExport->setGeometry(QRect(950,20,130,50));

    //短信记录检测
    MessagesCheck =new  QPushButton(MessageWidget);
    //MessagesCheck->setText(QStringLiteral("检测"));
    MessagesCheck->setFixedSize(120,50);

    MessagesCheck->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/checkmoinit.png);}"
                                 "QPushButton:hover{border-image: url(:/skin/sourceskin/checkmohover.png);}"
                                 "QPushButton:pressed{border-image: url(:/skin/sourceskin/checkmopress.png);}");

    MessagesCheck->setGeometry(QRect(800,20,100,50));



    MessagesExport = new QPushButton(MessageWidget);
    //MessagesExport->setText( QStringLiteral("导出报表")),
    MessagesExport->setFixedSize(120,50);
    MessagesExport->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/exinfoinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/exinfohover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/exinfopress.png);}");

   //MessagesExport->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    MessagesExport->setGeometry(QRect(950,20,120,50));

    //文件信息检测
    FileCheck =new  QPushButton(FileWidget);
    //FileCheck->setText(QStringLiteral("检测"));
    FileCheck->setFixedSize(120,50);
    FileCheck->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/checkmoinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/checkmohover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/checkmopress.png);}");
    FileCheck->setGeometry(QRect(800,20,110,50));

    FileExport = new QPushButton(FileWidget);
    //FileExport->setText(QStringLiteral("导出报表"));
    FileExport->setFixedSize(120,50);
    FileExport->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/exinfoinit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/exinfohover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/exinfopress.png);}");

    //FileExport->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    FileExport->setGeometry(QRect(950,20,120,50));


    //状态显示按钮
    contanctState =new QLabel(ContactsWidget);
    contanctState->setText(QStringLiteral("未 进 行 通 讯 录 检 测，请 开 始 检 测！"));
    contanctState->setFixedSize(600,50);
    contanctState->setStyleSheet("color:rgb(68,68,68);font:16pt,Microsoft YaHei;");
    contanctState->setGeometry(QRect(20,20,800,50));

    CallhistState =new QLabel(CallhistoryWidget);
    CallhistState->setText(QStringLiteral("未 进 行 通 话 记 录 检 测，请 开 始 检 测！"));
    CallhistState->setFixedSize(600,50);
    CallhistState->setStyleSheet("color:rgb(68,68,68);font:16pt,Microsoft YaHei");
    CallhistState->setGeometry(QRect(20,20,800,50));


    MessageState =new  QLabel(MessageWidget);
    MessageState->setText(QStringLiteral("未 进 行 短 信 检 测，请 开 始 检 测！"));
    MessageState->setFixedSize(600,50);
    MessageState->setStyleSheet("color:rgb(68,68,68);font:16pt,Microsoft YaHei");
    MessageState->setGeometry(QRect(20,20,800,50));


    FileState =new  QLabel(FileWidget);
    FileState->setText(QStringLiteral("未 进 行 手  机 文 件 检 测，请 开 始 检 测！"));
    FileState->setFixedSize(600,50);
    FileState->setStyleSheet("color:rgb(68,68,68);font:16pt,Microsoft YaHei");
    FileState->setGeometry(QRect(20,20,800,50));

    PhoneInfoTableWidget();

    MessagFirstPage =new QPushButton( MessageWidget);
    MessagFirstPage->setFixedSize(55,30);
    MessagFirstPage->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/firstinit.png);}"
                                   "QPushButton:hover{border-image: url(:/image/sourceskin/firsthover.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/sourceskin/firstpress.png);}");

//    setStyleSheet("color:rgb(68,68,68);font:16pt,黑体;");
//    MessagFirstPage->setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127)}"
//              "QPushButton:pressed{background-color: rgb(255, 0, 0);};color:rgb(68,68,68);font:18pt,黑体;");
//    MessagFirstPage->setStyleSheet("background-color:rgb(85,170,127);font:10pt,黑体;");
    MessagFirstPage->setGeometry(QRect(322,555,600,50));

    MessagefrontPage =new QPushButton(MessageWidget);
    MessagefrontPage->setFixedSize(55,30);
    MessagefrontPage->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/preinit.png);}"
                                    "QPushButton:hover{border-image: url(:/image/sourceskin/prehover.png);}"
                                    "QPushButton:pressed{border-image: url(:/image/sourceskin/prepress.png);}");

            //setStyleSheet("background-color:rgb(85,170,127);font:10pt,黑体;");
    MessagefrontPage->setGeometry(QRect(382,555,600,50));

    MessageEdit = new QLineEdit(MessageWidget);
    MessageEdit->setFixedSize(55,30);
    MessageEdit->setText(QString::number(pageIndex));
    MessageEdit->setStyleSheet("font:10pt,黑体;");
    //background:lightgray;
    MessageEdit->setGeometry(QRect(442,555,600,50));

    MessagePageCount = new QLabel(QStringLiteral("  / 0"),MessageWidget);
    MessagePageCount->setFixedSize(55,30);
    MessagePageCount->setStyleSheet("font:10pt,黑体;");
    //background:lightgray;
    //Messagefron->setStyleSheet("background-color:rgb(85,170,127);font:10pt,黑体;");
    MessagePageCount->setGeometry(QRect(502,555,600,50));

    MessageOk = new QPushButton(MessageWidget);
    MessageOk->setFixedSize(55,30);
    MessageOk->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/goinit.png);}"
                             "QPushButton:hover{border-image: url(:/image/sourceskin/gohover.png);}"
                             "QPushButton:pressed{border-image: url(:/image/sourceskin/gopress.png);}");
            //setStyleSheet("background-color:rgb(85,170,127);font:10pt,黑体;");
    MessageOk->setGeometry(QRect(562,555,600,50));

    MessageNextPage =new  QPushButton(MessageWidget);
    MessageNextPage->setFixedSize(55,30);
    MessageNextPage->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/nextinit.png);}"
                                   "QPushButton:hover{border-image: url(:/image/sourceskin/nexthover.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/sourceskin/nextpress.png);}");
            //setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127)}"
                                  //"QPushButton:pressed{background-color: rgb(255, 0, 0);};color:rgb(68,68,68);font:18pt,黑体;");
    //MessageNextPage->setStyleSheet("background-color:rgb(85,170,127);font:10pt,黑体;");
    MessageNextPage->setGeometry(QRect(622,555,600,50));

    MessageLastPage =new QPushButton(MessageWidget);
    MessageLastPage->setFixedSize(55,30);
    MessageLastPage->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/lastinit.png);}"
                                   "QPushButton:hover{border-image: url(:/image/sourceskin/lasthover.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/sourceskin/lastpress.png);}");
            //setStyleSheet("background-color:rgb(85,170,127);font:10pt,黑体;");
    MessageLastPage->setGeometry(QRect(682,555,600,50));


    connect(Contactsbutton,SIGNAL(clicked()),this,SLOT(slotContactsbutton()));
    connect(Callhistorybutton,SIGNAL(clicked()),this,SLOT(slotCallhistorybutton()));
    connect(Messagesbutton,SIGNAL(clicked()),this,SLOT(slotMessagesbutton()));
    connect(Filebutton,SIGNAL(clicked()),this,SLOT(slotFilebutton()));

    connect(ContactCheck,SIGNAL(clicked()),this,SLOT(slotContactsclick()));
    connect(ContactExport,SIGNAL(clicked()),this,SLOT(slotContactExport()));

    connect(CallhistoryCheck,SIGNAL(clicked()),this,SLOT(slotCallhistoryclick()));
    connect(CallhistoryExport,SIGNAL(clicked()),this,SLOT(slotCallhistoryExport()));


    connect(MessagesCheck,SIGNAL(clicked()),this,SLOT(slotMessagesclick()));
    connect(MessagesExport,SIGNAL(clicked()),this,SLOT(slotMessageExport()));
    connect(MessageNextPage,SIGNAL(clicked()),this,SLOT(slotMessageNextPage()));
    connect(MessagefrontPage,SIGNAL(clicked()),this,SLOT(slotFrontPage()));
    connect(MessagFirstPage,SIGNAL(clicked()),this,SLOT(slotMessageFirstPage()));
    connect(MessageLastPage,SIGNAL(clicked()),this,SLOT(slotMessageLatPage()));
    connect(MessageOk,SIGNAL(clicked()),this,SLOT(slotMessageCurrentOk()));

    connect(FileCheck,SIGNAL(clicked()),this,SLOT(slotFileclick()));
    connect(FileExport,SIGNAL(clicked()),this,SLOT(slotFileExport()));

}
void downwidget::PhoneInfoTableWidget()
{
    //通讯录数据
    ContactTable = new QTableWidget(this->ContactsWidget);
    //ContactTable->setFixedSize(990,510);
    ContactTable->setFixedSize(1060,515);
    ContactTable->setGeometry(QRect(20,80,120,510));

    ContactTable->setAlternatingRowColors(true);
    ContactTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    //ContactTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    ContactTable->setStyleSheet("color:rgb(68,68,68);font:13pt,Microsoft YaHei");

    //获取滑动条
    QScrollBar *Resulbar = ContactTable->verticalScrollBar();
    Resulbar->setStyleSheet("QScrollBar{background:lightgray;}");


    //ContactTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ContactTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

    int i = 0;
    QStringList header;
    header<<QStringLiteral("序号")<<QStringLiteral("联系人")<<QStringLiteral("联系方式");

    ContactTable->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

    QFont font = ContactTable->horizontalHeader()->font();
    font.setBold(true);
    ContactTable->horizontalHeader()->setFixedHeight(50);

    ContactTable->setColumnCount(3);
    ContactTable->setHorizontalHeaderLabels(header);

    ContactTable->setRowHeight(i,250);
    ContactTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ContactTable->setColumnWidth(0,70);
    ContactTable->setColumnWidth(1,400);
    ContactTable->setColumnWidth(2,590);
    //ContactTable->setColumnWidth(3,250);

    //ContactTable->setShowGrid(false); //设置不显示格子线

    QHeaderView *columnhead = ContactTable->verticalHeader();
    columnhead->setFixedWidth(40);

    QHeaderView *columnhead11 = ContactTable->verticalHeader();
    columnhead11->setVisible(false);

    ContactTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行

    //表头居左
    //ContactTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    //表头样式表
    ContactTable->horizontalHeader()->setEnabled(false);

    QFont font3 =ContactTable->horizontalHeader()->font();    //设置表头字体加粗
    font3.setBold(true);

    ContactTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    int nRow = ContactTable->rowCount();

    qDebug()<<nRow<<"All Count";
    for(i = 0 ; i < nRow; i++)
    {
       for(int j=0;j<3;j++)
       {
          //safeResultTable->setItem(i,j,new QTableWidgetItem(QString::number((i+1)*(j+1))));
          ContactTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
    }

    //通话记录检测结果
    CallhistoryTable = new QTableWidget(CallhistoryWidget);
    //CallhistoryTable->setFixedSize(990,510);
    CallhistoryTable->setFixedSize(1060,515);
    CallhistoryTable->setGeometry(QRect(20,80,120,520));

    CallhistoryTable->setAlternatingRowColors(true);
    CallhistoryTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    CallhistoryTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    CallhistoryTable->setStyleSheet("color:rgb(68,68,68);font:13pt,Microsoft YaHei");

    QScrollBar *Resulbar1 = CallhistoryTable->verticalScrollBar();
    Resulbar1->setStyleSheet("QScrollBar{background:lightgray;}");

    QHeaderView *columnhead12 = CallhistoryTable->verticalHeader();
    columnhead12->setVisible(false);


    //CallhistoryTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    CallhistoryTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

    int i1 = 0;
    QStringList header1;
    header1<<QStringLiteral("序号")<<QStringLiteral("通话号码")<<QStringLiteral("通话时长(s)")<<QStringLiteral("通话状态")<<QStringLiteral("日期");

    CallhistoryTable->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

    QFont font1 = CallhistoryTable->horizontalHeader()->font();
    font1.setBold(true);
    CallhistoryTable->horizontalHeader()->setFixedHeight(50);

    CallhistoryTable->setColumnCount(5);
    CallhistoryTable->setHorizontalHeaderLabels(header1);

    CallhistoryTable->setRowHeight(i,300);
    CallhistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    CallhistoryTable->setColumnWidth(0,70);
    CallhistoryTable->setColumnWidth(1,270);
    CallhistoryTable->setColumnWidth(2,220);
    CallhistoryTable->setColumnWidth(3,255);
    CallhistoryTable->setColumnWidth(4,250);

    //ContactTable->setShowGrid(false); //设置不显示格子线

    QHeaderView *columnhead1 = CallhistoryTable->verticalHeader();
    columnhead1->setFixedWidth(50);

    CallhistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行

    //表头居左
    //ContactTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    //表头样式表
    CallhistoryTable->horizontalHeader()->setEnabled(false);

    QFont font36 =CallhistoryTable->horizontalHeader()->font();    //设置表头字体加粗
    font36.setBold(true);

    CallhistoryTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    int nRow1 = CallhistoryTable->rowCount();

    qDebug()<<nRow<<"All Count";
    for(i1 = 0 ; i1 < nRow1; i1++)
    {
       for(int j=0;j<5;j++)
       {
          //safeResultTable->setItem(i,j,new QTableWidgetItem(QString::number((i+1)*(j+1))));
          CallhistoryTable->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
    }

    //短信数据表格
    MessagesTable = new QTableWidget(MessageWidget);
    //MessagesTable->setFixedSize(990,450);
    MessagesTable->setFixedSize(1060,450);
    MessagesTable->setGeometry(QRect(20,80,120,520));

    MessagesTable ->setAlternatingRowColors(true);
    MessagesTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    MessagesTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    MessagesTable->setStyleSheet("color:rgb(68,68,68);font:13pt,Microsoft YaHei");

//    QScrollBar *Resulbar2 = MessagesTable->verticalScrollBar();
//    Resulbar2->setStyleSheet("QScrollBar{background:lightgray;}");


    MessagesTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    MessagesTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    MessagesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    MessagesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

    int i2 = 0;
    QStringList header2;
    header2<<QStringLiteral("序号")<<QStringLiteral("接收号码")<<QStringLiteral("短信详细")<<QStringLiteral("发送状态")<<QStringLiteral("日期");

    MessagesTable->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

    QFont font2 = MessagesTable->horizontalHeader()->font();
    font2.setBold(true);
    MessagesTable->horizontalHeader()->setFixedHeight(50);

    MessagesTable->setColumnCount(5);
    MessagesTable->setHorizontalHeaderLabels(header2);

    MessagesTable->setRowHeight(i,300);
    MessagesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MessagesTable->setColumnWidth(0,70);
    MessagesTable->setColumnWidth(1,320);
    MessagesTable->setColumnWidth(2,100);
    MessagesTable->setColumnWidth(3,230);
    MessagesTable->setColumnWidth(4,340);

    //ContactTable->setShowGrid(false); //设置不显示格子线

    QHeaderView *columnhead2 = MessagesTable->verticalHeader();
    columnhead2->setFixedWidth(50);


    QHeaderView *columnhead13 = MessagesTable->verticalHeader();
    columnhead13->setVisible(false);

    //MessagesTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行

    //表头居左
    //ContactTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    //表头样式表
    MessagesTable->horizontalHeader()->setEnabled(false);

    QFont font34 =MessagesTable->horizontalHeader()->font();    //设置表头字体加粗
    font34.setBold(true);

    MessagesTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    int nRow2 = MessagesTable->rowCount();

    qDebug()<<nRow<<"All Count";
    for(i2 = 0 ; i1 < nRow2; i1++)
    {
       for(int j=0;j<5;j++)
       {
          //safeResultTable->setItem(i,j,new QTableWidgetItem(QString::number((i+1)*(j+1))));
          MessagesTable->item(i2,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
    }

//    QHeaderView *columnhead22 = MessagesTable->verticalHeader();
//    columnhead22->setVisible(false);

    //文件信息数据表格
    FileTable = new QTableWidget(FileWidget);
    //FileTable->setFixedSize(990,510);
    FileTable->setFixedSize(1060,515);
    FileTable->setGeometry(QRect(20,80,120,520));

    FileTable->setAlternatingRowColors(true);
    FileTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    FileTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    FileTable->setStyleSheet("color:rgb(68,68,68);font:13pt,Microsoft YaHei");

    QScrollBar *Resulbar3 = FileTable ->verticalScrollBar();
    Resulbar3->setStyleSheet("QScrollBar{background:lightgray;}");


    FileTable ->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    FileTable ->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框

    int i3 = 0;
    QStringList header3;
    header3<<QStringLiteral("文件名")<<QStringLiteral("文件路径");

    FileTable ->horizontalHeader()->setStyleSheet("QHeaderView::section{font:20pt}");

    QFont font38 = FileTable->horizontalHeader()->font();
    font38.setBold(true);
    FileTable ->horizontalHeader()->setFixedHeight(50);

    FileTable ->setColumnCount(2);
    FileTable ->setHorizontalHeaderLabels(header3);

    FileTable->setRowHeight(i,300);
    FileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    FileTable->setColumnWidth(0,330);
    FileTable->setColumnWidth(1,730);
//  FileTable->setColumnWidth(2,235);
//  FileTable->setColumnWidth(3,235);

    //ContactTable->setShowGrid(false); //设置不显示格子线

    QHeaderView *columnhead3 = FileTable->verticalHeader();
    columnhead3->setVisible(false);

    FileTable ->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行

    //表头居左
    //ContactTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    //表头样式表
    FileTable->horizontalHeader()->setEnabled(false);

    QFont font33 =FileTable->horizontalHeader()->font();    //设置表头字体加粗
    font33.setBold(true);

    FileTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    int nRow3 = FileTable ->rowCount();

    qDebug()<<nRow<<"All Count";
    for(i3 = 0 ; i1 < nRow3; i1++)
    {
       for(int j=0;j<3;j++)
       {
          //safeResultTable->setItem(i,j,new QTableWidgetItem(QString::number((i+1)*(j+1))));
          FileTable->item(i3,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       }
    }
}


//通讯录信息解析和获取
void downwidget::slotContactsclick()
{

    contanctState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg";
    ContactCheck->setEnabled(false);

    //AppList::ContactsInfo[1000].clear();

    for(int i  = 0; i < downwidget::contactInfoi; i++)
    {
        AppList::ContactsInfo[i].clear();
    }
    downwidget::contactInfoi = 0;

    int  contanctRow =  ContactTable->rowCount();
    for(int i= 0; i <contanctRow ; i++)
    {
        ContactTable->removeRow(0);
    }

//    m_adb->ApplyServ();
//    if(m_socket->linkServer())
//    {
//        qDebug()<<"Link Server";
        QString msg;
        msg.append(MSG_USER_OPERATE_Contact).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL);
        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_Contact,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";

//    }else
//    {
//        qDebug()<<"Server Conn Filed";
//    }

}

void downwidget::slotContactExport()
{

    if(AppList::ContactsInfo[0].isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("请先通讯录检测再导出！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

//        QString safeResultInfo = QStringLiteral("请先安全检测再导出！！！");
//        QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                                     safeResultInfo, QStringLiteral("确定"));
        return;
    }

//    ContactExport->setStyleSheet("background-image:url(:/source/icon1/MessageExDo.png);background-color:transparent;");
//    CallhistoryExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    MessagesExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    FileExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");

    qDebug()<<"rrrr";
    m_contactMsgbox = new MsgBox;
    m_contactMsgbox->setExport(QStringLiteral("通讯录检测报表"));

    m_contactMsgbox->anmeEdit->setText(downwidget::unit);
    m_contactMsgbox->unitEdit->setText(downwidget::name);
    m_contactMsgbox->phoneEdit->setText(downwidget::phone);
    m_contactMsgbox->remarkEdit->setText(downwidget::detail);
    m_contactMsgbox->show();

    //QWord::showSafewordinfo("unit","name","phone","detail");

    connect(m_contactMsgbox->exportbutton,SIGNAL(clicked()),this,SLOT(slotContaReport()));

}

void downwidget::slotContaReport()
{


    downwidget::unit = m_contactMsgbox->anmeEdit->text();
    downwidget::name = m_contactMsgbox->unitEdit->text();
    downwidget::phone = m_contactMsgbox->phoneEdit->text();
    downwidget::detail = m_contactMsgbox->remarkEdit->text();

    m_contactMsgbox->close();

    qDebug()<<name<<unit<<"dfbhtrfghtfrdbhgtfc";

    m_contactWord =new QWord;

    contanctState->setText(QStringLiteral("通 讯 录 正 在 导 出 中，请 稍 后....."));

    bool OK = m_safeResultWord->showContanctInfo(downwidget::contactInfoi,unit,name,phone,detail);

    if(true == OK)
    {
        contanctState->setText(QStringLiteral("通 讯 录  已 经 导 出，请 查 阅！！！"));

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

//        if (QMessageBox::question(NULL,QStringLiteral("完成"),QStringLiteral("文件已经导出，是否现在打开？"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
//        {

//            qDebug()<<"jyyj"<<AppList::currentExportDir;
//            //AppList::currentExportDir = QStringLiteral("E:\\MobileCheck\\Export\\通讯录检测记录20170112173821");
//            //AppList::currentExportDir = "E:\\MobileCheck\\Export\\123.docx";
//           // QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(AppList::currentExportDir)));
//           // QString str =  AppList::currentExportDir.append(".doc");
//            QDesktopServices::openUrl(QUrl::fromLocalFile(AppList::currentExportDir));
//        }else
//        {
//            //QMessageBox::question(NULL,QStringLiteral("完成"),QStringLiteral("文件已经导出，是否现在打开？"),QMessageBox::Yes|QMessageBox::No).close();
//        }

    }else if(false == OK)
    {
        contanctState->setText(QStringLiteral("检 测 已 经 完 成，请 导 出 报 表！！！"));
    }
}

void downwidget::slotContactJoson(QJsonObject object)
{

    qDebug()<<"8889999";
    parseContactInfo(object);

}

void downwidget::parseContactInfo(QJsonObject object)
{
      qDebug()<<"parse........";

      QString contactdatail;

      QJsonValue ret_vaue = object.take("ret");
      QJsonValue opetype_value = object.take("opType");
      QString ret = ret_vaue.toString();
      QString opetype = opetype_value.toString();
      qDebug()<<ret<<opetype<<"result";

      if(ret == "200")
      {

          QJsonArray contact= object.take("contact").toArray();

          int tag = contact.at(0).toInt();
          qDebug() << "tag:" << tag;

          for(int i = 0; i < contact.size(); i++)
          {

             QJsonObject json = contact.at(i).toObject();

             //QJsonObject contact  = object.take("contact").toObject();

             QJsonValue phoneNum = json.take("phoneNum");
             QString phonenum = phoneNum.toString();

             QJsonValue contactName = json.take("contactName");
             QString contactname = contactName.toString();

             QJsonValue contactId = json.take("contactId");
             QString contactid = contactId.toString();

             QString pnumber1 = m_socket->m_parsejson->RightInfoTransCode(phonenum);

             QString pnumber = pnumber1.left(pnumber1.length()-1);

             //qDebug()<<pum<<contact<<"conatct;;;;;";

             QString contact = m_socket->m_parsejson->RightInfoTransCode(contactname);
             QString contaId = m_socket->m_parsejson->RightInfoTransCode(contactid);

             qDebug()<<"IphonContact: "<<pnumber<<contact <<contaId<<"+++++++++";

             ContactTable->insertRow(downwidget::contactInfoi);

             ContactTable->setItem(downwidget::contactInfoi,0,new QTableWidgetItem(QString::number(downwidget::contactInfoi+1)));
             ContactTable->setItem(downwidget::contactInfoi,1,new QTableWidgetItem(contact));
             ContactTable->setItem(downwidget::contactInfoi,2,new QTableWidgetItem(pnumber));
             //ContactTable->setItem(downwidget::contactInfoi,3,new QTableWidgetItem(contaId));

             int nRow = ContactTable->rowCount();
             qDebug()<<nRow<<"All Count";
             for(int i = 0 ; i < nRow; i++)
             {
                for(int j=0;j<3;j++)
                {

                   ContactTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                }
             }

             contanctState->setText(QStringLiteral("检 测 已 经 完 成，请 查 看 检 测 结 果 ！"));

             contactdatail = pnumber.append(MSG_DATA_ITEMS_SEPARATOR).append(contact);

                     //append(MSG_DATA_ITEMS_SEPARATOR).append(contaId);

             AppList::ContactsInfo[downwidget::contactInfoi] = contactdatail;
             downwidget::contactInfoi++;

           }

           //ContactCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");

           ContactCheck->setEnabled(true);
           return;
      }else if(ret == "210")
      {
          contanctState->setText(QStringLiteral("检 测 已 经 完 成，未 检 测 到 通 讯 录 ！"));
          //ContactCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
          ContactCheck->setEnabled(true);
          return;
      }else
      {
          qDebug()<<"parseContactJson Error";
          ContactCheck->setEnabled(true);
          return;
      }

}

void downwidget::slotCallhistoryJson(QJsonObject object)
{
    qDebug()<<"start parseRecondJson";

    QString callhistorydatail;
    QDate date;
    QTime time;
    QString str1;
    QString str2;
    QString datestr;
    QString action;

    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();
    qDebug()<<ret<<opetype<<"result";

    if(ret == "200")
    {
        QJsonArray  CallHistoryArray= object.take("callHistory").toArray();

        int tag = CallHistoryArray.at(0).toInt();
        qDebug() << "tag:" << tag;
        for(int i = 0; i < CallHistoryArray.size(); i++)
        {
                QJsonObject json = CallHistoryArray.at(i).toObject();
                QString destNum1 =  json.value("desNum").toString();
                QString duration1 = json.value("duration").toString();
                QString action1 = json.value("action").toString();
                QString date1 = json.value("date").toString();


                QString destNum = m_socket->m_parsejson->RightInfoTransCode(destNum1);
                QString duration = m_socket->m_parsejson->RightInfoTransCode(duration1);
                action= m_socket->m_parsejson->RightInfoTransCode(action1);
                QString date2 = m_socket->m_parsejson->RightInfoTransCode(date1);

                if(action == "1")
                {
                     action = QStringLiteral("已拨通");
                }else
                {
                     action = QStringLiteral("未拨通");
                }

                qDebug()<<"RecordInfo: "<<destNum <<duration <<action <<date2<<"++++++=====";

                CallhistoryTable->insertRow(downwidget::Callhistoryi);

                CallhistoryTable->setItem(downwidget::Callhistoryi,0,new QTableWidgetItem(QString::number(downwidget::Callhistoryi+1)));
                CallhistoryTable->setItem(downwidget::Callhistoryi,1,new QTableWidgetItem(destNum));
                CallhistoryTable->setItem(downwidget::Callhistoryi,2,new QTableWidgetItem(duration));
                CallhistoryTable->setItem(downwidget::Callhistoryi,3,new QTableWidgetItem(action));
                CallhistoryTable->setItem(downwidget::Callhistoryi,4,new QTableWidgetItem(date2));

                int nRow = CallhistoryTable->rowCount();
                qDebug()<<nRow<<"All Count";
                for(int i = 0 ; i < nRow; i++)
                {
                   for(int j=0;j<5;j++)
                   {

                      CallhistoryTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                   }
                }

                CallhistState->setText(QStringLiteral("检 测 已 经 完 成，请 查 看 检 测 结 果 ！"));

                callhistorydatail = destNum.append(MSG_DATA_ITEMS_SEPARATOR).append(duration).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(action).append(MSG_DATA_ITEMS_SEPARATOR).
                                append(date2);

                qDebug()<<callhistorydatail<<"kkkkllll";
                AppList::CallhistoryInfo[downwidget::Callhistoryi] = callhistorydatail;
                downwidget::Callhistoryi++;
        }

       //CallhistoryCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
       CallhistoryCheck->setEnabled(true);
       return ;
    }else if(ret == "210")
    {
        CallhistState->setText(QStringLiteral("检 测 已 经 完 成，未 检 测 到 通 话 记 录 ！"));
        //CallhistoryCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
        CallhistoryCheck->setEnabled(true);
        return;
    }
    else
    {
        qDebug()<<"parseRecordJson Error";
        CallhistoryCheck->setEnabled(true);
        return;
    }


}

void  downwidget::slotCallhistoryExport()
{

//    ContactExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    CallhistoryExport->setStyleSheet("background-image:url(:/source/icon1/MessageExDo.png);background-color:transparent;");
//    MessagesExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    FileExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");

    if(AppList::CallhistoryInfo[0].isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("请检测通话记录，再导出！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();
        return;
    }

    qDebug()<<"callhistory";
    m_callhistoryMsgbox = new MsgBox;
    m_callhistoryMsgbox->setExport(QStringLiteral("通话记录报表"));

    m_callhistoryMsgbox->anmeEdit->setText(downwidget::unit);
    m_callhistoryMsgbox->unitEdit->setText(downwidget::name);
    m_callhistoryMsgbox->phoneEdit->setText(downwidget::phone);
    m_callhistoryMsgbox->remarkEdit->setText(downwidget::detail);
    m_callhistoryMsgbox->show();

    connect(m_callhistoryMsgbox->exportbutton,SIGNAL(clicked()),this,SLOT(slotCallhistoryReport()));


}

void downwidget::slotCallhistoryReport()
{
    downwidget::unit = m_callhistoryMsgbox->anmeEdit->text();
    downwidget::name = m_callhistoryMsgbox->unitEdit->text();
    downwidget::phone = m_callhistoryMsgbox->phoneEdit->text();
    downwidget::detail = m_callhistoryMsgbox->remarkEdit->text();

    m_callhistoryMsgbox->close();

    qDebug()<<name<<unit<<"dfbhtrfghtfrdbhgtfc";

    m_callhisWord=new QWord;

    CallhistState->setText(QStringLiteral("通 话 记 录 正 在 导 出 中，请 稍 后..."));

    bool OK = m_callhisWord->showCallhistoryInfo(downwidget::Callhistoryi,unit,name,phone,detail);

    if(true == OK)
    {
        CallhistState->setText(QStringLiteral("通 话 记 录 已 经 导 出，请 查 阅！！！"));

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

    }else if(false == OK)
    {
        CallhistState->setText(QStringLiteral("检 测 已 经 完 成，请 导 出 报 表！！！"));
    }

}


//通话记录检测
void downwidget::slotCallhistoryclick()
{
//    MessagesCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    ContactCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    CallhistoryCheck->setStyleSheet("background-image:url(:/source/icon1/MessCheckDo.png);background-color:transparent;");
//    FileCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
    CallhistState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg";    
    CallhistoryCheck->setEnabled(false);
    AppList::CallhistoryInfo[1000].clear();
    downwidget::Callhistoryi = 0;

    for(int i  = 0; i < downwidget::Callhistoryi; i++)
    {
        AppList::ContactsInfo[i].clear();
    }
    downwidget::Callhistoryi = 0;

    int  contanctRow =  CallhistoryTable->rowCount();
    for(int i= 0; i <contanctRow ; i++)
    {
        CallhistoryTable->removeRow(0);
    }

    m_adb->ApplyServ();
    if(m_socket->linkServer())
    {
        qDebug()<<"Link Server";
        QString msg;
        msg.append(MSG_USER_OPERATE_Records).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL);
        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_Records,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";

    }else
    {
        qDebug()<<"Server Conn Filed";
    }

}


//短信记录检测
void downwidget::slotMessagesclick()
{

//    MessagesCheck->setStyleSheet("background-image:url(:/source/icon1/MessCheckDo.png);background-color:transparent;");
//    ContactCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    CallhistoryCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    FileCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");

    MessageState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg"; 
    MessagesCheck->setEnabled(false);
    for(int i  = 0; i < downwidget::Messagei; i++)
    {
        AppList::MessageInfo[i].clear();
    }
    downwidget::contactInfoi = 0;

    int  contanctRow =  MessagesTable->rowCount();
    for(int i= 0; i <contanctRow ; i++)
    {
        MessagesTable->removeRow(0);
    }
    downwidget::Messagecount = 0;
    downwidget::Messagei = 0;
    int pageIndex = 1;

    m_adb->ApplyServ();
    if(m_socket->linkServer())
    {
        qDebug()<<"Link Server";
        QString msg;
        msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
            append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(pageIndex));
        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";

    }else
    {
        qDebug()<<"Server Conn Filed";
    }

}

void downwidget::slotFileclick()
{

//    MessagesCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    ContactCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    CallhistoryCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
//    FileCheck->setStyleSheet("background-image:url(:/source/icon1/MessCheckDo.png);background-color:transparent;");

    FileState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg";
    FileCheck->setEnabled(false);

    for(int i  = 0; i < downwidget::Filei; i++)
    {
        AppList::FileInfo[i].clear();
    }
    downwidget::Filei = 0;

    int  contanctRow =  FileTable->rowCount();
    for(int i= 0; i <contanctRow ; i++)
    {
        FileTable->removeRow(0);
    }

    if(m_socket->linkServer())
    {
        qDebug()<<"Link Server";
        QString msg;
        msg.append(MSG_USER_OPERATE_SD_Document).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_SELECT_ALL).append(MSG_DATA_ITEMS_SEPARATOR).append("/sdcard");
        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_SD_Document,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";

    }else
    {
        qDebug()<<"Server Conn Filed";
    }


}

//短信记录
void downwidget::slotMessageJson(QJsonObject object)
{

    qDebug()<<"start praseMessageJsonss";
    QString messageDatail;

    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();
    QString countstr = object.take("count").toString();
    QString pageIndexstr = object.take("pageIndex").toString();

    count = countstr.toInt();
    pageIndex = pageIndexstr.toInt();

    //downwidget::Messagei = (pageIndex - 1)*10 ;

    qDebug()<<count<<pageIndex<<"hhhhhhwgwr";

    int remainder = count%10;
    Messagecount = (count - remainder)/10;
    if(remainder != 0)
    {
        Messagecount = Messagecount+1;
    }

    QString str = "  /";
    QString text = str.append(QString::number(Messagecount));
    MessagePageCount->setText(text);
    MessageEdit->setText(QString::number(pageIndex));
    qDebug()<<count<<Messagecount <<"hhhhhhwgwr";
    qDebug()<<ret<<opetype<<"result";

//    bool OK = SetMessageCurrentIndex(object,ret,pageIndex);

//    if(OK  == true)
//    {
//        return;
//    }

    if(ret == "200")
    {
        QJsonArray message= object.take("message").toArray();

        int tag = message.count();
        qDebug() << "tag:" << tag;
        for(int i = 0; i < message.size(); i++)
        {

           qDebug()<<"jtyrjhr";
           QJsonObject json = message.at(i).toObject();
           QString destnum = json.take("desNum").toString();
           QString content = json.take("content").toString();
           QString action = json.take("action").toString();
           QString date = json.take("date").toString();


           QString DestNum = m_socket->m_parsejson->RightInfoTransCode(destnum);
           QString Content = m_socket->m_parsejson->RightInfoTransCode(content);
           QString Action= m_socket->m_parsejson->RightInfoTransCode(action);
           QString Date = m_socket->m_parsejson->RightInfoTransCode(date);

           qDebug()<<"IphonContact:"<<DestNum<<Content<<Action<<Date<<"=--------";


           MessageDetailbutton[downwidget::Messagei] = new QPushButton();
           MessageDetailbutton[downwidget::Messagei]->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/shortmsginit.png);}"
                                                           "QPushButton:hover{border-image: url(:/image/sourceskin/shortmsghover.png);}"
                                                           "QPushButton:pressed{border-image: url(:/image/sourceskin/shortmsgpress.png);}");
           MessageDetailbutton[downwidget::Messagei]->setFixedSize(99,39);

           MessagesTable->insertRow(downwidget::Messagei);

           MessagesTable->setItem(downwidget::Messagei,0,new QTableWidgetItem(QString::number(downwidget::Messagei+1)));
           MessagesTable->setItem(downwidget::Messagei,1,new QTableWidgetItem(DestNum));


           MessagesTable->setCellWidget(downwidget::Messagei,2,MessageDetailbutton[downwidget::Messagei]);
           MessagesTable->setItem(downwidget::Messagei, 2, new QTableWidgetItem(QStringLiteral("")));
           connect(MessageDetailbutton[downwidget::Messagei],SIGNAL(clicked()),this,SLOT(slotMessageDetail()));

           MessagesTable->setItem(downwidget::Messagei,3,new QTableWidgetItem(Action));
           MessagesTable->setItem(downwidget::Messagei,4,new QTableWidgetItem(Date));

           int nRow = MessagesTable->rowCount();

           qDebug()<<nRow<<"All Count";
           for(int i =0; i<nRow; i++)
           {
               MessagesTable->setRowHeight(i,40);
           }
           for(int i = 0 ; i < nRow; i++)
           {
              for(int j=0;j<5;j++)
              {

                 MessagesTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

              }
           }

           messageDatail = DestNum.append(MSG_DATA_ITEMS_SEPARATOR).append(Content).
                           append(MSG_DATA_ITEMS_SEPARATOR).append(Action).append(MSG_DATA_ITEMS_SEPARATOR).
                           append(Date);

           AppList::MessageInfo[downwidget::Messagei] = messageDatail;
           downwidget::Messagei++;
        }
        MessageState->setText(QStringLiteral("检 测 已 经 完 成，请 查 看 检 测 结 果 ！"));
        //MessagesCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
        downwidget::Messagei = 0;
        MessagesCheck->setEnabled(true);
        MessageOk->setEnabled(true);
        MessageNextPage->setEnabled(true);
        MessagefrontPage->setEnabled(true);
        MessagFirstPage->setEnabled(true);
        MessageLastPage->setEnabled(true);
        return;
    }else if(ret == "210")
    {
        MessageState->setText(QStringLiteral("检 测 已 经 完 成，未 检 测 到 短 信 记 录 ！"));
        //MessagesCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
        MessagesCheck->setEnabled(true);
        MessageOk->setEnabled(true);
        MessageNextPage->setEnabled(true);
        MessagefrontPage->setEnabled(true);
        MessagFirstPage->setEnabled(true);
        MessageLastPage->setEnabled(true);
        return;
    }
    else
    {
        qDebug()<<"parseMessageJson Error";
        MessagesCheck->setEnabled(true);
        MessageOk->setEnabled(true);
        MessageNextPage->setEnabled(true);
        MessagefrontPage->setEnabled(true);
        MessagFirstPage->setEnabled(true);
        MessagFirstPage->setEnabled(true);
        MessageLastPage->setEnabled(true);
        return;
    }

}
void downwidget::slotMessagexport(QJsonObject object)
{

    qDebug()<<"start praseMessageJsons export";
    QString messageDatail;
    QString DestNum;
    //int j = 0;

    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();
    QString countstr = object.take("count").toString();
    QString pageIndexstr = object.take("pageIndex").toString();

    int count = countstr.toInt();
    pageIndex = pageIndexstr.toInt();

    qDebug()<<opetype<<"ooiooo"<<count<<"jyjyrj";


    if(ret == "200")
    {
         QJsonArray message= object.take("message").toArray();

         int tag = message.count();
         qDebug() << "tag:" << tag;
         for(int i = 0; i < message.size(); i++)
         {

            qDebug()<<"jtyrjhr";
            QJsonObject json = message.at(i).toObject();
            QString destnum = json.take("desNum").toString();
            QString content = json.take("content").toString();
            QString action = json.take("action").toString();
            QString date = json.take("date").toString();

            qDebug()<<"IphonContact:"<<destnum<<content <<action<<date<<"+++++++++";

            QString DestNum = m_socket->m_parsejson->RightInfoTransCode(destnum);
            QString Content = m_socket->m_parsejson->RightInfoTransCode(content);
            QString Action= m_socket->m_parsejson->RightInfoTransCode(action);
            QString Date = m_socket->m_parsejson->RightInfoTransCode(date);

            qDebug()<<"IphonContact:"<<DestNum<<Content<<Action<<Date<<"=--------";

            messageDatail = DestNum.append(MSG_DATA_ITEMS_SEPARATOR).append(Content).
                            append(MSG_DATA_ITEMS_SEPARATOR).append(Action).append(MSG_DATA_ITEMS_SEPARATOR).
                            append(Date);

           qDebug()<<messageDatail<<"iiiiiiiihthttt";

           AppList::MessageExportInfo[downwidget::MessageAllRow] = messageDatail;
           downwidget::MessageAllRow++;
        }
        m_messageWord=new QWord;
        MessageState->setText(QStringLiteral("检 测 已 经 完 成,正 在 导 出 中..."));
        bool OK =  m_messageWord->showMessageInfo(count,unit,name,phone,detail);
        if(true == OK)
        {
           MessageState->setText(QStringLiteral("短 信 已 经 全 部 导 出，请 查 阅！！"));

           QMessageBox box(QMessageBox::Question,QStringLiteral("导出完成"),QStringLiteral("文件已经导出，是否现在打开？？"));
           box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
           box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
           box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
           box.setWindowIcon(QIcon("screen/open.ico"));

           if(box.exec() == QMessageBox::Ok)
           {
               QDesktopServices::openUrl(QUrl::fromLocalFile(AppList::currentExportDir));
               box.close();
               MessagesCheck->setEnabled(true);
               //MessageOk->setEnabled(true);
               return;
           }else
           {
               box.close();
               MessagesCheck->setEnabled(true);
               //MessageOk->setEnabled(true);
               return;
           }

        }else if(false == OK)
        {
           MessageState->setText(QStringLiteral("检 测 已 经 完 成，请 导 出 报 表！！！"));
           MessagesCheck->setEnabled(true);
           MessageOk->setEnabled(true);
           return;
        }

    }else if(ret == "210")
    {
        MessageState->setText(QStringLiteral("检 测 已 经 完 成，未 检 测 到 短 信 记 录 ！"));
        //MessagesCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
        MessagesCheck->setEnabled(true);
        MessageOk->setEnabled(true);
        return;
    }else
    {
        qDebug()<<"parseMessageJson Error";
        MessagesCheck->setEnabled(true);
        MessageOk->setEnabled(true);
        return;
    }

}

void downwidget::slotMessageDetail()
{

    qDebug()<<"Message 666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =MessagesTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    AppList::currentrow = index.row();
    qDebug()<<"当前row:"<<AppList::currentrow;

    QStringList AllInfo;
    QString messagedetail;

    QString msg = AppList::MessageInfo[AppList::currentrow];


    AllInfo = msg.split(MSG_DATA_ITEMS_SEPARATOR);


    qDebug()<<msg<<AllInfo.count()<<"uuuuu";

    messagedetail = AllInfo.at(1);
    QString str1 = "    ";

    QString str  = str1.append(messagedetail);

    m_MessageInfo = new MsgBox();
    m_MessageInfo->setMessageInfo(str,QString("../source/logo.ico"));
    m_MessageInfo->show();


}

//短信下一页
void downwidget::slotMessageNextPage()
{

    MessageNextPage->setEnabled(false);


    int indexstr =  MessageEdit->text().toInt();
    if(indexstr == Messagecount || indexstr > Messagecount)
    {

        MessageEdit->setText(QString::number(Messagecount));
        MessageNextPage->setEnabled(true);
        return;
    }else
    {

        MessageState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
        qDebug()<<"rgfrg";

        int Rowcount = MessagesTable->rowCount();

        for(int i= 0; i <Rowcount ; i++)
        {
            MessagesTable->removeRow(0);
        }

        indexstr = indexstr+1;
        MessageEdit->setText(QString::number(indexstr));


        m_adb->ApplyServ();

        if(m_socket->linkServer())
        {
           qDebug()<<"Link Server";
           QString msg;
           msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
               append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(indexstr));
           qDebug()<<msg<<"++++===";
           m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
           qDebug()<<"12345";

        }else
        {
                MessageState->setText(QStringLiteral("服 务 器 连 接 失 败，重新连接手机..."));

                qDebug()<<"Server Conn Filed";
                MessageNextPage->setEnabled(true);
        }
        return;

    }
}

//上一页
void downwidget::slotFrontPage()
{

    MessagefrontPage->setEnabled(false);

    int indexstr =  MessageEdit->text().toInt();
    if(indexstr == 1)
    {
        MessagefrontPage->setEnabled(true);
        return;
    }
    if(indexstr > downwidget::Messagecount)
    {
        MessageEdit->setText(QString::number(downwidget::Messagecount));
        MessagefrontPage->setEnabled(true);
        return;
    }

    int Rowcount = MessagesTable->rowCount();

    for(int i= 0; i <Rowcount ; i++)
    {
        MessagesTable->removeRow(0);
    }

    MessageState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg";

    if(indexstr > 1)
    {
      indexstr = indexstr-1;
      //checkCurrentIndex(indexstr);

      m_adb->ApplyServ();
      if(m_socket->linkServer())
      {
          qDebug()<<"Link Server";
          QString msg;
          msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
              append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(indexstr));
          qDebug()<<msg<<"++++===";
          m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
          qDebug()<<"12345";

      }else
      {
          MessageState->setText(QStringLiteral("服 务 器 连 接 失 败，重新连接手机..."));
          MessagefrontPage->setEnabled(true);
          qDebug()<<"Server Conn Filed";
      }

    }else
    {
        MessagefrontPage->setEnabled(true);
        return;
    }

}

//回到第一页
void downwidget::slotMessageFirstPage()
{

    MessagFirstPage->setEnabled(false);

    int indexstr;

    indexstr =  MessageEdit->text().toInt();
    if(indexstr == 1)
    {
        MessagFirstPage->setEnabled(true);
        return;
    }else
    {
        MessageState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
        qDebug()<<"rgfrg";

        int Rowcount = MessagesTable->rowCount();

        for(int i= 0; i <Rowcount ; i++)
        {
            MessagesTable->removeRow(0);
        }

        MessageEdit->setText(QString::number(1));
        indexstr =  MessageEdit->text().toInt();

    }


    m_adb->ApplyServ();
    if(m_socket->linkServer())
    {
          qDebug()<<"Link Server";
          QString msg;
          msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
              append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(indexstr));
          qDebug()<<msg<<"++++===";
          m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
          qDebug()<<"12345";
          return;

    }else
    {
          qDebug()<<"Server Conn Filed";

          QMessageBox box(QMessageBox::Warning,QStringLiteral("提示"),QStringLiteral("服务器异常，请重新连接..."));
          box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
          box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
          box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
          box.setWindowIcon(QIcon("screen/carful.ico"));
          box.exec();

          MessageState->setText(QStringLiteral("检 测 失 败，请 重 新 连 接 服  务 器！！！"));

          MessagFirstPage->setEnabled(true);

          return;
    }
}

void downwidget::slotMessageCurrentOk()
{

    MessageOk->setEnabled(false);

    QString indexstr = MessageEdit->text().trimmed();

    int currentIndex = indexstr.toInt();

    if(currentIndex == 0)
    {
       MessageEdit->setText(QString::number(1));
    }

    if(currentIndex == Messagecount || currentIndex > Messagecount)
    {

        MessageEdit->setText(QString::number(Messagecount));
    }

    int indexpage = MessageEdit->text().toInt();

    int Rowcount = MessagesTable->rowCount();

    for(int i= 0; i <Rowcount ; i++)
    {
        MessagesTable->removeRow(0);
    }

    MessageState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg";

    m_adb->ApplyServ();

    if(m_socket->linkServer())
    {
           qDebug()<<"Link Server";
           QString msg;
           msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
               append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(indexpage));
           qDebug()<<msg<<"++++===";
           m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
           qDebug()<<"12345";
           return;

     }else
     {
         MessageOk->setEnabled(true);
         qDebug()<<"Server Conn Filed";
         return;
     }

}


//最后一页
void downwidget::slotMessageLatPage()
{

    MessageLastPage->setEnabled(false);


    int indexPre = MessageEdit->text().toInt();

    if(indexPre == downwidget::Messagecount)
    {
        //MessagesTable->scrollToBottom();
        MessageLastPage->setEnabled(true);
        return;
    }

    MessageState->setText(QStringLiteral("正 在 检 测 中，请 稍 后....."));
    qDebug()<<"rgfrg";

    int Rowcount = MessagesTable->rowCount();

    for(int i= 0; i <Rowcount ; i++)
    {
        MessagesTable->removeRow(0);
    }



    QString indexstr = MessageEdit->text();
    int index = indexstr.toInt();


    if(index < downwidget::Messagecount)
    {

        MessageEdit->setText(QString::number(Messagecount));

        QString indexstr = MessageEdit->text();

        m_adb->ApplyServ();
        if(m_socket->linkServer())
        {
            qDebug()<<"Link Server";
            QString msg;
            msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
                append(MSG_DATA_ITEMS_SEPARATOR).append(indexstr);
            qDebug()<<msg<<"++++===";
            m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
            qDebug()<<"12345";

        }else
        {
            MessageLastPage->setEnabled(true);
            qDebug()<<"Server Conn Filed";
        }

        return;
    }
}
void downwidget::checkCurrentIndex(int index)
{

    qDebug()<<"index empty";

    //MessagesCheck->setEnabled(false);

    int i = (index-1)*10+1;

    qDebug()<<index<<i<<"oooo";


    if(index > downwidget::Messagecount)
    {
        MessageEdit->setText(QString::number(downwidget::Messagecount));
        return;

    }

    if(downwidget::Messagei < index*10)
    {
        return;
    }
    //QString text = MessagesTable->itemAt(i,3)->text();
    QTableWidgetItem *item =  MessagesTable->item(i,3);
    QString text  = item->text();

    qDebug()<< text<<"grgrwgwrgrgrwgr";

    if(text == "")
    {

        qDebug()<<"index empty ddd";
       MessageState->setText(QStringLiteral("正 在 检 测 中,请 稍 后！"));
        m_adb->ApplyServ();
        if(m_socket->linkServer())
        {
            qDebug()<<"Link Server";
            QString msg;
            msg.append(MSG_USER_OPERATE_Message).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(downwidget::pageValue)).
                append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(index));
            qDebug()<<msg<<"++++===";
            m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
            qDebug()<<"12345";

        }else
        {
            qDebug()<<"Server Conn Filed";
        }
    }else
    {
        return;

    }

}
bool downwidget::SetMessageCurrentIndex(QJsonObject object, QString ret,int pageIndex)
{

        if(pageIndex*10 < Messagei)
        {

            int i = (pageIndex-1)*10+1;
            QTableWidgetItem *item = MessagesTable->item(i,0);
            QString text = item->text();

            qDebug()<<"text:"<<text<<"jjkjkj";

            if(text.isEmpty())
            {

                    QJsonArray message= object.take("message").toArray();

//                    QJsonValue ret_vaue = object.take("ret");
//                    QString ret = ret_vaue.toString();

//                    qDebug()<<ret<<"uuuuu";

                    int tag = message.count();
                    int j = (pageIndex-1)*10;
                    qDebug() << "tag:" << tag;

                    if(ret == "200")
                    {


                       for(int i = 0; i < tag; i++)
                       {

                          QJsonObject json = message.at(i).toObject();
                          QString destnum = json.take("desNum").toString();
                          QString content = json.take("content").toString();
                          QString action = json.take("action").toString();
                          QString date = json.take("date").toString();

                          QString DestNum = m_socket->m_parsejson->RightInfoTransCode(destnum);
                          QString Content = m_socket->m_parsejson->RightInfoTransCode(content);
                          QString Action= m_socket->m_parsejson->RightInfoTransCode(action);
                          QString Date = m_socket->m_parsejson->RightInfoTransCode(date);



                         qDebug()<<"j:"<<j<<"poo";

                         MessageDetailbutton[j] = new QPushButton(QStringLiteral("短信详细"));
                         MessageDetailbutton[j]->setStyleSheet("QPushButton:hover{background-color: rgb(85, 170, 127);}"
                                                         "QPushButton:pressed{background-color: rgb(255, 0, 0);}");
                         MessageDetailbutton[j]->setFixedSize(100,38);

                        //MessagesTable->insertRow(downwidget::Messagei);

                        MessagesTable->setItem(j,0,new QTableWidgetItem(DestNum));


                        MessagesTable->setCellWidget(j,1,MessageDetailbutton[j]);
                        MessagesTable->setItem(j, 1, new QTableWidgetItem(QStringLiteral("")));
                        connect(MessageDetailbutton[j],SIGNAL(clicked()),this,SLOT(slotMessageDetail()));

                        MessagesTable->setItem(j,2,new QTableWidgetItem(Action));
                        MessagesTable->setItem(j,3,new QTableWidgetItem(Date));

                        MessageState->setText(QStringLiteral("检 测 已 经 完 成，请 查 看 检 测 结 果 ！"));

                        QString messageDatail = DestNum.append(MSG_DATA_ITEMS_SEPARATOR).append(Content).
                                        append(MSG_DATA_ITEMS_SEPARATOR).append(Action).append(MSG_DATA_ITEMS_SEPARATOR).
                                        append(Date);

                        AppList::MessageInfo[j] = messageDatail;

                        j= j+1;

                        qDebug()<<j<<"ththt";
                     }

                     int nRow = MessagesTable->rowCount();
                     qDebug()<<nRow<<"All Count";
                     for(int i =0; i<nRow; i++)
                     {
                        MessagesTable->setRowHeight(i,40);
                     }

                    MessageState->setText(QStringLiteral("短 信 已 经 检 测 完 毕，请 查 看 结 果 ！"));
                    return true;
              }else
              {
                        qDebug()<<"Ret error";
                        return false;

              }

            }else
            {
                return false;
            }
        }else
        {
            return false;
        }


}

void downwidget::insertMessagetable(int row)
{

    MessagesTable->insertRow(row);
    MessagesTable->setItem(row,0,new QTableWidgetItem(""));
    MessagesTable->setItem(row,1,new QTableWidgetItem(""));
    MessagesTable->setItem(row,2,new QTableWidgetItem(""));
    MessagesTable->setItem(row,3,new QTableWidgetItem(""));

}

void downwidget::slotMessageExport()
{
//    ContactExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    CallhistoryExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    MessagesExport->setStyleSheet("background-image:url(:/source/icon1/MessageExDo.png);background-color:transparent;");
//    FileExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");


    if(AppList::MessageInfo[0].isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("请先短信检测再导出！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

//        QString safeResultInfo = QStringLiteral("请先安全检测再导出！！！");
//        QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                                     safeResultInfo, QStringLiteral("确定"));
        return;
    }

//    qDebug()<<"callhistory";

//    MessageState->setText(QStringLiteral("检 测 数 据 中，请 稍 后...."));

//    int i = 1;
//    m_adb->ApplyServ();
//    if(m_socket->linkServer())
//    {
//        qDebug()<<"Link Server";
//        QString msg;
//        qDebug()<<MSG_USER_OPERATE_Message_Export_ALL<<"9oooooo";

//        //QString str = "21";
//        msg.append(MSG_USER_OPERATE_Message_Export_ALL);

//        qDebug()<<msg<<"++++===";
//        m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
//        qDebug()<<"12345";
//        msg = "";
//    }else
//    {
//        qDebug()<<"Server Conn Filed";
//    }


    m_messageMsgbox = new MsgBox;
    m_messageMsgbox->setExport(QStringLiteral("短信记录报表"));

    //MessageState->setText(QStringLiteral("数 据 检 测 已 经 完 成！"));

    m_messageMsgbox->anmeEdit->setText(downwidget::unit);
    m_messageMsgbox->unitEdit->setText(downwidget::name);
    m_messageMsgbox->phoneEdit->setText(downwidget::phone);
    m_messageMsgbox->remarkEdit->setText(downwidget::detail);
    m_messageMsgbox->show();

    connect(m_messageMsgbox->exportbutton,SIGNAL(clicked()),this,SLOT(slotMessageReport()));

}

void downwidget::slotMessageReport()
{
    qDebug()<<"callhistory"<<"ii9i9iiii123456";

    downwidget::unit = m_messageMsgbox->anmeEdit->text();
    downwidget::name = m_messageMsgbox->unitEdit->text();
    downwidget::phone = m_messageMsgbox->phoneEdit->text();
    downwidget::detail = m_messageMsgbox->remarkEdit->text();

    m_messageMsgbox->close();

    MessageState->setText(QStringLiteral("检 测 数 据 中，请 稍 后...."));
    m_adb->ApplyServ();
    if(m_socket->linkServer())
    {
        qDebug()<<"Link Server";
        QString msg;
        qDebug()<<MSG_USER_OPERATE_Message_Export_ALL<<"9oooooo";

        //QString str = "21";
        msg.append(MSG_USER_OPERATE_Message_Export_ALL);

        qDebug()<<msg<<"++++===";
        m_socket->sendMsg(MSG_USER_OPERATE_Message,MSG_OPERATE_CMD_SELECT_ALL,msg.size(),msg);
        qDebug()<<"12345";
        msg = "";
    }else
    {
        qDebug()<<"Server Conn Filed";

        QMessageBox box(QMessageBox::Warning,QStringLiteral("提示"),QStringLiteral("服务器异常，请重新连接..."));
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        MessageState->setText(QStringLiteral("检 测 失 败，请 重 新 连 接 服  务 器！！！"));

        return;
    }


    qDebug()<<name<<unit<<"dfbhtrfghtfrdbhgtfc";

    //m_messageWord=new QWord;

    //m_messageWord->showMessageInfo(downwidget::MessageAllRow,unit,name,phone,detail);
}


//文件信息

void downwidget::slotFileJson(QJsonObject object)
{

     qDebug()<<"start praseSDDocumentJsonsss";

     QString fileDatail;
     QStringList filelist;
     int count;

     QJsonValue ret_vaue = object.take("ret");
     QJsonValue opetype_value = object.take("opType");

     QString ret = ret_vaue.toString();
     QString opetype = opetype_value.toString();

     qDebug()<<ret<<opetype<<"result";

     if(ret == "200")
     {

         QJsonArray fileNameList= object.take("fileList").toArray();

         int tag = fileNameList.at(0).toInt();
         qDebug() << "tag:" << tag;
         for(int i = 0; i < fileNameList.size(); i++)
         {

            QJsonObject json = fileNameList.at(i).toObject();

            QString fileName = json.take("fileName").toString();
            QString filepath;

            qDebug()<<"FileInfo: "<<fileName<<"right";
            QString filename = m_socket->m_parsejson->RightInfoTransCode(fileName);

            qDebug()<<"FileInfo: "<<filename<<filepath<<"+++++++++";

            filelist = filename.split("/");
            count= filelist.count();

            QString Filename = filelist.at(count-1);
            for(int i = 1; i < count-1;i++)
            {
                filepath.append(filelist.at(i)).append("/");
            }

            qDebug()<<count<<filepath<<"path....";

            FileTable->insertRow(downwidget::Filei);
            FileTable->setItem(downwidget::Filei,0,new QTableWidgetItem(filelist.at(count-1)));
            FileTable->setItem(downwidget::Filei,1,new QTableWidgetItem(filepath));

            int nRow = FileTable->rowCount();

            qDebug()<<nRow<<"All Count";
            for(int i = 0 ; i < nRow; i++)
            {
               for(int j=0;j<2;j++)
               {

                  FileTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

               }
            }

            FileState->setText(QStringLiteral("检 测 已 经 完 成，请 查 看 检 测 结 果 ！"));

            fileDatail = Filename.append(MSG_DATA_ITEMS_SEPARATOR).append(filepath);

            AppList::FileInfo[downwidget::Filei] = fileDatail;
            downwidget::Filei++;

            //QString filename = json.take("fileName").toString();
            //QString filepath = json.take("filePath").toString();

            qDebug()<<"filename:"<<fileName<<"+++++++++";
         }

         //FileCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
         FileCheck->setEnabled(true);
         return;
     }else if(ret == "210")
     {
         //FileCheck->setStyleSheet("background-image:url(:/source/icon1/checkup.png);background-color:transparent;");
         FileState->setText(QStringLiteral("检 测 已 经 完 成，未 发 现 文 件 ！"));
         FileCheck->setEnabled(true);
         return;

     }
     else
     {
         qDebug()<<"parseFileJson Error";
         FileCheck->setEnabled(true);
         return;
     }

}

void downwidget::slotFileExport()
{

//    ContactExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    CallhistoryExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    MessagesExport->setStyleSheet("background-image:url(:/source/icon1/exportup.png);background-color:transparent;");
//    FileExport->setStyleSheet("background-image:url(:/source/icon1/MessageExDo.png);background-color:transparent;");

    if(AppList::FileInfo[0].isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("导出提示"),QStringLiteral("请先文件检测再导出！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();
        return;
    }

    qDebug()<<"callhistory";
    m_fileMsgbox= new MsgBox;
    m_fileMsgbox->setExport(QStringLiteral("文件信息报表"));

    m_fileMsgbox->anmeEdit->setText(downwidget::unit);
    m_fileMsgbox->unitEdit->setText(downwidget::name);
    m_fileMsgbox->phoneEdit->setText(downwidget::phone);
    m_fileMsgbox->remarkEdit->setText(downwidget::detail);
    m_fileMsgbox->show();

    //QWord::showSafewordinfo("unit","name","phone","detail");

    connect(m_fileMsgbox->exportbutton, SIGNAL(clicked()),this,SLOT(slotFileReport()));

}

void downwidget::slotFileReport()
{

    downwidget::unit = m_fileMsgbox->anmeEdit->text();
    downwidget::name = m_fileMsgbox->unitEdit->text();
    downwidget::phone = m_fileMsgbox->phoneEdit->text();
    downwidget::detail = m_fileMsgbox->remarkEdit->text();

    m_fileMsgbox->close();

    qDebug()<<name<<unit<<"dfbhtrfghtfrdbhgtfc";

    m_FileWord=new QWord;

    FileState->setText(QStringLiteral("文 件 信 息 正 在 导 出 中，请 稍 后..."));

    bool OK =  m_FileWord->showFileInfo(downwidget::Filei,unit,name,phone,detail);
    if(true == OK)
    {
         FileState->setText(QStringLiteral("文 件 信 息 已 经 导 出，请 查 阅！！！"));

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

    }else if(false == OK)
    {
         FileState->setText(QStringLiteral("检 测 已 经 完 成，请 导 出 报 表！！！"));
    }

}

void downwidget::slotContactsbutton()
{/*
    Contactsbutton->setStyleSheet("");
    Contactsbutton->setStyleSheet("background-image:url(:/source/icon1/containfoDo.png);background-color:transparent;");
    //Contactsbutton->setStyleSheet("background-image:url(:/source/icon1/contactup.png);background-color:transparent;");
    Callhistorybutton->setStyleSheet("background-image:url(:/source/icon1/callhistoryup.png);background-color:transparent;");
    Messagesbutton->setStyleSheet("background-image:url(:/source/icon1/messageup.png);background-color:transparent;");
    Filebutton->setStyleSheet("background-image:url(:/source/icon1/Fileup.png);background-color:transparent;");*/
    MobileAllInfowidget->setCurrentIndex(0);
}

void  downwidget::slotCallhistorybutton()
{
//    Contactsbutton->setStyleSheet("background-image:url(:/source/icon1/contactup.png);background-color:transparent;");
//    //Callhistorybutton->setStyleSheet("background-image:url(:/source/icon1/callhistoryup.png);background-color:transparent;");
//    Messagesbutton->setStyleSheet("background-image:url(:/source/icon1/messageup.png);background-color:transparent;");
//    Filebutton->setStyleSheet("background-image:url(:/source/icon1/Fileup.png);background-color:transparent;");
//    Callhistorybutton->setStyleSheet("background-image:url(:/source/icon1/contactDo.png);background-color:transparent;");
    MobileAllInfowidget->setCurrentIndex(1);

}

void downwidget::slotMessagesbutton()
{
//    Contactsbutton->setStyleSheet("background-image:url(:/source/icon1/contactup.png);background-color:transparent;");
//    Callhistorybutton->setStyleSheet("background-image:url(:/source/icon1/callhistoryup.png);background-color:transparent;");
//    //Messagesbutton->setStyleSheet("background-image:url(:/source/icon1/messageup.png);background-color:transparent;");
//    Filebutton->setStyleSheet("background-image:url(:/source/icon1/Fileup.png);background-color:transparent;");
//    Messagesbutton->setStyleSheet("background-image:url(:/source/icon1/MessageDownDo.png);background-color:transparent;");
    MobileAllInfowidget->setCurrentIndex(2);
}

void  downwidget::slotFilebutton()
{
//    Contactsbutton->setStyleSheet("background-image:url(:/source/icon1/contactup.png);background-color:transparent;");
//    Callhistorybutton->setStyleSheet("background-image:url(:/source/icon1/callhistoryup.png);background-color:transparent;");
//    Messagesbutton->setStyleSheet("background-image:url(:/source/icon1/messageup.png);background-color:transparent;");
//    //Filebutton->setStyleSheet("background-image:url(:/source/icon1/Fileup.png);background-color:transparent;");
//    Filebutton->setStyleSheet("background-image:url(:/source/icon1/FileDownDo.png);background-color:transparent;");
    MobileAllInfowidget->setCurrentIndex(3);
}

