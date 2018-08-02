#include "loginwidget.h"
#include <QFont>
#include <QPainter>
#include <QBitmap>
#include <QPixmap>
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
#include <QStringList>
#include <QPainterPath>
#include <QtMath>
#include <QApplication>
#include <Dbt.h>
#include <WinUser.h>
#include <cmddata.h>
#include <QMessageBox>
#include <QStringList>
#include <Protocal/protocal.h>
#include <QPixmap>
#include <QIcon>
#include <applist.h>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QMessageBox>
#include <string>
#include <string.h>
#include <QDateTime>


QString LoginWidget::Username;
QString LoginWidget::PassWord;
QString LoginWidget::UserInfo;
QStringList LoginWidget::userlist;
QString LoginWidget::Userpart;

//BOOL (WINAPI *My_GetFileLicenseInfo)(__in CHAR *LpPath);
//BOOL (WINAPI *My_GetFileLicenseValue)(__in CHAR *LpKey,__out CHAR *LpValue,__in int nLen);

LoginWidget::LoginWidget(QWidget *parent)
    : QDialog(parent)
{

       setAttribute(Qt::WA_TranslucentBackground);
       //setAttribute(Qt::WA_TranslucentBackground,true);
       //setWindowFlags(Qt::FramelessWindowHint);

       this->resize(490, 270);
       //获取主界面的宽度
       //int width = this->width();
       //int height = this->height();

       //this->setWindowIcon(QIcon(":/LoginWidget/pic/logo.ico"));

      this->setWindowIcon(QIcon(":/skin/source/icon/logo.ico"));

       //初始化为未按下鼠标左键
       mouse_press = false;
       //设置标题栏隐藏
       this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

      upwidget = new QWidget(this);
      upwidget->setGeometry(0, 0, 490, 50);
      upwidget->setStyleSheet("background-color:rgb(0,85,0)");

      //downwidget = new QWidget(this);
      downwidget = new QLabel(this);
      downwidget->setGeometry(0, 40, this->width(), this->height()-40);
      downwidget->setStyleSheet("background-image:url(:/sourceskin/loginback.png);background-color:transparent;");
//      QPixmap pixmap1;
//      pixmap1.load("screen/123.png");
      //QPixmap fitpixmap=pixmap1.scaled(510,230,Qt::KeepAspectRatio);
      //QPixmap fitpixmap=pixmap.scaled(240,428,Qt::KeepAspectRatio);
      //downwidget->setStyleSheet("background-image:url(:/pic/MessCheckDo.png)");
      //downwidget->setPixmap(pixmap1);

      //设置标题
      title_label = new QLabel(upwidget);

      title_label->setGeometry(10, 0, 180, 40);
      title_label->setStyleSheet("background-image:url(:/sourceskin/titlelogin.png)");

      m_closebtn = new ButtonFour(":/pic/close.png",upwidget);
      m_closebtn->setFixedSize(29,24);
      m_closebtn->setGeometry(upwidget->width()-34,2,29,24);

      m_minbtn = new ButtonFour(":/pic/min.png",upwidget);
      m_minbtn->setFixedSize(29,24);
      m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

      //设置提示图片
      msg_label = new QLabel(this);
      msg_label->setGeometry(20, 50, 36, 36);
      msg_label->setScaledContents(true);

      namelabel = new QLabel(this);
      namelabel->setGeometry(250, 70, 70, 40);
      QFont font2 = namelabel->font();
      font2.setBold(true);
      //namelabel->setStyleSheet("color:rgb(255,255,0);font:16pt;background-color:rgb(0,85,0)");
      namelabel->setStyleSheet("font: 14pt");
      namelabel->setFont(font2);
      namelabel->setText(QStringLiteral("用户名:"));

      nameEdit = new QLineEdit(this);
      nameEdit->setGeometry(320, 70, 140, 35);
      QFont font1 = nameEdit->font();
      font1.setBold(true);
      nameEdit->setStyleSheet("font: 12pt");
      nameEdit->setFont(font1);

      passlaber = new QLabel(this);
      passlaber->setGeometry(250,125, 70, 40);
      QFont font3 = passlaber->font();
      font3.setBold(true);
      //unitlaber->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
      passlaber->setStyleSheet("font: 14pt");
      passlaber->setFont(font3);
      passlaber->setText(QStringLiteral("密  码:"));

      passEdit = new QLineEdit(this);
      passEdit->setGeometry(320, 125, 140, 35);
      passEdit->setEchoMode(QLineEdit::Password);
      QFont font4 = passEdit->font();
      font4.setBold(true);
      passEdit->setStyleSheet("font: 12pt");
      passEdit->setFont(font4);

      LoginPrompt = new QLabel(this);
      LoginPrompt->setGeometry(250, 160, 210, 30);
      LoginPrompt->setStyleSheet("color:rgb(255,0,0);font: 10pt;Microsoft YaHei");
      //LoginPrompt->setText(QStringLiteral("密码输入错误,请重新输入！"));


      Loginbutton = new QPushButton(this);
      Loginbutton->setGeometry(250, 195, 210, 40);
      Loginbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/loginInitial.png);}"
                                              "QPushButton:hover{border-image: url(:/sourceskin/loginhover.png);}"
                                              "QPushButton:pressed{border-image: url(:/sourceskin/loginpress.png);}");
      nameEdit->setFocus();

      nameEdit->setText("admin");
      passEdit->setText("admin");

      QObject::connect(m_closebtn, SIGNAL(clicked()), this, SLOT(close()));
      QObject::connect(m_minbtn,SIGNAL(clicked()),this,SLOT(showMinimized()));
      QObject::connect(Loginbutton,SIGNAL(clicked()),this,SLOT(LoginSlot()));

      connect(nameEdit,SIGNAL(returnPressed()),this,SLOT(UsernameSlot()));
      connect(passEdit,SIGNAL(returnPressed()),this,SLOT(PassWordSlot()));

      m_authoriza = new Authoriza;

      //m_authoriza->installEventFilter(this);


//      timer= new QTimer;
//      timer->setInterval(5000);
      //timer->start();
      //connect(timer,SIGNAL(timeout()),this,SLOT(timedone()),Qt::DirectConnection);

}

void LoginWidget::timedone()
{

//    qDebug()<<"123456";

//    bool OK =  m_authoriza->AuthorizaInitializeRemove();

//    if(OK == false)
//    {
//        qDebug()<<"ggggg";

//        timer->stop();
//        m_mainwidget->close();
//        LoginPrompt->setText(QStringLiteral("本产品未授权，请插入Key！"));

//        this->show();
//        return;
//    }
}


LoginWidget::~LoginWidget()
{

}


void LoginWidget::paintEvent(QPaintEvent *event)
{
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(2, 2, this->width()-4, this->height()-4);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));

        QColor color(0, 0, 0, 50);

        for(int i=0; i<2; i++)
        {
             QPainterPath path;
             path.setFillRule(Qt::WindingFill);
             path.addRect(2-i, 2-i, this->width()-(2-i)*2, this->height()-(2-i)*2);
             color.setAlpha(150 - qSqrt(i)*50);
             painter.setPen(color);
             painter.drawPath(path);
        }

        return;

}


void LoginWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        //qDebug()<<"jjyjyr";
        break;
    case Qt::Key_Up:
        //qDebug()<<";ou;o;ou;u";
//    case Qt::Key_1:
//        qDebug()<<event
    default:
        QDialog::keyPressEvent(event);
    }
}

bool LoginWidget::winEvent(MSG *pMsg, long *result)
{
     //MSG* pMsg = reinterpret_cast<MSG*>(message);
   int msgtype = pMsg->message;
//    bool isMax_ = false; //窗口正常化
//    switch(message->message)
//       {
//       case WM_NCLBUTTONDBLCLK:
//       {
//           //slotShowMaxRestore();
//           return true;
//       }
//       break;
//       case WM_NCHITTEST:
//           if(isMax_)
//           {
//               return false;
//           }
//           int xPos = GET_X_LPARAM(message->lParam) - this->frameGeometry().x();
//           int yPos = GET_Y_LPARAM(message->lParam) - this->frameGeometry().y();
//            如果鼠标位于子控件上（子控件不是m_upwidget），则不进行处理
//           if(this->childAt(xPos,yPos) == m_maskmainwidget->m_upwidget)
//           {
//              if(yPos <= 45 && yPos >= 7)
//              {
//                  *result = HTCAPTION; //返回标题栏
//              }
//           }
//           else if(this->childAt(xPos,yPos) != 0)
//           {
//               return false;
//           }

//           // 鼠标区域位于窗体边框，进行缩放
//           if(xPos > 1 && xPos < 7)
//               *result = HTLEFT;
//           if(xPos > (this->width() - 7) && xPos < (this->width() - 1))
//               *result = HTRIGHT;
//           if(yPos > 1 && yPos < 7)
//               *result = HTTOP;
//           if(yPos > (this->height() - 7) && yPos < (this->height() - 1))
//               *result = HTBOTTOM;
//           if(xPos > 1 && xPos < 7 && yPos > 1 && yPos < 7)
//               *result = HTTOPLEFT;
//           if(xPos > (this->width() - 7) && xPos < (this->width() - 1) && yPos > 1 && yPos < 7)
//               *result = HTTOPRIGHT;
//           if(xPos > 1 && xPos < 7 && yPos > (this->height() - 7) && yPos < (this->height() - 1))
//               *result = HTBOTTOMLEFT;
//           if(xPos > (this->width() - 7) && xPos < (this->width() - 1) && yPos > (this->height() - 7) && yPos < (this->height() - 1))
//               *result = HTBOTTOMRIGHT;
//           return true;
//       }
     QString strVKCode;
     BYTE keyBoardState[256] = {0};
     GetKeyboardState(keyBoardState);
      if(msgtype == WM_SYSKEYDOWN)
        {
                qDebug()<<"thjjhjh";
                static DWORD tickCount = 0;
                if ((GetTickCount() - tickCount) > 50)
                {
                            strVKCode = "";
                }
                WCHAR lpString[1024] = {0};
                ToUnicode(pMsg->wParam, HIWORD(pMsg->lParam), keyBoardState, lpString, 1024, 0);
                qDebug()<<"fefeqfqef";
                QString str = QString::fromWCharArray(lpString);
                strVKCode = strVKCode.append(str);
                //strVKCode += lpString;
                tickCount = GetTickCount();

                qDebug()<<strVKCode<<"12354566";

                return true;


        }
       //return false;

}

bool LoginWidget::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
    //hookkeyboard1 = SetWindowsHookEx(WH_KEYBOARD_LL,KeyBoardProc,0,0);

    MSG* pMsg = reinterpret_cast<MSG*>(message);


    //int msgtype = pMsg->message;
    //qDebug()<<msgtype<<"uuuuuuuu";
    switch (pMsg->message)
    {
      case WM_DEVICECHANGE:
      {

        // if(msgtype = WM_DEVICECHANGE)
        //{
        //qDebug()<<"Start";

        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)pMsg->lParam;

        switch(pMsg->wParam)
        {
           case DBT_DEVICETYPESPECIFIC:
                {
                   qDebug()<<"DBT_DEVICETYPESPECIFIC";
                }
                break;
           case DBT_DEVICEARRIVAL:
                  if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
                  {
                      PDEV_BROADCAST_VOLUME pldbv = (PDEV_BROADCAST_VOLUME)lpdb;
                      if(pldbv->dbcv_flags == 0)
                      {
                        //可以插入U盘
                        QString USBdisk = QString(m_mainwidget->FirstDriveFromMask(pldbv->dbcv_unitmask));
                        qDebug()<<QStringLiteral("插入USB设备")<<USBdisk;

                        //m_mainwidget->m_maskmainwidget->m_downwidget->checkbutton->setEnabled(true);

                        //m_mainwidget->m_maskmainwidget->m_downwidget->moblestate->setText(QStringLiteral("已识别到设备已插入,请稍后..."));

//                        m_mainwidget->m_maskmainwidget->m_downwidget->checkbutton->setEnabled(true);
//                        m_mainwidget->m_maskmainwidget->m_downwidget->safecheckbutton->setEnabled(true);
//                        m_mainwidget->m_maskmainwidget->m_downwidget->ContactCheck->setEnabled(true);
//                        m_mainwidget->m_maskmainwidget->m_downwidget->CallhistoryCheck->setEnabled(true);
//                        m_mainwidget->m_maskmainwidget->m_downwidget->MessagesCheck->setEnabled(true);
//                        m_mainwidget->m_maskmainwidget->m_downwidget->FileCheck->setEnabled(true);

                        qDebug()<<"DBT_DEVICEARRIVAL";
//                        m_mainwidget->my_usb_get_device_list();
//                        m_mainwidget->m_maskmainwidget->m_downwidget->moblestate->setText(QStringLiteral("已检测到设备，请开始检测！"));
//                        m_mainwidget->m_maskmainwidget->m_downwidget->labelprogress->setText(QStringLiteral("已发现设备插入，请开始检测！"));
//                        m_mainwidget->m_maskmainwidget->m_downwidget->labelPrompt->setText(QStringLiteral("已检测到设备插入!"));

                    }
                  }
                  break;

          case DBT_DEVICEREMOVECOMPLETE:
                  if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
                  {
                     PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                     if(lpdbv->dbcv_flags == 0)
                     {
                         qDebug()<<"USB设备移除";

                         QString str  = m_mainwidget->m_maskmainwidget->m_downwidget->m_adb->checkDevice();

                         qDebug()<<str<<"9oooo";

                         QString str1 = "List of devices attached \r\n\r\n";

                         if(str == str1)
                         {
                             m_mainwidget->m_maskmainwidget->m_downwidget->UsbRemove();

                             m_mainwidget->m_maskmainwidget->m_downwidget->moblestate->setText(QStringLiteral("设备已移除，请插入检测！"));
                         }
                    }
                 }
                 break;
        }
    }
    break;

//    case WM_KEYDOWN:
//    {
//           //static LRESULT WINAPI KeyBoardProc(int nCode,WPARAM wparam,LPARAM lparam);

//           hookkeyboard = NULL;

//           hookkeyboard = SetWindowsHookEx(WH_KEYBOARD_LL,KeyBoardProc,hInst,0);
//         /*  QString	strVKCode;
//           BYTE keyBoardState[256] = {0};
//           GetKeyboardState(keyBoardState);

//            qDebug()<<"thjjhjh";
//            static DWORD tickCount = 0;
//            if ((GetTickCount() - tickCount) > 50)
//            {
//                        strVKCode = "";
//            }
//            WCHAR lpString[1024] = {0};
//            ToUnicode(pMsg->wParam, HIWORD(pMsg->lParam), keyBoardState, lpString, 1024, 0);
//            qDebug()<<"fefeqfqef";
//            QString str = QString::fromWCharArray(lpString);
//            strVKCode = strVKCode.append(str);
//            //strVKCode += lpString;
//            tickCount = GetTickCount();

//            qDebug()<<strVKCode<<"12354566";

//            //return true*/;


//     }
//     break;
   }

   return false;


}



bool LoginWidget::eventFilter(QObject *object, QEvent *event)
{
//    if (object==nameEdit)         //首先判断控件(这里指 lineEdit1)
//      {
//           if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
//           {
//               QPalette p=QPalette();
//               p.setColor(QPalette::Base,Qt::green);
//               nameEdit->setPalette(p);
//           }
//           else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
//           {
//               QPalette p=QPalette();
//               p.setColor(QPalette::Base,Qt::white);
//               nameEdit->setPalette(p);
//            }
//      }

        qDebug()<<"filter.....";
        if(object == m_authoriza)
        {
//            bool OK = m_authoriza->AuthorizaInitialize();
//            if(OK == false)
//            {
//               qDebug()<<"filter false";
//               QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("本产品未授权，请插入Key！"));
//               box.setStandardButtons (QMessageBox::Ok);
//               box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//               box.setWindowIcon(QIcon("screen/carful.ico"));
//               box.exec();

//               m_mainwidget->close();

//               return QObject::eventFilter(this,event);     // 最后将事件交给上层对话框
//            }
        }

        return false;

//        QDialog *pDialog = qobject_cast<QDialog *>(object);
//        if (pDialog != NULL)
//        {
//               switch (event->type())
//               {

//                 case QEvent::KeyPress:
//                 {
//                     qDebug()<<"uuuuuu";
//                     QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(event);
//                     if (pKeyEvent->key() == Qt::Key_Escape)
//                     {
//                         return true;
//                     }
//                 }
//                 }
//         }

//       return QObject::eventFilter(object,event);     // 最后将事件交给上层对话框
}

void LoginWidget::mousePressEvent( QMouseEvent * event )
{
  //只能是鼠标左键移动和改变大小
  if(event->button() == Qt::LeftButton)
  {
    mouse_press = true;
  }
  //窗口移动距离
  move_point = event->globalPos() - pos();
}


void LoginWidget::mouseReleaseEvent( QMouseEvent *)
{
  mouse_press = false;
}
void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
      if(mouse_press)
      {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
      }
}

void LoginWidget::okOperate()
{
  bool is_hidden = check_box->isHidden();
  if(!is_hidden)
  {
    bool is_checked = check_box->isChecked();
    emit msgChecked(is_checked, true);
  }
  this->accept();
}

void LoginWidget::cancelOperate()
{
//  bool is_check_hidden = check_box->isHidden();
//  bool is_ok_hidden = ok_button->isHidden();
//  if(!is_check_hidden)
//  {
//    bool is_checked = check_box->isChecked();
//    if(!is_ok_hidden)
//    {
//      emit msgChecked(is_checked, false);
//    }
//   else
//   {
//     emit okMessageHidden(is_checked);
//   }
//  }
//  this->reject();
}

//判断授权
//bool LoginWidget::AuthorizaInitialize()
//{
//    QString stime = NULL;
//    QString etime = NULL;

//    HMODULE m_Hm = LoadLibraryW(L"PrintLicense.dll");
//    if (!m_Hm)
//    {
//        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("授权 DLL 加载失败！"));
//        box.setStandardButtons (QMessageBox::Ok);
//        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
//        box.setWindowIcon(QIcon("screen/carful.ico"));
//        box.exec();

//        return false;
//    }
//    My_GetFileLicenseInfo	= (BOOL (WINAPI *)(__in CHAR *LpPath))GetProcAddress(m_Hm,("GetFileLicenseInfo"));
//    My_GetFileLicenseValue	= (BOOL (WINAPI *)(__in CHAR *LpKey,__out CHAR *LpValue,__in int nLen))GetProcAddress(m_Hm,("GetFileLicenseValue"));

//    if (!My_GetFileLicenseInfo || !My_GetFileLicenseValue)
//    {
//        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("函数加载失败！"));
//        box.setStandardButtons (QMessageBox::Ok);
//        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
//        box.setWindowIcon(QIcon("screen/carful.ico"));
//        box.exec();

//        FreeLibrary(m_Hm);
//        return false;
//    }

//    My_GetFileLicenseInfo("介质");

//    //授权产品标题
//    CHAR Value_title[256];
//    My_GetFileLicenseValue("title", Value_title, 256);
//    QString title = QString::fromLocal8Bit(Value_title);
//    QString current_title = QStringLiteral("智能手机安全检测系统 (MobileCheck)");
//    if(title != current_title)
//    {
//        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("未授权或授权产品不匹配！"));
//        box.setStandardButtons (QMessageBox::Ok);
//        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
//        box.setWindowIcon(QIcon("screen/carful.ico"));
//        box.exec();

//        FreeLibrary(m_Hm);
//        return false;

//    }

//    //授权部门或单位
//    CHAR Value_username[256];
//    My_GetFileLicenseValue("UserName", Value_username, 256);
//    QString username = QString::fromLocal8Bit(Value_username);
//    QString current_username = QStringLiteral("北京研发部");
//    if(username != current_username)
//    {
//        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("该部门或单位未授权！"));
//        box.setStandardButtons (QMessageBox::Ok);
//        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
//        box.setWindowIcon(QIcon("screen/carful.ico"));
//        box.exec();

//        FreeLibrary(m_Hm);
//        return false;
//    }

//    //授权公司
//    CHAR Value_Company[256];
//    My_GetFileLicenseValue("LicensingCompany", Value_Company, 256);
//    QString Company = QString::fromLocal8Bit(Value_Company);
//    qDebug()<<Company<<"fgggggg";
//    QString current_company = QStringLiteral("北京峰盛博远科技股份有限公司");
//    if(Company != current_company)
//    {
//        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("本产品为非法公司授权！"));
//        box.setStandardButtons (QMessageBox::Ok);
//        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//        box.setWindowIcon(QIcon("screen/carful.ico"));
//        box.exec();

//        FreeLibrary(m_Hm);
//        return false;
//    }

//    //授权版本类型
////    CHAR Value_title[256];
////    My_GetFileLicenseValue("LicensingCompany", Value_title, 256);
////    QString title = QString::fromLocal8Bit(Value_title);
////    qDebug()<<title<<"fgggggg";


//    //开始授权日期
//    CHAR Value_stime[256];
//    My_GetFileLicenseValue("stime", Value_stime, 256);
//    stime = QString::fromLocal8Bit(Value_stime);
//    //qDebug()<<stime<<"fgggggg";

//    //结束授权日期
//    CHAR Value_etime[256];
//    My_GetFileLicenseValue("etime", Value_etime, 256);
//    etime = QString::fromLocal8Bit(Value_etime);
//    //qDebug()<<etime<<"fgggggg";

//    //当前时间
//    QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
//    qDebug()<<currenttime<<"fgggggg";

//    QDateTime sdatetime = QDateTime::fromString(stime,"yyyy-MM-dd");
//    QDateTime edatetime = QDateTime::fromString(etime,"yyyy-MM-dd");
//    QDateTime currentdate = QDateTime::fromString(currenttime,"yyyy-MM-dd");
//    //QDateTime currentdate = QDateTime::fromString("2018-03-02","yyyy-MM-dd");
//    //QDateTime currentdate = QDateTime::fromString("2017-03-02","yyyy-MM-dd");

//    if(currentdate < sdatetime || currentdate > edatetime)
//    {
//        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("本产品未授权或授权过期！"));
//        box.setStandardButtons (QMessageBox::Ok);
//        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//        box.setWindowIcon(QIcon("screen/carful.ico"));
//        box.exec();

//        FreeLibrary(m_Hm);
//        return false;

//    }

//    FreeLibrary(m_Hm);

//    return true;

//}

void LoginWidget::LoginSlot()
{

    m_mainwidget = new mainwidget();
    m_mainwidget->show();

    return;


    bool OK =  m_authoriza->AuthorizaInitialize();

    if(false == OK)
    {
        return;

    }
    qDebug()<<"sss start";
    Username = nameEdit->text().trimmed();
    PassWord = passEdit->text().trimmed();

    PassWord = this->EncryPassword(PassWord);

    //m_mainwidget = new mainwidget();

    if(Username == NULL)
    {

        QString  pMessage = QStringLiteral("用户名不允许为空，请重新输入！");
        LoginPrompt->setText(pMessage);
        //QMessageBox::information(this, QStringLiteral("登录提示"), pMessage, QStringLiteral("确定"));
        nameEdit->setFocus();
        passEdit->clear();
        return;
    }

    if(PassWord == NULL)
    {

       QString  pMessage = QStringLiteral("请输入密码！！！");
       LoginPrompt->setText(pMessage);
       passEdit->clear();
       //QMessageBox::information(this, QStringLiteral("登录提示"), pMessage, QStringLiteral("确定"));
       return;

    }

  if(PassWord != NULL)
  {
     UserInfo = cmdData::userLogin(Username);
     AppList::UserInfolist= UserInfo.split(MSG_DATA_ITEMS_SEPARATOR);
     if(UserInfo  == NULL)
     {
        QString  pMessage = QStringLiteral("用户名输入错误，请重新输入！");
        LoginPrompt->setText(pMessage);
        //QMessageBox::information(this, QStringLiteral("登录提示"), pMessage, QStringLiteral("确定"));
        nameEdit->clear();
        passEdit->clear();
        nameEdit->setFocus();
        return;
     }else
     {
        AppList::IfAmdin = AppList::UserInfolist.at(2);
        qDebug()<<AppList::IfAmdin;

        if(AppList::UserInfolist.at(1) == PassWord)
        {
            qDebug()<<"uuuuuu";

            QString  pMessage = QStringLiteral("恭喜您，登录成功！");
            Userpart = AppList::UserInfolist.at(3);

            LoginPrompt->setText(pMessage);
            m_mainwidget = new mainwidget();
            m_mainwidget->show();
            this->close();
            return;
        }else
        {
            QString  pMessage = QStringLiteral("密码输入错误，请重新输入！");
            LoginPrompt->setText(pMessage);
            //QMessageBox::information(this, QStringLiteral("登录提示"), pMessage, QStringLiteral("确定"));
            passEdit->clear();
            return;
        }
    }
  }
  qDebug()<<"thjthteg";
  return;
}

QString LoginWidget::EncryPassword(QString str)
{
        QByteArray byte_array;
        byte_array.append(str);
        QByteArray hash_byte_array = byte_array.toBase64();
        QString encrypt = hash_byte_array.data();

        qDebug()<<"encrypt data:"<<encrypt;

        return encrypt;
}
void LoginWidget::UsernameSlot()
{

    m_closebtn->setDefault(false);
    //nameEdit->setFocus();
    qDebug()<<"uiuiiuu";

    passEdit->setFocus();

}

void LoginWidget::PassWordSlot()
{
    m_closebtn->setDefault(false);
    qDebug()<<"sssstart";
    //LoginSlot();
}

