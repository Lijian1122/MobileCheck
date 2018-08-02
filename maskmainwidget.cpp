#include "maskmainwidget.h"
#include <QAction>
#include <QtPrintSupport/QPrintEngine>
#include <QPaintEvent>

maskmainwidget::maskmainwidget(QWidget *parent) :
    QWidget(parent)
{

   setMinimumSize(1360,734);
   //resize(1290,730);
   resize(1360,734);

   mainlayout = new QVBoxLayout(this);
   m_upwidget = new upwidget(this);
   m_downwidget = new downwidget(this);

   m_upwidget->setGeometry(0,0,m_upwidget->width(),m_upwidget->height());
   m_downwidget->setGeometry(0,130,m_downwidget->width(),m_downwidget->height());

   //this->maxsize();
   //m_downwidget->m_stackwidget->setGeometry(QRect(0,0,1290,600));
   //m_downwidget->m_stackwidget->setGeometry(QRect(0,0,m_downwidget->width(),m_downwidget->height()));

   //  connect(this,SIGNAL(signalsize(QSize)),m_downwidget,SLOT(slotmax(QSize)));

}

void maskmainwidget::slotmax(QSize maxsize)
{

    qDebug()<<"12345";
    resize(this->maximumSize());
    //resize(maxsize);

    m_upwidget->isMax_ = true;
    m_upwidget->setGeometry(0,0,maximumSize().width(),130);

    m_downwidget->isMax_ = true;
    //m_upwidget->setStyleSheet("background-color:black");
    //m_downwidget->setGeometry(0,130,maximumSize().width(),(maximumSize().height()-130));
    m_downwidget->setStyleSheet("background-color:red");
    m_downwidget->m_stackwidget->setGeometry(QRect(2,2,m_downwidget->width()-4,(m_downwidget->height()- 134)));
    maxsize = this->size();
    signalsize(maxsize);

}

void maskmainwidget::paintEvent(QPaintEvent *event)
{
    m_backgroundpixmap = new QPixmap;
    QPainter painter(this);
    if(this->isMaximized()) //窗口最大化则不用绘制阴影
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(5, 5, this->width()-10, this->height()-10);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));
        QColor color(0, 0, 0, 50);
        for(int i=0; i<5; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(5-i, 5-i, this->width()-(5-i)*2, this->height()-(5-i)*2);
            color.setAlpha(100 - qSqrt(i)*50);
            painter.setPen(color);
            painter.drawPath(path);
        }
        mainlayout->setMargin(5);
        m_upwidget->setGeometry(0,0,1675,m_upwidget->height());
        m_downwidget->setGeometry(0,130,m_downwidget->width(),m_downwidget->height());
        m_downwidget->m_stackwidget->setGeometry(QRect(0,0,1290,600));
  //      painter.drawPixmap(5,5,rect().width()-10,rect().height()-10,m_backgroundpixmap);
    }
    else
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(5, 5, this->width()-10, this->height()-10);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));
        QColor color(0, 0, 0, 50);
        for(int i=0; i<5; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(5-i, 5-i, this->width()-(5-i)*2, this->height()-(5-i)*2);
            color.setAlpha(100 - qSqrt(i)*50);
            painter.setPen(color);
            painter.drawPath(path);
        }
        mainlayout->setMargin(5);
        m_upwidget->setGeometry(0,0,this->maximumWidth(),m_upwidget->height());
        m_downwidget->setGeometry(0,130,this->maximumWidth(),(this->maximumHeight()- m_upwidget->height()));
        m_downwidget->m_stackwidget->setGeometry(QRect(0,0,this->maximumWidth(),(this->maximumHeight()- m_upwidget->height())));
//        m_upwidget->setGeometry(0,0,1675,m_upwidget->height());
//        m_downwidget->setGeometry(0,130,this->maximumWidth(),m_downwidget->height());
//        m_downwidget->m_stackwidget->setGeometry(QRect(0,0,1290,600));
      //  painter.drawPixmap(rect(),m_backgroundpixmap);
    }
}

//void maskmainwidget::mousePressEvent(QMouseEvent * event )
//{
//  //只能是鼠标左键移动和改变大小
//  if(event->button() == Qt::LeftButton)
//  {
//    mouse_press = true;
//  }
//  //窗口移动距离
//  move_point = event->globalPos() - pos();
//}

//void maskmainwidget::mouseReleaseEvent(QMouseEvent *)
//{
//    mouse_press= false;
//}
//void maskmainwidget::mouseMoveEvent(QMouseEvent *event)
//{
//    //移动窗口
//      if(mouse_press)
//      {
//        QPoint move_pos = event->globalPos();
//        move(move_pos - move_point);
//      }
//}
