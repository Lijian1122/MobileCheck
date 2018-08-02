#include "mybutton.h"
#include <QPixmap>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintEngine>

#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QFontMetrics>
#include <QBrush>
#include <QtMath>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>

mainButton::mainButton(QString strpixnormal,QString strpixenter,QString strpixleave,QWidget*parent):QPushButton(parent)
{
    QPixmap pixnormal(strpixnormal);
    QPixmap pixenter(strpixenter);
    QPixmap pixleave(strpixleave);

    setCursor(Qt::PointingHandCursor);
    m_leave=false;
    m_enter=true;
    m_leaveIndex=0;
    m_enterIndex=0;
    m_pixnormal=pixnormal;
    for(int i=0;i<10;i++)//进入
    {
        m_enterlist<<pixenter.copy(i*(pixenter.width()/10),0,pixenter.width()/10,pixenter.height());
    }
    for(int j=0;j<8;j++)//离开
    {
        m_leavelist<<pixleave.copy(j*(pixleave.width()/8),0,pixleave.width()/8,pixleave.height());
    }
    m_enteranimation=new QPropertyAnimation(this,"");
    m_enteranimation->setStartValue(0);
    m_enteranimation->setEndValue(9);
    m_enteranimation->setDuration(600);
    connect(m_enteranimation,SIGNAL(valueChanged(QVariant)),this,SLOT(entervaluechange(QVariant)));

    m_leaveanimation=new QPropertyAnimation(this,"");
    m_leaveanimation->setStartValue(0);
    m_leaveanimation->setEndValue(7);
    m_leaveanimation->setDuration(600);
    connect(m_leaveanimation,SIGNAL(valueChanged(QVariant)),this,SLOT(leavevaluechange(QVariant)));

}
mainButton::~mainButton()
{
    delete m_leaveanimation;
    delete m_enteranimation;

}
void mainButton::enterEvent(QEvent *)
{
    m_enter=true;
    m_leave=false;
    m_enteranimation->start();
}
void mainButton::leaveEvent(QEvent *)
{
    m_enter=false;
    m_leave=true;
    m_leaveanimation->start();
}
void mainButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(m_enter)
    painter.drawPixmap(rect(),m_enterlist.at(m_enterIndex));
    if(m_leave)
    painter.drawPixmap(rect(),m_leavelist.at(m_leaveIndex));
}


//有关菜单四态图
ButtonFour::ButtonFour(QString pixnormal,QWidget*parent):QPushButton(parent)
{
     this->setCursor(Qt::PointingHandCursor);
     m_index=0;
     m_enter=false;
     QPixmap pix(pixnormal);
     for(int i=0;i<4;i++)
     m_pixlist<<pix.copy(i*(pix.width()/4),0,pix.width()/4,pix.height());
}
void ButtonFour::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap((width()-m_pixlist.at(m_index).width())/2,(height()-m_pixlist.at(m_index).height())/2
                             ,m_pixlist.at(m_index).width()
                             ,m_pixlist.at(m_index).height(),m_pixlist.at(m_index));//画图画到中间

}

void ButtonFour::enterEvent(QEvent *)
{
    m_index=1;
    m_enter=true;
    update();
}

void ButtonFour::leaveEvent(QEvent*)
{
    m_index=0;
    m_enter=false;
    update();
}

void ButtonFour::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)//如果是左键按下
    {
        m_index=2;
        update();
        QPushButton::mousePressEvent(e);//返回到上级
    }

}

void ButtonFour::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)//如果是左键放下
    {
        m_index=1;
        update();
       QPushButton::mouseReleaseEvent(e);//返回到上级 引出按钮clicked信号
    }

}
ButtonFour::~ButtonFour()
{

}

//按钮两张图片切换
main4Button::main4Button(QString pixani,QString pixurl,QWidget*parent):QPushButton(parent)
{
    QPixmap anipix(pixani);
    QPixmap norpix(pixurl);
    for(int i=0;i<4;i++)
    m_normallist<<norpix.copy(i*(norpix.width()/4),0,norpix.width()/4,norpix.height());
    for(int i=0;i<8;i++)
    m_animalist<<anipix.copy(i*(anipix.width()/8),0,anipix.width()/8,anipix.height());
    setCursor(Qt::PointingHandCursor);
    animaindex=0;
    m_animation=new QPropertyAnimation(this,"");
    m_animation->setStartValue(0);
    m_animation->setEndValue(7);
    m_animation->setDuration(500);
    connect(m_animation,SIGNAL(valueChanged(QVariant)),this,SLOT(slot_valuechange(QVariant)));
    m_enter=false;
}
void main4Button::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(m_enter)
    {
        p.drawPixmap(rect(),m_animalist.at(animaindex));
    }
    else
    {
        p.drawPixmap(rect(),m_normallist.at(0));
    }
}
void main4Button::enterEvent(QEvent *)
{
    m_enter=true;
    m_animation->start();
}
void main4Button::leaveEvent(QEvent *)
{
    m_enter=false;
    update();
}


//垂直的两态图切换

checkButton::checkButton(QString pixcheckurl, QWidget *parent):QPushButton(parent)
{

    this->setCursor(Qt::PointingHandCursor);
    m_checked=false;
    m_enter=0;
    QPixmap pix(pixcheckurl);
    for(int i=0;i<2;i++)
    m_checklist<<pix.copy(i*(pix.height()/2),0,pix.width(),(pix.height()/2));
}
void checkButton::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.drawPixmap((width()-m_checklist.at(m_enter).width())/2,(height()-m_checklist.at(m_enter).height())
                             ,m_checklist.at(m_enter).width()
                             ,m_checklist.at(m_enter).height(),m_checklist.at(m_enter));//画图画到中间
//    QPainter p(this);
//    QPainter p1(this);
//    QPixmap m_pixcheckhover(":/image/cat_hover.png");
//    QPixmap m_pixuncheckhover(":/image/cat_gray_hover.png");

//    if(m_checked)//如果选中了
//    {
//        if(m_enter)
//        {
//            p.drawPixmap(rect(),m_pixcheckhover);
//            p.drawPixmap(110,110,m_checklist.at(m_checkindex));
//        }
//        p1.drawPixmap(rect(),m_pixcheck);
//        p1.drawPixmap(110,110,m_checklist.at(m_checkindex));
//    }
//    else//如果没选中了
//    {
//        if(m_enter)
//        {
//             p.drawPixmap(rect(),m_pixuncheckhover);
//             p.drawPixmap(110,110,m_checklist.at(m_uncheckindex));
//        }
//        p1.drawPixmap(rect(),m_pixuncheck);
//        p1.drawPixmap(110,110,m_checklist.at(m_uncheckindex));
//    }
}
void checkButton::enterEvent(QEvent *)
{
    m_enter=0;
    m_checked=false;
    update();
}

void checkButton::leaveEvent(QEvent *)
{
    m_enter=1;
    m_checked=true;
    update();
}

void checkButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)//如果是左键按下
    {
        m_enter=0;
        update();
        QPushButton::mousePressEvent(e);//返回到上级
    }

}


