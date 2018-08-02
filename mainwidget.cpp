#include "mainwidget.h"
#include <QPainter>
#include <QBrush>
#include <QtMath>

#include "QDebug"
#include "QLibrary"
#include "QMessageBox"
#include "QTextCodec"
#include "Dbt.h"
#include <qabstractnativeeventfilter.h>
#include <QMessageBox>
#include <windows.h>
#include <string>
#include <QProgressBar>
#include <QFile>
#include "adb.h"
#include "protocal.h"
#include "Common/applist.h"
#include <QStringList>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QImageReader>
#include <QIODevice>
#include <QtMath>
#include <QPainterPath>
#include <QDialogButtonBox>
#include <QToolBar>
#include <QMenuBar>
#include <QDir>

#pragma comment(lib, "user32.lib")
#pragma comment(lib,"setupapi.lib")
#pragma comment(lib,"hid/hid.lib")

#define WM_WinCreate WM_USER+1000

mainwidget::mainwidget(QWidget *parent)
    : QDialog(parent)
{

    //setAttribute(Qt::WA_TranslucentBackground,true);
    //setWindowFlags(Qt::FramelessWindowHint);
    // | Qt::WindowStaysOnTopHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint
    //setWindowFlags(Qt::FramelessWindowHint);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    //Qt::Tool
    //setAttribute(Qt::WA_TranslucentBackground);
    //setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    //setMinimumSize(1280,730);
    //setMaximumSize(1280,730);
    //resize(1280,730);
    setFixedSize(1364,738);
    setWindowIcon(QIcon(":/skin/source/icon/logo.ico"));
    m_MousePressed = false;
    isMax_ = false; //窗口正常化

    m_maskmainwidget = new maskmainwidget(this);
    //m_maskmainwidget->resize(1280,730);
    m_maskmainwidget->setFixedSize(1360,734);
    m_maskmainwidget->setGeometry(2,2,maximumWidth() -4,maximumHeight()- 4);
    //this->m_maskmainwidget->m_downwidget->setStyleSheet("border: 2px solid black;");

    //m_backgroundpixmap.load(":/skin/source/mainbackgroud.png");
    //m_upwidget = new upwidget(this);
    //m_downwidget = new downwidget(this);

    //m_upwidget->setGeometry(0,0,m_upwidget->width(),m_upwidget->height());
    //m_downwidget->setGeometry(0,(830-(830/720)*130),m_downwidget->width(),m_downwidget->height());

    //m_rightwidget = new rightwidget(this);

    setFocusPolicy(Qt::StrongFocus);
    setdialoglayout();

    creatExportForder();

    //系统托盘
    system_tray = new QSystemTrayIcon();
    m_traymenu=new QMenu;
    m_actionshow = new QAction(QStringLiteral("最大化"),m_traymenu);
    m_actionhide = new QAction(QStringLiteral("最小化"),m_traymenu);
    m_actionquit = new QAction(QStringLiteral("退出"),m_traymenu);
    m_traymenu->addAction(m_actionshow);
    m_traymenu->addAction(m_actionhide);
    m_traymenu->addAction(m_actionquit);
    system_tray->setContextMenu(m_traymenu);

    system_tray ->setToolTip(QString("MobileCheck"));
    system_tray ->setIcon(QIcon(":/skin/source/icon/logo.ico"));
    system_tray->show();
    connect(system_tray , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_iconIsActived(QSystemTrayIcon::ActivationReason)));
    //托盘菜单信号槽
    connect(m_actionshow,SIGNAL(triggered()),this,SLOT(showMaximized()));
    connect(m_actionhide,SIGNAL(triggered()),this,SLOT(slotMin()));
    connect(m_actionquit,SIGNAL(triggered()),this,SLOT(slotClose()));

    //connect(m_maskmainwidget->m_upwidget->m_menubtn->setObjectName(usercation),SIGNAL(isChecked()),this,SLOT(slotbai()));

    //窗口菜单信号和曹
    connect(m_maskmainwidget->m_upwidget->m_closebtn,SIGNAL(clicked()),this,SLOT(slotClose()));
    connect(m_maskmainwidget->m_upwidget->m_minbtn,SIGNAL(clicked()),this,SLOT(slotMin()));
    //connect(m_maskmainwidget->m_upwidget->m_menubtn,SIGNAL(clicked()),this,SLOT(menuAction()));
    //connect(m_maskmainwidget->m_upwidget->m_maxbtn,SIGNAL(clicked()),this,SLOT(slotShowMaxRestore()));


    //操作按钮信号和槽
    connect(m_maskmainwidget->m_upwidget->m_homepagebtn,SIGNAL(clicked()),this,SLOT(slot_setcurstack0()));
    connect(m_maskmainwidget->m_upwidget->m_Safeguardsbtn,SIGNAL(clicked()),this,SLOT(slot_setcurstack1()));
    connect(m_maskmainwidget->m_upwidget->m_moni_resultbtn,SIGNAL(clicked()),this,SLOT(slot_setcurstack2()));
    connect(m_maskmainwidget->m_upwidget->m_countbtn,SIGNAL(clicked()),this,SLOT(slot_setcurstack3()));
    connect(m_maskmainwidget->m_upwidget->m_qrcodebtn,SIGNAL(clicked()),this,SLOT(slot_setcurstack4()));


    connect(this,SIGNAL(signalMax(QSize)),m_maskmainwidget,SLOT(slotmax(QSize)));
    //connect(this,SIGNAL(signalMax(QSize)),m_maskmainwidget->m_downwidget,SLOT(slotmax(QSize)));
    //connect(this,SIGNAL(signalMax(QSize)),m_maskmainwidget->m_upwidget,SLOT(slotShowMaxRestore(QSize)));

    //connect(m_maskmainwidget->m_downwidget->checkbutton,SIGNAL(clicked()),m_maskmainwidget->m_downwidget,SLOT(slotHomePageshow()));
    //connect(m_maskmainwidget->m_downwidget->checkbutton,SIGNAL(clicked()),this,SLOT(Homepage()));

    installEventFilter(this);

    //this->showMaximized();

   //m_parsejson = new ParseJson();

   //connect(m_parsejson,SIGNAL(signalmobile(QString)),m_maskmainwidget->m_downwidget,SLOT(slotmobileinfo(QString)));\


    curGemRect = this->geometry();

    mouse_press = false;

}

void mainwidget::slotMin()
{
   this->showMinimized();
   //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

}

void mainwidget::slotClose()
{
    system_tray->setVisible(false);
    this->close();
}

void mainwidget::creatExportForder()
{

    QString saveFileName= QDir::currentPath();

    QString currentpathPre = saveFileName.append("/").append("Export");

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

//使窗体变为顶层窗体
//void mainwidget::activateWindow()
//{
//    QRect curGemRect = this->geometry();

//    Qt::WindowStates winStatus = Qt::WindowNoState;
//    if (this->windowState() & Qt::WindowMaximized)
//    {
//        winStatus = Qt::WindowMaximized;
//    }
//    this->setWindowState(Qt::WindowMinimized);
//    this->setWindowState(Qt::WindowActive | winStatus);
//    this->setGeometry(curGemRect);
//    this->activateWindow();
//    this->raise();
//    return;
//}

//void mainwidget::resizeEvent(QResizeEvent*event)
//{
//    curGemRect = geometry();
//}

//void mainwidget::moveEvent(QMoveEvent *event)
//{
//    curGemRect = geometry();
//}

void mainwidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}


void mainwidget::datatopicture(QString fromdata,QString toPic,QString myformat)
{
//        QFile file("D:\Qt\p1.txt");
//        QString topic = "D:\Qt\p2.png";
          QString ss = NULL;
          QFile file(fromdata);
          QByteArray Revcmsg;
          int m=0;

          if(file.open(QFile::ReadWrite))
          {
              QByteArray data = file.readAll();
              QString data1 = data.data();
              //QByteArray hexed = data1.toLatin1();

              QByteArray compressed = qCompress(data, 1); // better just open file with QFile, load data, compress and toHex?

              QByteArray hexed = compressed.toHex();
            //QByteArray hexed = data1.toLocal8Bit().toHex();

            //hexed = hexed.append(data1).toHex();
              qDebug()<<data<<data1.size();

              qDebug()<<hexed.data()<<"=====";

          }

          QFile file1("D:/Qt/88.txt");
          QString str;

          if(file1.open(QFile::ReadWrite))
          {

              QString lijian("D:/Qt/86.png");
              QByteArray read = file1.readAll();
              qDebug()<<read.data()<<"+++";

              QString rStr = QString::fromLatin1(read.data(), read.size());

              qDebug()<<rStr<<"-----";

              QByteArray hexed = QByteArray::fromHex(rStr.toLatin1());

              qDebug()<<hexed.data()<<hexed.size();

              QByteArray compressed = qUncompress(hexed);

               //QBuffer buffer(&compressed);
              QBuffer buffer(&hexed);

              buffer.open(QIODevice::ReadWrite);


              QImageReader reader(&buffer, "PNG");
              reader.setFormat("PNG");
              QImage image = reader.read();

              qDebug()<<reader.errorString()<<reader.error();
              image.save(lijian);
          }


//         if(file.open(QFile::ReadWrite))
//         {
//             QByteArray data = file.readAll();
//             QString data1 = data.data();
//             qDebug()<<data1.size();
//             QStringList byte = data1.split(" ");
//             int count = byte.count();
//             QByteArray date1;
//             for(int i = 0; i < count; i++)
//             {

//                  QString date = byte.at(i);
//                  int a = date.toInt();
                  //qDebug()<<date<<"+++++";
//                  bool ok = true;
//                  QString ss = "0X";
//                QString dec= (QString::number(a,16).toUpper());
//
//                  QString dec= QString::number(a,16);
//                  qDebug()<<dec<<"===";
//                  QByteArray hexed = QByteArray::fromHex(dec.toLatin1());

//                  qDebug()<<hexed.data()<<hexed.size();

//                  QByteArray compressed = qUncompress(hexed);
                  //qDebug()<<dec<<"-----";
//                QByteArray date1 = date.toLatin1();

//                qDebug()<<date1.toHex().data()<<"=======";
                  //QByteArray date1 = dec.toLatin1();

//                  //qDebug()<<date1.data()<<"=======";
//                  Revcmsg = Revcmsg.append(compressed.data());
//             }
//         }

          //QByteArray Revcmsg1 = Revcmsg.toHex();
//          QBuffer buffer(&Revcmsg);

//          buffer.open(QIODevice::ReadWrite);

//          QImageReader reader(&buffer, "PNG");
//          reader.setFormat("PNG");


//          qDebug()<<Revcmsg.data();
//          qDebug()<<buffer.data().size()<<"===";

//          QImage image = reader.read();

          //QString saveFileName=QCoreApplication::applicationDirPath()+ "/33.PNG";

//          qDebug()<<reader.errorString()<<reader.error();

//          image.save(toPic);


}

//void mainwidget::Homepage()
//{

//   m_maskmainwidget->m_downwidget->slotHomePageshow();
////    //分割线框
////    QWidget *cutoff1 = new QWidget(m_maskmainwidget->m_downwidget->widget1);
////    //cutoff1->setFixedSize(930,2);
////    cutoff1->setStyleSheet("background-image:url(:/source/Image/cutoff.jpg)");
////    //cutoff1->setGeometry(350,105,930,2);
////    cutoff1->setGeometry(350,105,(m_maskmainwidget->m_downwidget->maximumWidth() - 350),2);

//}

mainwidget::~mainwidget()
{
    //UnhookWindowsHookEx(pdWidget1->hookkeyboard);
}

QString mainwidget::UTF82GBK(const QString &str)
{
      QTextCodec *gbk = QTextCodec::codecForName("GB18030");
      QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

//    //QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
//    QString utf2gbk = utf8->toUnicode(inStr.toLatin1());

//    qDebug()<<"utf2gbk"<<utf2gbk;

//    return utf2gbk;


       std::string str0 = "6E56";
       QString str1 = QString::fromStdString(str0);

       QStringList list = str1.split(",");
       int count = list.count();
       qDebug()<<count;

//       QTextCodec *codec = QTextCodec::codecForName("utf-8");
//       //QString unicode_str = codec->toUnicode(str.toLatin1().data());
//

//
//       QString unicode_str = codec->toUnicode(str1.c_str());
//       qDebug()<<unicode_str;


       for(int i = 0;i < count; i++)
       {
           QString strstr = list.at(i);
           //QString unicode_str = gbk->toUnicode(strstr.fromUtf8(*str0));
           QString unicode_str = gbk->toUnicode(strstr.toLocal8Bit());
           qDebug()<<strstr<<unicode_str;

       }

       return NULL;
}
void mainwidget::setdialoglayout()
{
    mainlayout = new QVBoxLayout(this);
//    QHBoxLayout *uplayout = new QHBoxLayout();
//    QHBoxLayout *downlayout = new QHBoxLayout();

//    uplayout->addWidget(m_upwidget);
//    uplayout->setMargin(0);
//    downlayout->addWidget(m_downwidget);
//    downlayout->setMargin(0);
//    downlayout->setSpacing(0);

//    mainlayout->addLayout(uplayout);
//    mainlayout->addLayout(downlayout);
//    mainlayout->setMargin(5);
//    mainlayout->setSpacing(0);
//    this->setLayout(mainlayout);

}

//void mainwidget::mousePressEvent(QMouseEvent *e)
//{
//    if(rect().contains(e->pos()) == true && e->button() == Qt::LeftButton && !this->isMaximized())
//    {
//        m_MousePressed = true;
//        m_WindowPos = this->pos();
//        m_MousePos = e->globalPos();
//        e->accept();
//    }
//}


void mainwidget::mousePressEvent(QMouseEvent *event)
{
  //只能是鼠标左键移动和改变大小
  if(event->button() == Qt::LeftButton)
  {
    mouse_press = true;
  }
  //窗口移动距离
  move_point = event->globalPos() - pos();

  //this->move(m_WindowPos + (event->globalPos() - m_MousePos));
  //event->accept();
}

void mainwidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press= false;
}
void mainwidget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
      if(mouse_press)
      {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
      }
}

//void mainwidget::mouseMoveEvent(QMouseEvent *e)
//{
//    if(m_MousePressed && e->pos().y() <= 45)
//    {
//        this->move(m_WindowPos + (e->globalPos() - m_MousePos));
//        e->accept();
//    }

//}

//void mainwidget::mouseReleaseEvent(QMouseEvent *e)
//{
//    if(e->button() == Qt::LeftButton)
//    {
//        m_MousePressed = false;
//    }
//}

//void mainwidget::mouseDoubleClickEvent(QMouseEvent *e)
//{
//    if(e->button() == Qt::LeftButton && e->pos().y() <= 45)
//    {
//        slotShowMaxRestore();
//    }
//}

void mainwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(this->isMaximized()) //窗口最大化则不用绘制阴影
    {
//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRect(5, 5, this->width()-10, this->height()-10);
//        painter.setRenderHint(QPainter::Antialiasing, true);
//        painter.fillPath(path, QBrush(Qt::white));
//        QColor color(0, 0, 0, 50);
//        for(int i=0; i<5; i++)
//        {
//            QPainterPath path;
//            path.setFillRule(Qt::WindingFill);
//            path.addRect(5-i, 5-i, this->width()-(5-i)*2, this->height()-(5-i)*2);
//            color.setAlpha(100 - qSqrt(i)*50);
//            painter.setPen(color);
//            painter.drawPath(path);
//        }
//        //mainlayout->setMargin(5);
//        //painter.drawPixmap(5,5,rect().width()-10,rect().height()-10,m_backgroundpixmap);

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
    else
    {
        //mainlayout->setMargin(0);
        //painter.drawPixmap(rect(),m_backgroundpixmap);

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

//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(2, 2, this->width()-4, this->height()-4);
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.fillPath(path, QBrush(Qt::white));

//    QColor color(0, 0, 0, 50);

//    for(int i=0; i<2; i++)
//    {
//            QPainterPath path;
//            path.setFillRule(Qt::WindingFill);
//            path.addRect(2-i, 2-i, this->width()-(2-i)*2, this->height()-(2-i)*2);
//            color.setAlpha(150 - qSqrt(i)*50);
//            painter.setPen(color);
//            painter.drawPath(path);
//    }



}

//bool mainwidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    Q_UNUSED(eventType);

//    MSG* msg = reinterpret_cast<MSG*>(message);
//    return winEvent(msg, result);
//}

//bool mainwidget::winEvent(MSG *message, long *result)
//{
//    switch(message->message)
//       {
//       case WM_NCLBUTTONDBLCLK:
//       {
//           slotShowMaxRestore();
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
//           // 如果鼠标位于子控件上（子控件不是m_upwidget），则不进行处理
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
//       return false;

//}

//bool mainwidget::eventFilter(QObject *object, QEvent *event)
//{
//    return QDialog::eventFilter(object,event);     // 最后将事件交给上层对话框
//}

void mainwidget::slot_iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        //点击托盘显示窗口
        case QSystemTrayIcon::Context:
        {
           //traymenu->setGeometry(QCursor::pos().rx()-traymenu->width(),QCursor::pos().ry()-traymenu->height(),traymenu->width(),traymenu->height());//托盘菜单的位置
           break;
        }
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
        {
           showNormal();
           activateWindow();
           break;
        }
        default:
           break;
    }

}

void mainwidget::opentgpmenu()
{

}

void mainwidget::slotShowMaxRestore()
{

//    if (isMax_)
//    {
//        mainlayout->setMargin(5);
//        m_maskmainwidget->setGeometry(2,2,maximumWidth() -4,maximumHeight()- 4);
//        this->showNormal();
//        //m_maxbtn->setpixmap(":/skin/top_zdh.png");
//    } else
//    {
//        mainlayout->setMargin(0);
//        this->showMaximized();
//        QSize maxsize = this->maximumSize();
//        m_maskmainwidget->setGeometry(0,0,maximumWidth(),maximumHeight());
//        //m_maskmainwidget->m_upwidget->setGeometry(0,0,this->maximumWidth(),130);
//        //m_maskmainwidget->m_downwidget->setGeometry(0,130,this->maximumWidth(),(this->maximumHeight()-130));
//        //m_maskmainwidget->m_downwidget->setStyleSheet("background-color:blue");
//        //qDebug()<<maxsize.width()<<"+++++";

//        signalMax(maxsize);
//    }
//    isMax_ = !isMax_;

    //screenshotfun();

}

void mainwidget::menuAction()
{
   qDebug()<<"grwegrwg";

   remove_menu = new QMenu();

   QMenu *m_menu = new QMenu();

   qDebug()<<"grwegrwgssssssssssssss";
//   usercation = new QAction(QStringLiteral("用户管理"), m_maskmainwidget->m_upwidget->m_menubtn);
//   WhiteList = new QAction(QStringLiteral("白名单管理"),m_maskmainwidget->m_upwidget->m_menubtn);
//   Password = new QAction(QStringLiteral("修改密码"),m_maskmainwidget->m_upwidget->m_menubtn);



   m_maskmainwidget->m_upwidget->m_menubtn->setContextMenuPolicy(Qt::ActionsContextMenu);

   usercation = new QAction(this);
   usercation->setText(QStringLiteral("用户管理"));

   WhiteList = new QAction(this);
   WhiteList->setText(QStringLiteral("白名单管理"));

   Password = new QAction(this);
   Password->setText(QStringLiteral("修改密码"));

//   m_maskmainwidget->m_upwidget->m_menubtn->addAction(usercation);
//   m_maskmainwidget->m_upwidget->m_menubtn->addAction(WhiteList);
//   m_maskmainwidget->m_upwidget->m_menubtn->addAction(Password);


//   remove_menu->addAction(usercation);
//   remove_menu->addAction(WhiteList);
//   remove_menu->addAction(Password);

    m_menu->addAction(usercation);
    m_menu->addAction(WhiteList);
    m_menu->addAction(Password);

    qDebug()<<"888999997i78i";

    remove_menu->show();
    m_maskmainwidget->m_upwidget->m_menubtn->setMenu(m_menu);

    connect(usercation,SIGNAL(triggered()),this,SLOT(slotbai()));
    connect(WhiteList,SIGNAL(triggered()),this, SLOT(showMinimized()));

}

void mainwidget::slotbai()
{
    this->close();
}

///***判断USB设备是否插入********/
//bool mainwidget::nativeEventFilter(const QByteArray &eventType, void *message, long *)
//{
//    MSG* pMsg = reinterpret_cast<MSG*>(message);
//    QString sMessage = QStringLiteral("手机已经插入,开始下载APK文件");
//    QString pMessage = QStringLiteral("手机已经拔走!");

//    int msgtype = pMsg->message;
//    if(msgtype = WM_DEVICECHANGE)
//    {
//        //qDebug()<<"Start";

//        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)pMsg->lParam;

//        switch(pMsg->wParam)
//        {
//           case DBT_DEVICETYPESPECIFIC:
//                {
//                   qDebug()<<"DBT_DEVICETYPESPECIFIC";
//                   break;
//                }
//           case DBT_DEVICEARRIVAL:
//                  if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
//                  {
//                      PDEV_BROADCAST_VOLUME pldbv = (PDEV_BROADCAST_VOLUME)lpdb;
//                      if(pldbv->dbcv_flags == 0)
//                      {
//                        //可以插入U盘
//                        QString USBdisk = QString(this->FirstDriveFromMask(pldbv->dbcv_unitmask));
//                        qDebug()<<QStringLiteral("插入USB设备")<<USBdisk;

//                        qDebug()<<"DBT_DEVICEARRIVAL";
//                        QMessageBox::information(this, QStringLiteral("设备插入提示"),
//                                                 sMessage, QStringLiteral("确定"));

//                        my_usb_get_device_list();

//                        m_adb->CheckAndroidUsbByAdb();

//                        qDebug()<<QStringLiteral("确认安卓设备插入");
//                      }
//                  }

//                  break;
//          case DBT_DEVICEREMOVECOMPLETE:
//                  if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
//                  {
//                     PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
//                     if(lpdbv->dbcv_flags == 0)
//                     {
//                         qDebug()<<"USB设备移除";

//                         m_maskmainwidget->m_downwidget->UsbRemove();

//                         QString title = QStringLiteral("设备移除提示");

//                         qDebug()<<"DBT_DEVICEREMOVECOMPLETE";
//                         QMessageBox::information(this, QStringLiteral("设备移除提示"), pMessage, QStringLiteral("确定"));

//                         //QMessageBox msgBox(QMessageBox::Warning, title, pMessage, QMessageBox::NoButton);

//                         //QMessageBox::information(this, QStringLiteral("设备移除提示"), pMessage, QMessageBox::NoButton);

//                         //QDialogButtonBox *boxs = msgBox.findChild<QDialogButtonBox*>();

//                         //boxs->hide();

//                         //msgBox.setModal(false);

//                         //msgBox.show();
//                     }
//                  }
//                  break;
//        }

//    }
//    return false;
//}

/********USB配置文件**************/
char mainwidget::FirstDriveFromMask (ULONG unitmask)
{
    char i;

    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
          break;
         unitmask = unitmask >> 1;
    }
    return (i + 'A');
}
LPCWSTR mainwidget::stringToLPCWSTR(std::string orig)
{
    size_t origsize = orig.length() + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length()-1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
    return wcstring;
}

int mainwidget::my_usb_get_device_list(void)
{
    HDEVINFO hDevInfo;
    SP_DEVICE_INTERFACE_DATA spDevData;
    HIDD_ATTRIBUTES strtAttrib;

    BOOL bRes = TRUE;
    int nIndex = 2;

    hDevInfo = ::SetupDiGetClassDevs((LPGUID)&UsbClassGuid,NULL,NULL,DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
    if (hDevInfo != INVALID_HANDLE_VALUE)
    {
        pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT,1024);
        pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

            spDevData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

           BOOL bSuccess;
           while(nIndex > 0)
           {

              bSuccess = ::SetupDiEnumDeviceInterfaces(hDevInfo,NULL,(LPGUID)&GUID_DEVINTERFACE_USB_DEVICE,
                                                         nIndex,&spDevData);
              if(!bSuccess)
              {
                  break;
              }
              nIndex--;
          }

                bRes = ::SetupDiGetInterfaceDeviceDetail(hDevInfo,&spDevData,pDetail,1024,NULL,NULL);
                if (bRes)
                {
                    qDebug()<<"12345";
                    szStr = pDetail->DevicePath;

                    wchar_t * wText = szStr;
                    DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);// WideCharToMultiByte的运用
                    char *psText;   // psText为char*的临时数组，作为赋值给std::string的中间变量
                    psText = new char[dwNum];
                    WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);// WideCharToMultiByte的再次运用
                    //str = psText;
                    QString str = QString(QLatin1String(psText));
                    std::string strstr = psText;

                    LPCWSTR buff = stringToLPCWSTR(strstr);
                    qDebug()<<buff;
                    HANDLE hCom = CreateFile(pDetail->DevicePath,GENERIC_READ|GENERIC_WRITE,
                                             FILE_SHARE_READ|FILE_SHARE_WRITE,
                                             NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,NULL);

                    int error = GetLastError();

                    qDebug()<<str;
                    if (hCom == INVALID_HANDLE_VALUE)
                    {


                       qDebug()<<"INVALID_HANDLE_VALUE"<<error;

                    }
                    if(!HidD_GetAttributes(hCom,&strtAttrib))
                    {
                       int error  = GetLastError();
                       USHORT msg = strtAttrib.ProductID;
                       USHORT msgid = strtAttrib.VendorID;
                       int m = (int)msg;
                       qDebug()<<"ProductID"<<msg;
                       qDebug()<<"VendorID"<<msgid;
                       qDebug()<<error;

                    }else
                    {
                        qDebug()<<"strrAttrib Error";
                    }

                    CloseHandle(hCom);
                }

        }

        ::GlobalFree(pDetail);
        ::SetupDiDestroyDeviceInfoList(hDevInfo);

        return 0;
}
