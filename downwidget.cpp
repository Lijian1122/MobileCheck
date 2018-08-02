#include "downwidget.h"
#include <QDebug>
#include <QtMath>
#include <QPainterPath>
#include <QPainter>


downwidget* downwidget::m_widget = NULL;

downwidget::downwidget(QWidget *parent) : QWidget(parent)
{
    //setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::FramelessWindowHint);


    //m_widget = NULL;
    //m_widget = new downwidget();

    screentimer = new QTimer();

    //hookkeyboard = new HHOOK;

    m_tcpthread = new TcpThread(this);

    m_socket = new Socket;

    m_adb = new Adb;

    m_safeResultWord = new QWord;

    //resize(1290,601);
    resize(1360,604);
    setwidgetshow();

    //this->showMaximized();

    //checkbutton = new QPushButton(QStringLiteral("手机检测"),this->widget1);
    checkbutton = new QPushButton(this->widget1);
    checkbutton->setFixedSize(150,55);
    //checkbutton->setStyleSheet("background-color:rgb(0,0,0)");
    //checkbutton->setStyleSheet("background-image:url(:/source/Image/jiance.png);background-color:transparent;");

    checkbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/mobilecheckInit.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/mobilecheckhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/mobilecheckpress.png);}");
    //checkbutton->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    checkbutton->setGeometry(QRect(this->width()-180,42,200,55));

    //首页手机信息
    setHomePageshow();

    //安全检测
    SafeCheck();

    //安全检测结果
    safeResultshow();

    //所有手机信息展示
    PhoneInfoCheckfun();

    //统计检测信息
    countCheckResultInfo();

    //二维码查询检测信息
    QrcodeCheckInfo();

    //checkbutton->setEnabled(false);
    safecheckbutton->setEnabled(false);
    ContactCheck->setEnabled(false);
    CallhistoryCheck->setEnabled(false);
    MessagesCheck->setEnabled(false);
    FileCheck->setEnabled(false);

    checkbutton->setFocus();

   connect(checkbutton,SIGNAL(clicked()),this,SLOT(slotHomePageshow2()));
   connect(m_socket->m_parsejson,SIGNAL(signalmobile(QString)),this,SLOT(slotmobileinfo(QString)));
   connect(m_socket->m_parsejson,SIGNAL(signalpicture(QString)),this,SLOT(slotAppIcon(QString)));
//   connect(checkbutton,SIGNAL(clicked()),this,SLOT(slotProgressUpdate(QStringList)));
   connect(m_socket->m_parsejson,SIGNAL(ProgressbarApp(QString)),this,SLOT(slotProgressUpdate(QString)));
//   connect(safeResultbutton,SIGNAL(clicked()),this,SLOT(slotSafeResult()));
   connect(safecheckbutton,SIGNAL(clicked()),this,SLOT(slotSafecheck()));
   connect(safeResultbutton,SIGNAL(clicked()),this,SLOT(slotSafeResult()));

   connect(m_socket->m_parsejson,SIGNAL(signalAppList(QStringList)),this,SLOT(slotRequestCheckInfo(QStringList)));
   connect(m_socket->m_parsejson,SIGNAL(singalSafeResult(QJsonObject)),this,SLOT(safeResultJson(QJsonObject)));

   connect(m_socket->m_parsejson,SIGNAL(singalContactInfo(QJsonObject)),this,SLOT(slotContactJoson(QJsonObject)));
   connect(m_socket->m_parsejson,SIGNAL(signalCallhistoryInfo(QJsonObject)),this,SLOT(slotCallhistoryJson(QJsonObject)));
   connect(m_socket->m_parsejson,SIGNAL(signalMessageInfo(QJsonObject)),this,SLOT(slotMessageJson(QJsonObject)));
   connect(m_socket->m_parsejson,SIGNAL(signalFileInfo(QJsonObject)),this,SLOT(slotFileJson(QJsonObject)));
   connect(m_socket->m_parsejson,SIGNAL(signalMessageExport(QJsonObject)),this,SLOT(slotMessagexport(QJsonObject)));


   connect(this,SIGNAL(runsafecheckSignal()),this,SLOT(slotsafecheckSignal()));
   //connect(m_widget,SIGNAL(SiganlUpdateQrcode(QString)),m_widget,SLOT(slotUpdateQrcode(QString)));
   //首页展示界面启动
   //m_homethread->start();

   //connect(m_homethread,SIGNAL(started()),this,SLOT(slotHomePage()));
}

//void downwidget::slotmax(QSize maxsize)
//{
//     //resizeEvent(maxsize);
//    //this->resize(maxsize.width(),(maxsize.height()-130));
//    //this->setStyleSheet("background-color:red");

//    //m_downwidget->setGeometry(0,130,this->width(),(this->height()-130));
//    //this->resize(maxsize.width(),(maxsize.height() - 130));
//    //this->setStyleSheet("background-color:red");
//    // m_downwidget->m_stackwidget->setGeometry(QRect(0,0,m_downwidget->width(),(m_downwidget->height()- 130)));

//    qDebug()<<"12222"<<this->rect().width();

//}

void downwidget::resizeEvent(QResizeEvent* event)
{
//   QWidget::resizeEvent(event);

//   //检测结果
//   safeResultbutton = new QPushButton(QStringLiteral("检测结果"),this->SafeCheckwidget);
//   safeResultbutton->setFixedSize(150,55);
//   safeResultbutton->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
//   //safeResultbutton->setGeometry(QRect(this->width()- 200,32,150,55));
//   safeResultbutton->move(event->size().width()-200,32);

}

void downwidget::setwidgetshow()
{
    m_stackwidget = new QStackedWidget(this);
    m_stackwidget->setGeometry(2, 2, this->width()-4, this->height()-4);

    //首页手机信息展示
    widget1= new QWidget(m_stackwidget);

    //安全监测
    SafeCheckwidget = new QWidget(m_stackwidget);
    CheckResultwidget = new QWidget(m_stackwidget);
    PhoneDatailInfowidget = new QWidget(m_stackwidget);

    //QWidget *countCheckInfo;
    //QWidget *countQrcode;

    countCheckInfo= new QWidget(m_stackwidget);
    countQrcode= new QWidget(m_stackwidget);
    //widget4= new QWidget(m_stackwidget);


    widget1->setStyleSheet("background-color:white");

    SafeCheckwidget->setStyleSheet("background-color:white");
    CheckResultwidget->setStyleSheet("background-color:white");
    PhoneDatailInfowidget->setStyleSheet("background-color:white");
    countCheckInfo->setStyleSheet("background-color:white");
    countQrcode->setStyleSheet("background-color:white");

    m_stackwidget->addWidget(widget1);
    m_stackwidget->addWidget(SafeCheckwidget);
    m_stackwidget->addWidget(CheckResultwidget);
    m_stackwidget->addWidget(PhoneDatailInfowidget);
    m_stackwidget->addWidget(countCheckInfo);
    m_stackwidget->addWidget(countQrcode);

    m_stackwidget->setCurrentIndex(0);

}
void downwidget::paintEvent(QPaintEvent *event)
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

}

void downwidget::mousePressEvent(QMouseEvent *e)
{
//    QPoint pos = e->pos();
//    QTableWidgetItem  *item = safeResultTable->itemAt(pos);
//    qDebug()<<item->row()<<item->column()<<"8989";

}

bool downwidget::winEvent(MSG *pMsg, long *result)
{

    qDebug()<<"tehetheth";
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
     if(msgtype == WM_KEYDOWN)
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
     return false;

}

downwidget *downwidget::Instance()
{
    if(m_widget ==  NULL)
    {
        m_widget = new downwidget;


    }

    //QrcodeEdit->setText("123456");
    return m_widget;
}
