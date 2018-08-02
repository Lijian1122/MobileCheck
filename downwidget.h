
#ifndef DOWNWIDGET_H
#define DOWNWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <Common/stackwidget.h>
#include <adb.h>
#include <QTimer>
#include <socket.h>
#include <QProgressBar>
#include <QLayout>
#include <QResizeEvent>
#include <QList>
#include <QProgressDialog>
#include <QTableWidget>
#include <QJsonObject>
#include <cmddata.h>
#include <Mesgbox/msgbox.h>
#include <qword.h>
#include <QLineEdit>
#include "Dbt.h"
#include <QrcodeGenerate/qrcodegenerate.h>
#include <QLineEdit>
#include <QDateTimeEdit>

#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QRect>
#include <QImage>
#include <QPainter>
#include <QImage>

#include <qprintqcrode.h>
#include <QThread>
#include <tcpthread.h>

//LRESULT WINAPI KeyBoardProc(int nCode,WPARAM wparam,LPARAM lparam);

//UI线程类

class HomeThread : public QThread
{
    Q_OBJECT

private:
    int number;
    volatile bool stopped;
protected:
    void run();
    void stop();
public:
    HomeThread(QObject *parent=0);
    ~HomeThread();

signals:
    void UpdateSignal(int num);

public slots:
    void ResetSlot();


};

class downwidget : public QWidget
{
    Q_OBJECT
public:
    explicit downwidget(QWidget *parent = 0);

    void setwidgetshow();  
    void maxsize();

    void paintEvent(QPaintEvent *event);


    //使窗体变为顶层窗体。
    //void activateWindow();

    //窗口重绘
    //void resizeEvent(QResizeEvent* size);

    //首页展示
    void setHomePageshow();


    //手机信息检测
    //void MobileInfoCheck();

    //安全检测

    void SafeCheck();

    void SafeCheckInfo();

    void SafeCountCheckAPP();

    void IconInfoshow();
    void AppNameshow();

    void DeleteAwarryString(int row);


    //手机所有信息检测
    void PhoneInfoCheckfun();
    void PhoneInfoTableWidget();

    void checkCurrentIndex(int index);
    bool SetMessageCurrentIndex(QJsonObject object,QString ret, int index);
    void addSaveQcrode();

    //统计信息界面
    void countCheckResultInfo();
    void countCheckInfoWidget();

    void addUpdateCheckWidget(QStringList);


    //二维码查询信息条件
    void QrcodeCheckInfo();
    void countQrocdeCheckWidget();
    void addQrcrodeCheckWidget(QStringList);

    void creatQrcodeImageForder();

    void QcrodePrintPic();

    void SelectByQcrode(QString qcordestr);

    //void QprintPDdf();


    //权限检测布局
    void resizeEvent(QResizeEvent *event);

    //鼠标事件
    void mousePressEvent(QMouseEvent *e);

    void word123();

    //设备移除提示

    void UsbRemove();

    bool  safecheckSignal(QString info);

    static LRESULT WINAPI KeyBoardProc(int nCode,WPARAM wparam,LPARAM lparam);


signals:

    void SiganlUpdateQrcode(QString num);

    void runsafecheckSignal();

protected:
    bool winEvent(MSG *pMsg, long *result);


public slots:

    //void slotmax(QSize);

    //首页展示界面
    void slotHomePageshow2();

    void slotHomePage();
    void ScreenShotShow();
    void slotMobileState(QString str);
    void slotQrcodeSave();

    //显示图标界面
    void slotAppIcon(QString icondata);

    //手机信息槽信息
    void slotmobileinfo(QString);

    //权限安全检测
    void slotSafecheck();

    void slotsafecheckSignal();

    //权限安全检测结果
    void safeResultshow();
    void parseSafeResult(QJsonObject object);
    void slotSafeResult();
    void slotslidevalue();
    void slotRequestCheckInfo(QStringList packagelist);

    int getScore(int number);

    void IfCheckPackage(QString str);
    void slotExportReport();


    void safeResultJson(QJsonObject);
    void slotCheckDetail();
    void slotSetWhiteList();
    void slotUninstall();
    void slotExportApp();

    void slotReport();

    void setWhiteList();

    //权限检测进度条
    void slotProgressUpdate(QString);
    //QString calcValue(int nValue,int nTotal);

    //手机全部信息
    void slotContactsbutton();
    void slotCallhistorybutton();
    void slotMessagesbutton();
    void slotFilebutton();

    void slotContactsclick();
    void slotCallhistoryclick();
    void slotMessagesclick();
    void slotFileclick();

    //通讯录
    void slotContactJoson(QJsonObject);
    void parseContactInfo(QJsonObject object);

    void slotContactExport();
    void slotContaReport();

    //通话记录
    void slotCallhistoryJson(QJsonObject);

    void slotCallhistoryExport();
    void slotCallhistoryReport();


    //短信记录
    void slotMessageJson(QJsonObject);
    void slotMessagexport(QJsonObject);

    void slotMessageNextPage();
    void slotFrontPage();
    void slotMessageFirstPage();
    void slotMessageLatPage();
    void slotMessageCurrentOk();
    void insertMessagetable(int row);

    void slotMessageExport();
    void slotMessageReport();

    void slotMessageDetail();


    //文件信息

    void slotFileJson(QJsonObject);

    void slotFileExport();
    void slotFileReport();

    //统计查询信息
    //void selectCountCheckInfo(QDateTime,QDateTime);
    void slotCountCheckInfo();

    void slotPrintQrcode();
    void slotOpenCheckInfo();
    void slotSummaryInfo();


    //二维码统计查询信息
    void slotQCountCheckInfo();

    void slotQPrintQrcode();
    void slotQOpenCheckInfo();
    void slotQSummaryInfo();

    void slotSelectByQcrode();

    void slotUpdateQrcode(QString num);


public:

    QStackedWidget *m_stackwidget;

    QWidget *widget1;
    QWidget *countCheckInfo;
    QWidget *countQrcode;
    QWidget *widget4;

    QLabel *screenwidget;
    QWidget *transwidegt;

    QPushButton *safeResultbutton;
    QPushButton *safecheckbutton;

    QProgressBar *safeprogressBar;

    QWidget *SafeCheckwidget;

    QWidget *CheckResultwidget;


    QWidget *PhoneDatailInfowidget;

    QVBoxLayout *SafeChecklayout;

    bool isMax_;

    QString wide;

    QHBoxLayout *screenlayout;
    QHBoxLayout *startlayout;

    //手机连接状态
    QLabel *moblestate;

    //手机信息展示
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QLabel *label8;
    QLabel *label9;

    QLabel *label11;
    //QLineEdit *label11;
    QLabel *label21;
    QLabel *label31;
    QLabel *label41;
    QLabel *label51;
    QLabel *label61;
    QLabel *label71;
    QLabel *label81;
    QLabel *label91;

    //连接手机按钮
    QPushButton *checkbutton;

    //二维码框
    QWidget *qrwidget;
    QPushButton *saveqrcode;
    QrcodeGenerate *m_qrcode;

    //版本信息
    QLabel *labelverson;

    //手机截屏图片

    QLabel *labelscreen;

    //adb
    Adb *m_adb;

    QrcodeGenerate *home_printQrcode;

    //定时器
    QTimer *screentimer;

    //Sokcket
    Socket *m_socket;

    static int Iconiw;

    //检测结果界面

    QWidget *m_checkresult;
    QLabel *appcountlabel;
    QPushButton *GetReportbutton;
    QTableWidget *safeResultTable;
    QLabel *CheckScoreLabel;

    QPushButton *slidebutton;
    QScrollBar *Resulbar;
    static int row;
    static int permissi;
    static int lowriski;
    static int highriski;

    static int countLowRisk;
    static int countHighRisk;

    static QString Appname;
    static int range;
    static int currentrow;
    static int appRequesti;
    static int riskAppCount;
    static QString vType;
    QJsonObject AppObject;
    static int vTypecount;

    QPushButton *whitelistbutton[1000];
    QPushButton *Uninstallbutton[1000];
    QPushButton *ExportAppbutton[1000];
    QPushButton *CheckDetailbutton[1000];


    static QString unit ;
    static QString name ;
    static QString phone ;
    static QString detail ;

    //对话框
    MsgBox *msginfobox;
    MsgBox *msg_box;

    //导出文档

    QWord *m_safeResultWord;

    //进度提示
    QLabel *labelprogress;

    QLabel *Iconlabel[1000];

    QLabel *AppNamelabel[1000];


    //手机所有信息检测

    QLabel *labelPrompt;
    QWidget *buttonWidget;

    QPushButton *Contactsbutton;
    QPushButton *Callhistorybutton;
    QPushButton *Messagesbutton;
    QPushButton *Filebutton;

    QPushButton *ContactCheck;
    QPushButton *ContactExport;

    QPushButton *CallhistoryCheck;
    QPushButton *CallhistoryExport;

    QPushButton *MessagesCheck;
    QPushButton *MessagesExport;

    QPushButton *FileCheck;
    QPushButton *FileExport;


    QTableWidget *ContactTable;
    QTableWidget *CallhistoryTable;
    QTableWidget *MessagesTable;
    QTableWidget *FileTable;


    QPushButton *MessagFirstPage;
    QPushButton *MessageLastPage;
    QPushButton *MessageNextPage;
    QPushButton *MessagefrontPage;
    QLineEdit  *MessageEdit;
    QLabel *MessagePageCount;
    QPushButton *MessageOk;

    QLabel *contanctState;
    QLabel *CallhistState;
    QLabel *MessageState;
    QPushButton *MessageDetailbutton[100000];

    QLabel *FileState;


    static int contactInfoi;
    static int Callhistoryi;
    static int Messagei;
    static int Filei;
    static int MessageAllRow;

    QWord *m_contactWord;
    QWord *m_callhisWord;
    QWord *m_messageWord;
    QWord *m_FileWord;


    MsgBox *m_contactMsgbox;
    MsgBox *m_callhistoryMsgbox;
    MsgBox *m_messageMsgbox;
    MsgBox *m_fileMsgbox;

    MsgBox *m_MessageInfo;

    MsgBox *m_setWhiteListInfo;

    static int nCurScroller; //翻页时的当时滑动条位置
    static int pageValue; // 一页显示条数
    static int pageIndex; //页面索引
    static int Messagecount;
    static int count;
    //检测显示界面

    QStackedWidget *MobileAllInfowidget;
    QWidget *ContactsWidget;
    QWidget *CallhistoryWidget;
    QWidget *MessageWidget;
    QWidget *FileWidget;


    //统计检测信息界面

    QLabel *checkername;
    QLineEdit *checkernameText;

    QLabel *checkerUnit;
    QLineEdit *checkUnitText;

    QLabel *Checkedname;
    QLineEdit *CheckednameEdit;

    QLabel *checkedUnit;
    QLineEdit *checkedUnitEdit;

    QLabel *checkedPhone;
    QLineEdit *checkedPhoneText;

    QLabel *checkedRemark;
    QLineEdit *checkRemarkEdit;

    QLabel *checkStartTime;
    QDateTimeEdit *checkStartEdit;

    QLabel *checkEndTime;
    QDateTimeEdit *checkEndEdit;

    QPushButton *countInfoSelect;

    QTableWidget *countTablewidget;

    QWidget *countSummary;
    QLabel *SummaryTitle;

    QLabel *Personcount;
    QLabel *PersoncountEdit;

    QLabel *ApkCount;
    QLabel *ApkCountEdit;

    QLabel *Highcount;
    QLabel *HighCountEdit;

    QLabel *Riskcout;
    QLabel *RiskcoutEdit;

    QPushButton *ReportSummary;

    QPushButton *CheckQrcode[10000];
    QPushButton *CheckInfoOPen[10000];


    static int allApkcount;
    static int highRiskcount;
    static int lowRiskcount;

    //QrcodeGenerate *m_printQrcode;


    //二维码查询界面
    QPushButton *SweepQrcode;
    QLineEdit *QrcodeText;
    QPushButton *QrcodeSelect;    
    QTableWidget *countQrocdeWidget;

    QWidget *QcountSummary;
    QLabel *QSummaryTitle;

    QLabel *QPersoncount;
    QLabel *QPersoncountEdit;

    QLabel *QApkCount;
    QLabel *QApkCountEdit;

    QLabel *QHighcount;
    QLabel *QHighCountEdit;

    QLabel *QRiskcout;
    QLabel *QRiskcoutEdit;

    QPushButton *QCheckQrcode[10000];
    QPushButton *QCheckInfoOPen[10000];

    QPushButton *QReportSummary;

    static int qallApkcount;
    static int qhighRiskcount;
    static int qlowRiskcount;

    MsgBox *qcrodewidget;

    QImage Qcrodeimg;

    //QImage QcrodeImg;

    QPrintQcrode *m_printQrcode1;

    static QLabel *QrcodeLabel;
    static QLineEdit *QrcodeEdit;


    //线程实例化对象

    //首页展示线程

    //HomeThread *m_homethread;

    TcpThread *m_tcpthread;

    QString strVKCode;

    static downwidget *m_widget;

    static downwidget *Instance();

    static HHOOK hookkeyboard;

};
//downwidget* pdWidget1 = downwidget::Instance();
#endif // DOWNWIDGET_H
