#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <Windows.h>
#include <WindowsX.h>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QKeyEvent>

#include "upwidget.h"
#include "downwidget.h"
#include <maskmainwidget.h>

#include <QAbstractNativeEventFilter>
#include "Adb.h"

#include "Windows.h"
#include "lusb0_usb.h"
#include "SetupAPI.h"
#include "InitGuid.h"
#include "string"
#include "socket.h"
#include "QObject"
//#include <parseJson/parsejson.h>


extern "C"{
   #include "hid/hidsdi.h"
}

static wchar_t *szStr;

static PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;
DEFINE_GUID (UsbClassGuid, 0xa5dcbf10L, 0x6530, 0x11d2, 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed);
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE, 0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, \
0xC0, 0x4F, 0xB9, 0x51, 0xED);

//, public QAbstractNativeEventFilter
class mainwidget : public QDialog
{
    Q_OBJECT
public:
    explicit mainwidget(QWidget *parent = 0);
    ~mainwidget();

    int screenshotfun();

    QString UTF82GBK(const QString &inStr);

    void datatopicture(QString fromdata,QString topic,QString myformat);

    void creatExportForder();

    QByteArray  strToInterCode(const QString &str);//字符串转内码
    QString interCodeToStr(const QByteArray &data);

    void keyPressEvent(QKeyEvent *event);



//    //使窗体变为顶层窗体。
//    void activateWindow();

//    void resizeEvent(QResizeEvent*event);

//    void moveEvent(QMoveEvent *event);

    /***判断USB设备是否插入********/
    //virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);

    int my_usb_get_device_list(void);

    char FirstDriveFromMask (ULONG unitmask);

    LPCWSTR stringToLPCWSTR(std::string orig);

signals:

    void signalMax(QSize);

public slots:

    void slot_iconIsActived(QSystemTrayIcon::ActivationReason reason);
    void opentgpmenu();
    void slotShowMaxRestore();
    void menuAction();

    void slot_setcurstack0()
    {

        m_maskmainwidget->m_upwidget->m_closebtn->setDefault(false);
        m_maskmainwidget->m_downwidget->m_stackwidget->setCurrentIndex(0);
        //UnhookWindowsHookEx(m_maskmainwidget->m_downwidget->hookkeyboard1);

//        m_maskmainwidget->m_upwidget->m_homepagebtn->setStyleSheet("");
//        //m_maskmainwidget->m_upwidget->m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/home.png);");
//        m_maskmainwidget->m_upwidget->m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safeUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/resultUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");



    }
    void slot_setcurstack1()
    {
        qDebug()<<"safe check info";

//        m_maskmainwidget->m_upwidget->m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/homeUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safe.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/resultUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");

        m_maskmainwidget->m_downwidget->m_stackwidget->setCurrentIndex(1);
        //UnhookWindowsHookEx(m_maskmainwidget->m_downwidget->hookkeyboard1);

        //m_maskmainwidget->m_downwidget->SafeCheckInfo();

    }
    void slot_setcurstack2()
    {

//        m_maskmainwidget->m_upwidget->m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/InfoUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safeUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/result.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");

        m_maskmainwidget->m_downwidget->m_stackwidget->setCurrentIndex(3);
        //UnhookWindowsHookEx(m_maskmainwidget->m_downwidget->hookkeyboard1);

    }
    void slot_setcurstack3()
    {

//        m_maskmainwidget->m_upwidget->m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/InfoUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safeUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/result.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");


        m_maskmainwidget->m_downwidget->m_stackwidget->setCurrentIndex(4);

        //UnhookWindowsHookEx(m_maskmainwidget->m_downwidget->hookkeyboard1);
    }
    void slot_setcurstack4()
    {

//        m_maskmainwidget->m_upwidget->m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/InfoUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safeUp.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/result.png);background-color:transparent;");
//        m_maskmainwidget->m_upwidget->m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
        m_maskmainwidget->m_upwidget->m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");

        m_maskmainwidget->m_downwidget->m_stackwidget->setCurrentIndex(5);     
    }

    void slotbai();

    void Homepage(){//m_maskmainwidget->m_downwidget->slotHomePageshow();
    }

    void slotMin();

    void slotClose();


protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *enent);
//    void mouseDoubleClickEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *event);
//    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
//    bool winEvent(MSG *message, long *result);
//    bool eventFilter(QObject *object, QEvent *event);

private:

    void setdialoglayout();

    bool mouse_press;

    QPoint  move_point;

public:

    QVBoxLayout *mainlayout;

    maskmainwidget *m_maskmainwidget;
    //upwidget *m_upwidget;
    //downwidget *m_downwidget;
    //rightwidget *m_rightwidget;
    QPixmap m_backgroundpixmap;
    bool    m_MousePressed;
    QPoint  m_MousePos;
    QPoint  m_WindowPos;
    bool isMax_;
    QSystemTrayIcon *system_tray;
    QMenu *m_traymenu;
    QAction *m_actionshow;
    QAction *m_actionhide;
    QAction *m_actionquit;

    QAction *usercation ;
    QAction *WhiteList;
    QAction *Password;
    QMenu  *remove_menu;

    //usb设备相关参数
    QString MobilePID;
    QString MobileVID;
    Adb *m_adb;
    Socket *m_socket;
    //ParseJson * m_parsejson ;

    QRect curGemRect;

};

#endif // MAINWIDGET_H
